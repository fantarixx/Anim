/* FILE NAME: rndfnt.c
 * PROGRAMMER: RP5b
 * LAST UPDATE: 01.03.2023
 * PURPOSE: 3D animation project.
 *          Resourses handle module.
 *          Fonts handle module.
 */

#include <stdio.h>

#include <anim/rnd/rnd.h>

/* Font struct */
typedef struct tagrp5bFONT
{
  DWORD LineH, BaseH; /* Fontline height and base line height in pixels */
  FLT AdvanceX[256];  /* Every letter shift right value
                       * (0 if no letter present) */
} rp5bFONT;

/* Font data */
static rp5bFONT RP5b_RndFntFont;
/* Font characters primitives */
static rp5bPRIM RP5b_RndFntChars[256];
/* Font material */
static INT RP5b_RndFntMtlNo;

/* Load font from .G#DF file function.
 * ARGUMENTS:
 *   - font file name:
 *       CHAR *FileName;
 * RETURNS:
 *   (BOOL) TRUE if succes, FALSE otherwise.
 */
BOOL RP5b_RndFntLoad( CHAR *FileName )
{
  FILE *F;
  INT i;
  DWORD Sign, W, H, *tex;
  rp5bVERTEX Chars[256][4];
  rp5bMATERIAL mtl;

  if ((F = fopen(FileName, "rb")) == NULL)
    return FALSE;

  fread(&Sign, 4, 1, F);
  if (Sign != *(DWORD *)"G3DF")
  {
    fclose(F);
    return FALSE;
  }

  fread(&RP5b_RndFntFont, sizeof(rp5bFONT), 1, F);
  fread(&Chars, sizeof(rp5bVERTEX), 4 * 256, F);
  fread(&W, 4, 1, F);
  fread(&H, 4, 1, F);

  mtl = RP5b_RndMtlGetDef();
  strncpy(mtl.Name, FileName, RP5b_STR_MAX - 1);
  if ((tex = malloc(W * H * 4)) != NULL)
  {
    fread(tex, 4, W * H, F);
    mtl.Tex[0] = RP5b_RndTexAddImg(FileName, W, H, 4, tex);
    free(tex);

  }
  mtl.ShdNo = RP5b_RndShdAdd("font");
  RP5b_RndFntMtlNo = RP5b_RndMtlAdd(&mtl);

  for (i = 0; i < 256; i++)
  {
    RP5b_RndPrimFree(&RP5b_RndFntChars[i]);
    RP5b_RndPrimCreate(&RP5b_RndFntChars[i], RP5b_RND_PRIM_TRISTRIP, Chars[i], 4, NULL, 0);
    RP5b_RndFntChars[i].MtlNo = RP5b_RndFntMtlNo;
  }

  fclose(F);
  return TRUE;
} /* End of 'RP5b_RndFntLoad' function */

/* Init font subsystem funtion.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID RP5b_RndFntInit( VOID )
{
  RP5b_RndFntLoad("bin/fonts/Consolas.g3df");
} /* End of 'RP5b_RndFntInit' funtion */

/* Draw string function.
 * ARGUMENTS:
 *   - string to draw:
 *       CHAR *Str;
 * RETURNS: None.
 */
VOID RP5b_RndFntDraw( CHAR *Str )
{
  VEC3 Pos = {0, 0, 0};

  while (*Str != 0)
  {
    if (*Str == '\n')
      Pos.X = 0, Pos.Y -= 1;
    else
      if (RP5b_RndFntFont.AdvanceX[(BYTE)*Str] != 0)
      {
        RP5b_RndPrimDraw(&RP5b_RndFntChars[(BYTE)*Str], MatrTranslate(Pos));
        Pos.X += RP5b_RndFntFont.AdvanceX[(BYTE)*Str];
      }
    Str++;
  }
} /* End of 'RP5b_RndFntDraw' function */

/* Deinit font subsystem funtion.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID RP5b_RndFntClose( VOID )
{
  INT i;

  for (i = 0; i < 256; i++)
    RP5b_RndPrimFree(&RP5b_RndFntChars[i]);
  memset(RP5b_RndFntChars, 0, sizeof(RP5b_RndFntChars));
} /* End of 'RP5b_RndFntClose' function */

/* END OF 'rndfnt.c' FILE */