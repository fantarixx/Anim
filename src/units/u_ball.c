/* FILE NAME: u_ball.c
 * PROGRAMMER: RP5b
 * LAST UPDATE: 13.03.2023
 * PURPOSE: 3D animation project.
 *          Ball unit declaration module.
 */

#include "units.h"

/* Ball special type */
typedef struct
{
  RP5b_UNIT_BASE_FIELDS; /* Unit functions */
  VEC3 Pos;          /* Position */
  rp5bPRIM Ball;    /* Object */
} rp5bUNIT_BALL;

/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       rp5bUNIT_BALL *Uni;
 *   - animation context:
 *       rp5bANIM *Ani;
 * RETURNS: None.
 */
static VOID RP5b_UnitInit( rp5bUNIT_BALL *Uni, rp5bANIM *Ani )
{
  rp5bGRID G;

  RP5b_RndGridCreate(&G, 20, 20);
  RP5b_RndGridCreateSphere(&G, 1, G.W, G.H);
  RP5b_RndPrimFromGrid(&Uni->Ball, &G);
  Uni->Pos = Vec3Set(-4, 1, 0);
  Uni->Ball.InstanceCnt = 0;
  RP5b_RndGridFree(&G);
} /* End of 'RP5b_UnitInit' function */

/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       rp5bUNIT_BALL *Uni;
 *   - animation context:
 *       rp5bANIM *Ani;
 * RETURNS: None.
 */
static VOID RP5b_UnitResponse( rp5bUNIT_BALL *Uni, rp5bANIM *Ani )
{
  if (!Ani->IsPause)
    Uni->Pos.Z = sin(Ani->Time * 10);
} /* End of 'RP5b_UnitResponse' function */

/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       rp5bUNIT_BALL *Uni;
 *   - animation context:
 *       rp5bANIM *Ani;
 * RETURNS: None.
 */
static VOID RP5b_UnitRender( rp5bUNIT_BALL *Uni, rp5bANIM *Ani )
{
  RP5b_RndPrimDraw(&Uni->Ball, MatrTranslate(Vec3Set(Uni->Pos.X, Uni->Pos.Y, Uni->Pos.Z)));
} /* End of 'RP5b_UnitRender' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       rp5bUNIT_BALL *Uni;
 *   - animation context:
 *       rp5bANIM *Ani;
 * RETURNS: None.
 */
static VOID RP5b_UnitClose( rp5bUNIT_BALL *Uni, rp5bANIM *Ani )
{
  RP5b_RndPrimFree(&Uni->Ball);
} /* End of 'RP5b_Close' function */

/* Unit deffered render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       rp5bUNIT *Uni;
 *   - animation context:
 *       rp5bANIM *Ani;
 * RETURNS: None.
 */
static VOID RP5b_UnitDefRender( rp5bUNIT_BALL *Uni, rp5bANIM *Ani )
{
} /* End of 'RP5b_UnitDefRender' function */

/* Unit creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (rp5bUNIT *) pointer to created unit.
 */
rp5bUNIT * RP5b_UnitCreateBall( VOID )
{
  rp5bUNIT *Uni;

  if ((Uni = RP5b_AnimUnitCreate(sizeof(rp5bUNIT_BALL))) == NULL)
    return NULL;

  /* Setup unit methods */
  Uni->Init = (VOID *)RP5b_UnitInit;
  Uni->Close = (VOID *)RP5b_UnitClose;
  Uni->Response = (VOID *)RP5b_UnitResponse;
  Uni->Render = (VOID *)RP5b_UnitRender;
  Uni->DefRender = (VOID *)RP5b_UnitDefRender;

  return Uni;
} /* End of 'RP5b_UnitCreateBall' function */

/* END OF 'u_ball.c' FILE */