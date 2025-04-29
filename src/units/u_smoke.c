/* FILE NAME: u_smoke.c
   * PROGRAMMER: RP5b
 * LAST UPDATE: 13.03.2023
 * PURPOSE: 3D animation project.
 *          Smoke unit declaration module.
 */

#include <string.h>

#include "units.h"

/* Smoke special type */
typedef struct
{
  RP5b_UNIT_BASE_FIELDS;  /* Unit functions */
  rp5bPRIM Smoke;    /* Smoke primitive */
  VEC3 Pos;          /* Smoke position */
} rp5bUNIT_SMOKE;

/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       rp5bUNIT_SMOKE *Uni;
 *   - animation context:
 *       rp5bANIM *Ani;
 * RETURNS: None.
 */
static VOID RP5b_UnitInit( rp5bUNIT_SMOKE *Uni, rp5bANIM *Ani )
{
  rp5bVERTEX V[3] = {{{28, 5.8, 1.1}}, {{27.9, 5.8, 1.7}}, {{28.2, 5.8, 1.4}}};
  rp5bMATERIAL Mtl = RP5b_RndMtlGetDef();

  RP5b_RndPrimCreate(&Uni->Smoke, RP5b_RND_PRIM_POINTS, V, 3, NULL, 0);
  strncpy(Mtl.Name, "Smoke", RP5b_STR_MAX - 1);
  Mtl.Tex[0] = RP5b_RndTexAddFromFile("bin/textures/SMOKE.G32");
  Mtl.ShdNo = RP5b_RndShdAdd("smoke");
  Uni->Smoke.MtlNo = RP5b_RndMtlAdd(&Mtl);
  Uni->Smoke.InstanceCnt = 0;
} /* End of 'RP5b_UnitInit' function */

/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       rp5bUNIT_SMOKE *Uni;
 *   - animation context:
 *       rp5bANIM *Ani;
 * RETURNS: None.
 */
static VOID RP5b_UnitResponse( rp5bUNIT_SMOKE *Uni, rp5bANIM *Ani )
{
} /* End of 'RP5b_UnitResponse' function */

/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       rp5bUNIT_SMOKE *Uni;
 *   - animation context:
 *       rp5bANIM *Ani;
 * RETURNS: None.
 */
static VOID RP5b_UnitRender( rp5bUNIT_SMOKE *Uni, rp5bANIM *Ani )
{
} /* End of 'RP5b_UnitRender' function */

/* Unit deffered render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       rp5bUNIT *Uni;
 *   - animation context:
 *       rp5bANIM *Ani;
 * RETURNS: None.
 */
static VOID RP5b_UnitDefRender( rp5bUNIT_SMOKE *Uni, rp5bANIM *Ani )
{
  glDepthMask(FALSE);
  RP5b_RndPrimDraw(&Uni->Smoke, MatrIdentity());
  glDepthMask(TRUE);
} /* End of 'RP5b_UnitDefRender' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       rp5bUNIT_SMOKE *Uni;
 *   - animation context:
 *       rp5bANIM *Ani;
 * RETURNS: None.
 */
static VOID RP5b_UnitClose( rp5bUNIT_SMOKE *Uni, rp5bANIM *Ani )
{
  RP5b_RndPrimFree(&Uni->Smoke);
} /* End of 'RP5b_Close' function */

/* Unit creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (rp5bUNIT *) pointer to created unit.
 */
rp5bUNIT * RP5b_UnitCreateSmoke( VOID )
{
  rp5bUNIT *Uni;

  if ((Uni = RP5b_AnimUnitCreate(sizeof(rp5bUNIT_SMOKE))) == NULL)
    return NULL;

  /* Setup unit methods */
  Uni->Init = (VOID *)RP5b_UnitInit;
  Uni->Close = (VOID *)RP5b_UnitClose;
  Uni->Response = (VOID *)RP5b_UnitResponse;
  Uni->Render = (VOID *)RP5b_UnitRender;
  Uni->DefRender = (VOID *)RP5b_UnitDefRender;

  return Uni;
} /* End of 'RP5b_UnitCreateSmoke' function */

/* END OF 'u_smoke.c' FILE */