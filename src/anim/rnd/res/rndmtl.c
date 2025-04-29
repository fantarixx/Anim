/* FILE NAME: rndmtl.c
 * PROGRAMMER: RP5b
 * LAST UPDATE: 03.03.2023
 * PURPOSE: 3D animation project.
 *          Materials handle module.
 */

#include <anim/anim.h>

/* Material stock */
rp5bMATERIAL RP5b_RndMaterials[RP5b_MAX_MATERIALS]; /* Array of materials */
INT RP5b_RndMaterialsSize;                         /* Materials array */

/* Matirial returning function.
 * ARGUMENTS:
 *   - material number:
 *       INT MtlNo;
 * RETURNS:
 *   (rp5bMATERIAL) - current matirial.
 */
rp5bMATERIAL * RP5b_RndMtlGet( INT MtlNo )
{
  return &RP5b_RndMaterials[MtlNo];
} /* End of 'RP5b_RndMtlGet' function */

/* Macking default matirial function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (rp5bMATERIAL) - basic matirial.
 */
rp5bMATERIAL RP5b_RndMtlGetDef( VOID )
{
  rp5bMATERIAL def_mtl =
  {
    "Default",
    {0.1, 0.1, 0.1},
    {0.9, 0.9, 0.9},
    {0.3, 0.3, 0.3},
    30, 1,
    {-1, -1, -1, -1, -1, -1, -1, -1},
    0
  };

  return def_mtl;
} /* End of 'RP5b_RndMtlGetDef' function */

/* Material storage initialize function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID RP5b_RndMtlInit( VOID )
{
  RP5b_RndMaterialsSize = 0;
  RP5b_RndMaterials[RP5b_RndMaterialsSize++] = RP5b_RndMtlGetDef();
} /* End of 'RP5b_RndMtlInit' function */

/* Material storage deinitialize function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID RP5b_RndMtlClose( VOID )
{
  RP5b_RndMaterialsSize = 0;
} /* End of 'RP5b_RndMtlClose' function */

/* Material adding function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (INT) array numbers material.
 */
INT RP5b_RndMtlAdd( rp5bMATERIAL *Mtl )
{
  rp5bRND_UBO_MATERIAL Buf;

  if (RP5b_RndMaterialsSize >= RP5b_MAX_MATERIALS)
    return -1;

  Buf.KaTrans = Vec4Set3(Mtl->Ka, Mtl->Trans);
  Buf.Kd = Vec4Set3(Mtl->Kd, 0);
  Buf.KsPh = Vec4Set3(Mtl->Ks, Mtl->Ph);
  Buf.TexFlags0123 = Vec4Set(Mtl->Tex[0] != -1, Mtl->Tex[1] != -1,
                             Mtl->Tex[2] != -1, Mtl->Tex[3] != -1);
  Buf.TexFlags4567 = Vec4Set(Mtl->Tex[4] != -1, Mtl->Tex[5] != -1,
                             Mtl->Tex[6] != -1, Mtl->Tex[7] != -1);

  RP5b_RndMaterials[RP5b_RndMaterialsSize] = *Mtl;
  RP5b_RndMaterials[RP5b_RndMaterialsSize].UBONo =
    RP5b_RndUBOCreate(RP5b_RndMaterials[RP5b_RndMaterialsSize].Name, RP5b_RND_UBO_BIND_MATERIAL,
                      sizeof(rp5bRND_UBO_MATERIAL) / 16, &Buf);

  return RP5b_RndMaterialsSize++;
} /* End of 'RP5b_RndMtlAdd' function */

/* Getting shaders program identificator function.
 * ARGUMENTS:
 *   Number of material:
 *     INT MtlNo;
 * RETURNS:
 *   (INT) ProgId from shader.
 */
INT RP5b_RndMtlApply( INT MtlNo )
{
  INT prg, loc, i;
  rp5bMATERIAL *mtl;

  /* Set material pointer */
  if (MtlNo < 0 || MtlNo >= RP5b_RndMaterialsSize)
    MtlNo = 0;
  mtl = &RP5b_RndMaterials[MtlNo];

  /* Set shader program Id */
  prg = mtl->ShdNo;
  if (prg < 0 || prg >= RP5b_RndShadersSize)
    prg = 0;
  prg = RP5b_RndShaders[prg].ProgId;

  glUseProgram(prg);

  if ((loc = glGetUniformLocation(prg, "Time")) != -1)
    glUniform1f(loc, RP5b_Anim.Time);
  if ((loc = glGetUniformLocation(prg, "GlobalTime")) != -1)
    glUniform1f(loc, RP5b_Anim.GlobalTime);

  RP5b_RndUBOApply(mtl->UBONo);
  
  for (i = 0; i < 8; i++)
    if (mtl->Tex[i] != -1)
    {
      glActiveTexture(GL_TEXTURE0 + i);
      glBindTexture(GL_TEXTURE_2D, RP5b_RndTextures[mtl->Tex[i]].TexId);
    }
  return prg;
} /* End of 'RP5b_RndMtlApply' function */

/* END OF 'rndmtl.c' FILE */