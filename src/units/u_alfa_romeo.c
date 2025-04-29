/* FILE NAME: u_alfa_romeo.c
 * PROGRAMMER: RP5b
 * LAST UPDATE: 13.03.2023
 * PURPOSE: 3D animation project.
 *          Romeo Romeo unit declaration module.
 */

#include "units.h"

/* Romeo Romeo special type */
typedef struct
{
  RP5b_UNIT_BASE_FIELDS;   /* Unit functions */
  VEC3 Pos;                /* Position */
  rp5bPRIM Romeo;          /* Object */
} rp5bUNIT_ROMEO;

/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       rp5bUNIT_ROMEO *Uni;
 *   - animation context:
 *       rp5bANIM *Ani;
 * RETURNS: None.
 */
static VOID RP5b_UnitInit( rp5bUNIT_ROMEO *Uni, rp5bANIM *Ani )
{
  Uni->Pos = Vec3Set(0, 2, 0);
  RP5b_RndPrimLoad(&Uni->Romeo, "bin/models/Romeo_Romeo.obj");

  if (Uni->Romeo.NumOfElements > 0)
  {
    VEC3 B = VecSubVec(Uni->Romeo.MaxBB, Uni->Romeo.MinBB);
    MATR m = MatrTranslate(VecNeg(Uni->Romeo.MaxBB));
    FLT sc = B.X;

    if (sc < B.Y)
      sc = B.Y;
    if (sc < B.Z)
      sc = B.Z;
    m = MatrMulMatr5(m, MatrScale(Vec3Set1(50 / sc)), MatrRotateY(90), MatrRotateZ(90), MatrTranslate(Vec3Set(-50, -10, -40)));
    Uni->Romeo.Trans = m;
    Uni->Romeo.InstanceCnt = 0;
  }
} /* End of 'RP5b_UnitInit' function */

/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       rp5bUNIT_ROMEO *Uni;
 *   - animation context:
 *       rp5bANIM *Ani;
 * RETURNS: None.
 */
static VOID RP5b_UnitResponse( rp5bUNIT_ROMEO *Uni, rp5bANIM *Ani )
{
} /* End of 'RP5b_UnitResponse' function */

/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       rp5bUNIT_ROMEO *Uni;
 *   - animation context:
 *       rp5bANIM *Ani;
 * RETURNS: None.
 */
static VOID RP5b_UnitRender( rp5bUNIT_ROMEO *Uni, rp5bANIM *Ani )
{
  RP5b_RndPrimDraw(&Uni->Romeo, MatrTranslate(Vec3Set(Uni->Pos.X, Uni->Pos.Y, Uni->Pos.Z)));
} /* End of 'RP5b_UnitRender' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       rp5bUNIT_ROMEO *Uni;
 *   - animation context:
 *       rp5bANIM *Ani;
 * RETURNS: None.
 */
static VOID RP5b_Close( rp5bUNIT_ROMEO *Uni, rp5bANIM *Ani )
{
  RP5b_RndPrimFree(&Uni->Romeo);
} /* End of 'RP5b_Close' function */

/* Unit deffered render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       rp5bUNIT *Uni;
 *   - animation context:
 *       rp5bANIM *Ani;
 * RETURNS: None.
 */
static VOID RP5b_UnitDefRender( rp5bUNIT_ROMEO *Uni, rp5bANIM *Ani )
{
} /* End of 'RP5b_UnitDefRender' function */

/* Unit creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (rp5bUNIT *) pointer to created unit.
 */
rp5bUNIT * RP5b_UnitCreateRomeo( VOID )
{
  rp5bUNIT *Uni;

  if ((Uni = RP5b_AnimUnitCreate(sizeof(rp5bUNIT_ROMEO))) == NULL)
    return NULL;

  /* Setup unit methods */
  Uni->Init = (VOID *)RP5b_UnitInit;
  Uni->Close = (VOID *)RP5b_Close;
  Uni->Response = (VOID *)RP5b_UnitResponse;
  Uni->Render = (VOID *)RP5b_UnitRender;
  Uni->DefRender = (VOID *)RP5b_UnitDefRender;

  return Uni;
} /* End of 'RP5b_UnitCreateRomeoRomeo' function */

/* END OF 'u_alfa_romeo.c' FILE */