/* FILE NAME: rndshd.c
 * PROGRAMMER: RP5b
 * LAST UPDATE: 01.03.2023
 * PURPOSE: 3D animation project.
 *          Shaders handle module.
 */

#include <stdio.h>

#include "anim/rnd/res/rndres.h"

/* Shaders global data */
rp5bSHADER RP5b_RndShaders[RP5b_MAX_SHADERS]; /* Array of shaders */
INT RP5b_RndShadersSize;                      /* Shadres array store size */

/***
 * Shaders handle functions
 ***/

/* Load text from file function.
 * ARGUMENTS:
 *   - file name:
 *       CHAR *FileName;
 * RETURNS:
 *   (CHAR *) load text (allocated through malloc).
 */
static CHAR * RP5b_RndShdLoadTextFromFile( CHAR *FileName )
{
  FILE *F;
  INT flen;
  CHAR *txt;

  if ((F = fopen(FileName, "rb")) == NULL)
    return NULL;
  /* Get file length */
  fseek(F, 0, SEEK_END);
  flen = ftell(F);

  /* Allocate memory */
  if ((txt = malloc(flen + 1)) == NULL)
  {
    fclose(F);
    return NULL;
  }
  /* Read text from file */
  rewind(F);
  fread(txt, 1, flen, F);
  txt[flen] = 0;

  fclose(F);
  return txt;
} /* End of 'RP5b_RndShdLoadTextFromFile' function */

/* Store shader log to file function.
 * ARGUMENTS:
 *   - shader prefix file name:
 *       CHAR *FileNamePrefix;
 *   - shader handle part name:
 *       CHAR *Part;
 *   - logging text:
 *       CHAR *Text ;
 * RETURNS: None.
 */
static VOID RP5b_RndShdLog( CHAR *FileNamePrefix, CHAR *Part, CHAR *Text )
{
  FILE *F;

  if ((F = fopen("bin/shaders/RP5b{30}SHD.LOG", "a")) == NULL)
    return;
  fprintf(F, "%s/%s\n%s\n", FileNamePrefix, Part, Text);
  fclose(F);
} /* End of ' RP5b_RndShdLog' function */

/* Shader program load function.
 * ARGUMENTS:
 *   - shader directory files prefix (based from /bin/shaders/):
 *       CHAR *FileNamePrefix;
 * RETURNS:
 *   (INT) shader program index (0 if error is occured).
 */
static INT RP5b_RndShdLoad( CHAR *FileNamePrefix )
{
  INT i, prg = 0, res, Pos;
  CHAR *txt[8] = {NULL},
    *loc_inc_txt, *com_inc_txt, *loc_txt;
  struct
  {
    CHAR *Name;   /* Shader name */
    INT Type;     /* Shader type (see GL_***_SHADER) */
    CHAR *Define; /* Defines for shaders */
    INT Id;       /* Result shader Id */
  } shds[] =
  {
    {"vert", GL_VERTEX_SHADER, "\n#version 450\n#define RP5b_VERTEX_SHADER 1\n"},
    {"frag", GL_FRAGMENT_SHADER, "\n#version 450\n#define RP5b_FRAGMENT_SHADER 1\n"},
    {"geom", GL_GEOMETRY_SHADER, "\n#version 450\n#define RP5b_GEOMETRY_SHADER 1\n"},
    {"eval", GL_TESS_EVALUATION_SHADER, "\n#version 450\n#define RP5b_TESS_EVALUATION_SHADER 1\n"},
    {"ctrl", GL_TESS_CONTROL_SHADER, "\n#version 430\n#define RP5b_TESS_CONTROL_SHADER 1\n"},
  };
  INT NoofS = sizeof(shds) / sizeof(shds[0]);
  BOOL isok = TRUE;
  static CHAR Buf[30000];

  /* Load includes */
  com_inc_txt = RP5b_RndShdLoadTextFromFile("bin/shaders/includes/commondf.glsl");
  sprintf(Buf, "bin/shaders/%s/inc.glsl", FileNamePrefix);
  loc_inc_txt = RP5b_RndShdLoadTextFromFile(Buf);

  for (i = 0; i < NoofS && isok; i++)
  {
    /* Load file */
    sprintf(Buf, "bin/shaders/%s/%s.glsl", FileNamePrefix, shds[i].Name);
    loc_txt = RP5b_RndShdLoadTextFromFile(Buf);
    if (loc_txt == NULL)
    {
      if (i >= 2)
        continue;
      RP5b_RndShdLog(FileNamePrefix, shds[i].Name, "Error load file");
      isok = FALSE;
      break;
    }

    /* Create shader */
    if ((shds[i].Id = glCreateShader(shds[i].Type)) == 0)
    {
      RP5b_RndShdLog(FileNamePrefix, shds[i].Name, "Error shader creation");
      free(loc_txt);
      isok = FALSE;
      break;
    }

    /* Attach shader text */
    Pos = 0;
    txt[Pos++] = shds[i].Define;
    txt[Pos++] = "#line 1 \"commondf\"\n";
    txt[Pos++] = com_inc_txt == NULL ? "" : com_inc_txt;
    txt[Pos++] = loc_inc_txt == NULL ? "" : "\n#line 1 \"inc\"\n";
    txt[Pos++] = loc_inc_txt == NULL ? "" : loc_inc_txt;
    txt[Pos++] = strcat(strcat(strcpy(Buf, "\n#line 1 \""), shds[i].Name), "\"\n");
    txt[Pos++] = loc_txt;

    glShaderSource(shds[i].Id, Pos, txt, NULL);
    free(loc_txt);

    /* Compile shader */
    glCompileShader(shds[i].Id);
    glGetShaderiv(shds[i].Id, GL_COMPILE_STATUS, &res);
    if (res != 1)
    {
      glGetShaderInfoLog(shds[i].Id, sizeof(Buf), &res, Buf);
      RP5b_RndShdLog(FileNamePrefix, shds[i].Name, Buf);
      isok = FALSE;
      break;
    }
  }

  /* Free includes memory */
  if (loc_inc_txt != NULL)
    free(loc_inc_txt);
  if (com_inc_txt != NULL)
    free(com_inc_txt);

  /* Create shader program */
  if (isok)
    if ((prg = glCreateProgram()) == 0)
    {
      RP5b_RndShdLog(FileNamePrefix, "PROG", "Error program creation");
      isok = FALSE;
    }
    else
    {
      /* Attach shaders to program */
      for (i = 0; i < NoofS; i++)
        if (shds[i].Id != 0)
          glAttachShader(prg, shds[i].Id);

      /* Link shader program */
      glLinkProgram(prg);
      glGetProgramiv(prg, GL_LINK_STATUS, &res);
      if (res != 1)
      {
        glGetProgramInfoLog(prg, sizeof(Buf), &res, Buf);
        RP5b_RndShdLog(FileNamePrefix, "PROG", Buf);
        isok = FALSE;
      }
    }

  /* Error handle */
  if (!isok)
  {
    /* Delete shaders */
    for (i = 0; i < NoofS; i++)
      if (shds[i].Id != 0)
      {
        if (prg != 0)
          glDetachShader(prg, shds[i].Id);
        glDeleteShader(shds[i].Id);
      }

    /* Delete program */
    if (prg != 0)
      glDeleteProgram(prg);
    prg = 0;
  }
  return prg;
} /* End of 'RP5b_RndShdLoad' function */

