/* FILE NAME: u_g3dm.c
 * PROGRAMMER: RP5b
 * LAST UPDATE: 17.03.2023
 * PURPOSE: 3D animation project.
 *          G3DM unit declaration module.
 */

#include "units.h"

/* G3DM special type */
typedef struct
{
  RP5b_UNIT_BASE_FIELDS;  /* Unit functions */
  VEC3 Pos;           /* Object positions */
  rp5bPRIMS G3DM;  /* Object */
} rp5bUNIT_G3DM;

/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       rp5bUNIT_G3DM *Uni;
 *   - animation context:
 *       rp5bANIM *Ani;
 * RETURNS: None.
 */
static VOID RP5b_UnitInit( rp5bUNIT_G3DM *Uni, rp5bANIM *Ani )
{
  Uni->Pos = Vec3Set(0, 4, 2);
  RP5b_RndPrimsLoad(&Uni->G3DM, "bin/models/x6.g3dm");
  Uni->G3DM.Prims->InstanceCnt = 0;
} /* End of 'RP5b_UnitInit' function */

/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       rp5bUNIT_G3DM *Uni;
 *   - animation context:
 *       rp5bANIM *Ani;
 * RETURNS: None.
 */
static VOID RP5b_UnitResponse( rp5bUNIT_G3DM *Uni, rp5bANIM *Ani )
{
} /* End of 'RP5b_UnitResponse' function */

/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       rp5bUNIT_G3DM *Uni;
 *   - animation context:
 *       rp5bANIM *Ani;
 * RETURNS: None.
 */
static VOID RP5b_UnitRender( rp5bUNIT_G3DM *Uni, rp5bANIM *Ani )
{
  RP5b_RndPrimsDraw(&Uni->G3DM, MatrTranslate(Vec3Set(Uni->Pos.X, Uni->Pos.Y, Uni->Pos.Z)));
} /* End of 'RP5b_UnitRender' function */

/* Unit deffered render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       rp5bUNIT *Uni;
 *   - animation context:
 *       rp5bANIM *Ani;
 * RETURNS: None.
 */
static VOID RP5b_UnitDefRender( rp5bUNIT_G3DM *Uni, rp5bANIM *Ani )
{
} /* End of 'RP5b_UnitDefRender' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       rp5bUNIT_G3DM *Uni;
 *   - animation context:
 *       rp5bANIM *Ani;
 * RETURNS: None.
 */
static VOID RP5b_UnitClose( rp5bUNIT_G3DM *Uni, rp5bANIM *Ani )
{
  RP5b_RndPrimsFree(&Uni->G3DM);
} /* End of 'RP5b_Close' function */

/* Unit creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (rp5bUNIT *) pointer to created unit.
 */
rp5bUNIT * RP5b_UnitCreateG3DM( VOID )
{
  rp5bUNIT *Uni;

  if ((Uni = RP5b_AnimUnitCreate(sizeof(rp5bUNIT_G3DM))) == NULL)
    return NULL;

  /* Setup unit methods */
  Uni->Init = (VOID *)RP5b_UnitInit;
  Uni->Close = (VOID *)RP5b_UnitClose;
  Uni->Response = (VOID *)RP5b_UnitResponse;
  Uni->Render = (VOID *)RP5b_UnitRender;
  Uni->DefRender = (VOID *)RP5b_UnitDefRender;

  return Uni;
} /* End of 'RP5b_UnitCreateG3DM' function */

/* END OF 'u_g3dm.c' FILE */