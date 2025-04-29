/* FILE NAME: u_cow.c
 * PROGRAMMER: RP5b
 * LAST UPDATE: 13.03.2023
 * PURPOSE: 3D animation project.
 *          Cow unit declaration module.
 */

#include "units.h"

/* Cow special type */
typedef struct
{
  RP5b_UNIT_BASE_FIELDS;   /* Unit functions */
  rp5bPRIM Cow;       /* Position */
  VEC3 Pos;            /* Object */
} rp5bUNIT_COW;

/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       rp5bUNIT_COW *Uni;
 *   - animation context:
 *       rp5bANIM *Ani;
 * RETURNS: None.
 */
static VOID RP5b_Init( rp5bUNIT_COW *Uni, rp5bANIM *Ani )
{
  Uni->Pos = Vec3Set(0, 0, 2);
  RP5b_RndPrimLoad(&Uni->Cow, "bin/models/cow.obj");

  if (Uni->Cow.NumOfElements > 0)
  {
    VEC3 B = VecSubVec(Uni->Cow.MaxBB, Uni->Cow.MinBB);
    MATR m = MatrTranslate(VecNeg(Uni->Cow.MaxBB));
    FLT sc = B.X;

    if (sc < B.Y)
      sc = B.Y;
    if (sc < B.Z)
      sc = B.Z;
    m = MatrMulMatr3(m, MatrScale(Vec3Set1(20 / sc)), MatrTranslate(Vec3Set(-20, 0, 0)));
    Uni->Cow.Trans = m;
    Uni->Cow.InstanceCnt = 0;
  }
} /* End of 'RP5b_Init' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       rp5bUNIT_COW *Uni;
 *   - animation context:
 *       rp5bANIM *Ani;
 * RETURNS: None.
 */

static VOID RP5b_Close( rp5bUNIT_COW *Uni, rp5bANIM *Ani )
{
  RP5b_RndPrimFree(&Uni->Cow);
} /* End of 'RP5b_Close' function */

/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       rp5bUNIT_COW *Uni;
 *   - animation context:
 *       rp5bANIM *Ani;
 * RETURNS: None.
 */
static VOID RP5b_Render( rp5bUNIT_COW *Uni, rp5bANIM *Ani )
{
  RP5b_RndPrimDraw(&Uni->Cow, MatrTranslate(Vec3Set(Uni->Pos.X, Uni->Pos.Y, Uni->Pos.Z)));
} /* End of 'RP5b_Render' function */

/* Unit deffered render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       rp5bUNIT *Uni;
 *   - animation context:
 *       rp5bANIM *Ani;
 * RETURNS: None.
 */
static VOID RP5b_UnitDefRender( rp5bUNIT_COW *Uni, rp5bANIM *Ani )
{
} /* End of 'RP5b_UnitDefRender' function */

/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       rp5bUNIT_COW *Uni;
 *   - animation context:
 *       rp5bANIM *Ani;
 * RETURNS: None.
 */
static VOID RP5b_UnitResponse( rp5bUNIT_COW *Uni, rp5bANIM *Ani )
{
  if (!Ani->IsPause)
    Uni->Pos.Y = sin(Ani->Time * 2.5) - 0.9;
} /* End of 'RP5b_UnitResponse' function */

/* Unit creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (rp5bUNIT *) pointer to created unit.
 */
rp5bUNIT * RP5b_UnitCowCreate( VOID )
{
  rp5bUNIT *Uni;

  if ((Uni = RP5b_AnimUnitCreate(sizeof(rp5bUNIT_COW))) == NULL)
    return NULL;

  /* Setup unit methods */
  Uni->Init = (VOID *)RP5b_Init;
  Uni->Close = (VOID *)RP5b_Close;
  Uni->Response = (VOID *)RP5b_UnitResponse;
  Uni->Render = (VOID *)RP5b_Render;
  Uni->DefRender = (VOID *)RP5b_UnitDefRender;

  return Uni;
} /* End of 'RP5b_UnitCowCreate' function */

/* END OF 'u_cow.c' FILE */