/* Shader storage initialize function.
 * ARGUMENTS:
 *   - shader file path to load:
 *       CHAR *ShaderFileNamePrefix;
 * RETURNS:
 *   (INT) new shader stock number.
 */
INT RP5b_RndShdAdd( CHAR *ShaderFileNamePrefix )
{
  if (RP5b_RndShadersSize >= RP5b_MAX_SHADERS)
    return 0;

  strncpy(RP5b_RndShaders[RP5b_RndShadersSize].Name,
    ShaderFileNamePrefix, RP5b_STR_MAX - 1);
  RP5b_RndShaders[RP5b_RndShadersSize].ProgId =
    RP5b_RndShdLoad(ShaderFileNamePrefix);

  return RP5b_RndShadersSize++;
} /* End of 'RP5b_RndShdAdd' function */

/* Shader storage initialize function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID RP5b_RndShdInit( VOID )
{
  RP5b_RndShadersSize = 0;
  RP5b_RndShdAdd("default");
} /* End of 'RP5b_RndShdInit' function */

/* Shader program free function.
 * ARGUMENTS:
 *   - shader program index:
 *       INT Prg;
 * RETURNS: None.
 */
VOID RP5b_RndShdFree( INT Prg )
{
  INT shds[5] = {0}, n, i;

  if (Prg == 0 || !glIsProgram(Prg))
    return;
  glGetAttachedShaders(Prg, 5, &n, shds);
  /* Delete shaders */
  for (i = 0; i < n; i++)
    if (shds[i] != 0 &&  glIsShader(shds[i]))
    {
      glDetachShader(Prg, shds[i]);
      glDeleteShader(shds[i]);
    }
  /* Delete program */
  glDeleteProgram(Prg);
} /* End of 'RP5b_RndShdFree' function */

/* Shader storage deinitialize function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID RP5b_RndShdClose( VOID )
{
  INT i;

  for (i = 0; i < RP5b_RndShadersSize; i++)
    RP5b_RndShdFree(RP5b_RndShaders[i].ProgId);
  RP5b_RndShadersSize = 0;
} /* End of 'RP5b_RndShdClose' function */

/* Shader storage updating function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID RP5b_RndShdUpdate( VOID )
{
  INT i;

  for (i = 0; i < RP5b_RndShadersSize; i++)
  {
    RP5b_RndShdFree(RP5b_RndShaders[i].ProgId);
    RP5b_RndShaders[i].ProgId = RP5b_RndShdLoad(RP5b_RndShaders[i].Name); 
  }
} /* End of 'RP5b_RndShdUpdateS' function */

/* END OF 'rndshd.c' FILE */