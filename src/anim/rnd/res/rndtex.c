/* FILE NAME: rndtex.c
 * PROGRAMMER: RP5b
 * LAST UPDATE: 24.02.2023
 * PURPOSE: 3D animation project.
 *          Textures handle module.
 */

#include <stdio.h>

#include <anim/rnd/res/rndres.h>

/* Textures stock */
rp5bTEXTURE RP5b_RndTextures[RP5b_MAX_TEXTURES]; /* Array of textures */
INT RP5b_RndTexturesSize;                       /* Textures array store size */

/* Texture storage initialize function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID RP5b_RndTexInit( VOID )
{
  RP5b_RndTexturesSize = 0;
} /* End of 'RP5b_RndTexInit' function */

/* Texture storage deinitialize function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID RP5b_RndTexClose( VOID )
{
  INT i;

  for (i = 0; i < RP5b_RndTexturesSize; i++)
    glDeleteTextures(1, &RP5b_RndTextures[i].TexId);
  RP5b_RndTexturesSize = 0;
} /* End of 'RP5b_RndTexClose' function */

/* Texture adding to storage function.
 * ARGUMENTS:
 *   - Name of tuxture:
 *       CHAR *Name;
 *   - Texture sizes:
 *       INT W, H;
 *   - Resizing coef:
 *       INT C;
 *   - Array of texture pixels:
 *       VOID *Bits;
 * RETURNS:
 *   (INT) Number of texture in array of textures.
 */
INT RP5b_RndTexAddImg( CHAR *Name, INT W, INT H, INT C, VOID *Bits )
{
  INT mips;

  if (RP5b_RndTexturesSize >= RP5b_MAX_TEXTURES)
    return -1;

  /* Setup OpenGL texture */
  glGenTextures(1, &RP5b_RndTextures[RP5b_RndTexturesSize].TexId);
  glBindTexture(GL_TEXTURE_2D, RP5b_RndTextures[RP5b_RndTexturesSize].TexId);

  mips = log(W > H ? W : H) / log(2);
  mips = mips < 1 ? 1 : mips;

  /* Upload texture */
  glTexStorage2D(GL_TEXTURE_2D, mips, C == 4 ? GL_RGBA8 : C == 3 ? GL_RGB8 : GL_R8, W, H);
  glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, W, H, C == 4 ? GL_BGRA : C == 3 ? GL_BGR : GL_LUMINANCE,
    GL_UNSIGNED_BYTE, Bits);

  glGenerateMipmap(GL_TEXTURE_2D);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glBindTexture(GL_TEXTURE_2D, 0);

  /* Add to stock */
  strncpy(RP5b_RndTextures[RP5b_RndTexturesSize].Name, Name, RP5b_STR_MAX - 1);
  RP5b_RndTextures[RP5b_RndTexturesSize].H = H;
  RP5b_RndTextures[RP5b_RndTexturesSize].W = W;

  return RP5b_RndTexturesSize++;
} /* End of 'P5b_RndTexAddImg' function */

/* Texture adding from file function.
 * ARGUMENTS:
 *   - Name of file:
 *       CHAR *FileName;
 * RETURNS:
 *   (INT) Number of texture in array of textures.
 */
INT RP5b_RndTexAddFromFile( CHAR *FileName )
{
  INT res = -1;
  rp5bIMAGE Img;

  if (RP5b_ImgLoad(&Img, FileName))
  {
    res = RP5b_RndTexAddImg(FileName, Img.W, Img.H, 4, Img.Pixels);
    RP5b_ImgFree(&Img);
  }
  return res;
} /* End of 'RP5b_RndTexAddFromFile' function */

/* Add texture by OpenGL low-level format to stock function.
 * ARGUMENTS:
 *   - texture name:
 *       CHAR *Name;
 *   - texture size in pixels:
 *       INT W, H;
 *   - OpenGL texture element data type:
 *       INT GLType;
 * RETURNS:
 *   (INT) texture stock number (0 if error is occured).
 */
INT RP5b_RndTexAddFmt( CHAR *Name, INT W, INT H, INT GLType )
{
  if (RP5b_RndTexturesSize >= RP5b_MAX_TEXTURES)
    return -1;

  /* Setup OpenGL texture */
  glGenTextures(1, &RP5b_RndTextures[RP5b_RndTexturesSize].TexId);
  glBindTexture(GL_TEXTURE_2D, RP5b_RndTextures[RP5b_RndTexturesSize].TexId);

  glTexStorage2D(GL_TEXTURE_2D, 1, GLType, W, H);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glBindTexture(GL_TEXTURE_2D, 0);

  /* Add to stock */
  RP5b_RndTextures[RP5b_RndTexturesSize].W = W;
  RP5b_RndTextures[RP5b_RndTexturesSize].H = H;
  strncpy(RP5b_RndTextures[RP5b_RndTexturesSize].Name, Name, RP5b_STR_MAX - 1);
  return RP5b_RndTexturesSize++;
} /* End of 'RP5b_RndTexAddFmt' function */

/* END OF 'rndtex.c' FILE */