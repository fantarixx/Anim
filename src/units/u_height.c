/* FILE NAME: u_height.c
 * PROGRAMMER: RP5b
 * LAST UPDATE: 13.03.2023
 * PURPOSE: 3D animation project.
 *          Higher map unit declaration module.
 */

#include "units.h"

/* Map special type */
typedef struct
{
  RP5b_UNIT_BASE_FIELDS; /* Unit functions */
  VEC3 Pos;          /* Position */
  rp5bPRIM Map;    /* Object */
} rp5bUNIT_MAP;

/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       rp5bUNIT_MAP *Uni;
 *   - animation context:
 *       rp5bANIM *Ani;
 * RETURNS: None.
 */
static VOID RP5b_UnitInit( rp5bUNIT_MAP *Uni, rp5bANIM *Ani )
{
  INT x, y;
  rp5bMATERIAL Mtl;
  rp5bGRID G;
  HBITMAP hBm;
  BITMAP bm;

  if ((hBm = LoadImage(NULL, "bin/heights/hf.bmp", IMAGE_BITMAP, 0, 0,
    LR_LOADFROMFILE | LR_CREATEDIBSECTION)) != NULL)
  {
    GetObject(hBm, sizeof(bm), &bm);

    if (RP5b_RndGridCreate(&G, bm.bmWidth, bm.bmHeight) && (bm.bmBitsPixel == 8 || bm.bmBitsPixel == 24))
    {
      INT H = 100;
      BYTE *Bits = bm.bmBits;

      for (y = 0; y < G.H; y++)
        for (x = 0; x < G.W; x++)
        {
          INT hgt = Bits[y * bm.bmWidthBytes + x * (bm.bmBitsPixel / 8)];

          G.V[y * G.W + x].P = Vec3Set(H * x / (G.W - 1.0) - H / 2, 14 * hgt / 255.0, H * (1 - y / (G.H - 1.0)) - H / 2);
        }
        RP5b_RndPrimEvalBB(&Uni->Map, G.V, G.H * G.W);
        if (Uni->Map.NumOfElements > 0)
        {
          VEC3 B = VecSubVec(Uni->Map.MaxBB, Uni->Map.MinBB);
          MATR m = MatrTranslate(VecNeg(Uni->Map.MaxBB));
          FLT sc = B.X;

          if (sc < B.Y)
            sc = B.Y;
          if (sc < B.Z)
            sc = B.Z;
          m = MatrMulMatr3(m, MatrScale(Vec3Set1(20 / sc)), MatrTranslate(Vec3Set(-20, 0, 0)));
          Uni->Map.Trans = m;
        }
        RP5b_RndPrimFromGrid(&Uni->Map, &G);
        Uni->Pos = Vec3Set(0, -3, 0);

        RP5b_RndGridFree(&G);
    }
  }

  Mtl = RP5b_RndMtlGetDef();
  strncpy(Mtl.Name, "height", RP5b_STR_MAX - 1);
  Mtl.Tex[0] = RP5b_RndTexAddFromFile("bin/textures/hftex.bmp");
  Mtl.ShdNo = RP5b_RndShdAdd("height");
  Uni->Map.MtlNo = RP5b_RndMtlAdd(&Mtl);
  Uni->Map.InstanceCnt = 0;
} /* End of 'RP5b_UnitInit' function */

/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       rp5bUNIT_MAP *Uni;
 *   - animation context:
 *       rp5bANIM *Ani;
 * RETURNS: None.
 */
static VOID RP5b_UnitResponse( rp5bUNIT_MAP *Uni, rp5bANIM *Ani )
{
} /* End of 'RP5b_UnitResponse' function */

/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       rp5bUNIT_MAP *Uni;
 *   - animation context:
 *       rp5bANIM *Ani;
 * RETURNS: None.
 */
static VOID RP5b_UnitRender( rp5bUNIT_MAP *Uni, rp5bANIM *Ani )
{
  RP5b_RndPrimDraw(&Uni->Map, MatrTranslate(Vec3Set(Uni->Pos.X, Uni->Pos.Y, Uni->Pos.Z)));
} /* End of 'RP5b_UnitRender' function */

/* Unit deffered render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       rp5bUNIT *Uni;
 *   - animation context:
 *       rp5bANIM *Ani;
 * RETURNS: None.
 */
static VOID RP5b_UnitDefRender( rp5bUNIT_MAP *Uni, rp5bANIM *Ani )
{
} /* End of 'RP5b_UnitDefRender' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       rp5bUNIT_MAP *Uni;
 *   - animation context:
 *       rp5bANIM *Ani;
 * RETURNS: None.
 */
static VOID RP5b_UnitClose( rp5bUNIT_MAP *Uni, rp5bANIM *Ani )
{
  RP5b_RndPrimFree(&Uni->Map);
} /* End of 'RP5b_Close' function */

/* Unit creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (rp5bUNIT *) pointer to created unit.
 */
rp5bUNIT * RP5b_UnitCreateMap( VOID )
{
  rp5bUNIT *Uni;

  if ((Uni = RP5b_AnimUnitCreate(sizeof(rp5bUNIT_MAP))) == NULL)
    return NULL;

  /* Setup unit methods */
  Uni->Init = (VOID *)RP5b_UnitInit;
  Uni->Close = (VOID *)RP5b_UnitClose;
  Uni->Response = (VOID *)RP5b_UnitResponse;
  Uni->Render = (VOID *)RP5b_UnitRender;
  Uni->DefRender = (VOID *)RP5b_UnitDefRender;

  return Uni;
} /* End of 'RP5b_UnitCreateMap' function */

/* END OF 'u_height.c' FILE */