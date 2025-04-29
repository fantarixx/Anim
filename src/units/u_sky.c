/* FILE NAME: u_sky.c
   * PROGRAMMER: RP5b
 * LAST UPDATE: 17.03.2023
 * PURPOSE: 3D animation project.
 *          Sky unit declaration module.
 */

#include "units.h"

/* Sky special type */
typedef struct
{
  RP5b_UNIT_BASE_FIELDS; /* Unit functions */
  rp5bPRIM Sky;     /* Object */
} rp5bUNIT_SKY;

/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       rp5bUNIT_SKY *Uni;
 *   - animation context:
 *       rp5bANIM *Ani;
 * RETURNS: None.
 */
static VOID RP5b_UnitInit( rp5bUNIT_SKY *Uni, rp5bANIM *Ani )
{
  rp5bMATERIAL Mtl = RP5b_RndMtlGetDef();

  RP5b_RndPrimCreate(&Uni->Sky, RP5b_RND_PRIM_POINTS, NULL, 1, NULL, 0);
  strncpy(Mtl.Name, "Sky", RP5b_STR_MAX - 1);
  Mtl.Tex[0] = RP5b_RndTexAddFromFile("bin/textures/SeamlessBlueSky.g24");
  Mtl.ShdNo = RP5b_RndShdAdd("sky");
  Uni->Sky.MtlNo = RP5b_RndMtlAdd(&Mtl);
  Uni->Sky.InstanceCnt = 0;
} /* End of 'RP5b_UnitInit' function */

/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       rp5bUNIT_SKY *Uni;
 *   - animation context:
 *       rp5bANIM *Ani;
 * RETURNS: None.
 */
static VOID RP5b_UnitResponse( rp5bUNIT_SKY *Uni, rp5bANIM *Ani )
{
} /* End of 'RP5b_UnitResponse' function */

/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       rp5bUNIT_SKY *Uni;
 *   - animation context:
 *       rp5bANIM *Ani;
 * RETURNS: None.
 */
static VOID RP5b_UnitRender( rp5bUNIT_SKY *Uni, rp5bANIM *Ani )
{
  if (RP5b_RndPass != RP5b_RENDER_PASS_SHADOW)
  {
    glDepthMask(FALSE);
    RP5b_RndPrimDraw(&Uni->Sky, MatrIdentity());
    glDepthMask(TRUE);
  }
} /* End of 'RP5b_UnitRender' function */

/* Unit deffered render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       rp5bUNIT *Uni;
 *   - animation context:
 *       rp5bANIM *Ani;
 * RETURNS: None.
 */
static VOID RP5b_UnitDefRender( rp5bUNIT_SKY *Uni, rp5bANIM *Ani )
{
} /* End of 'RP5b_UnitDefRender' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       rp5bUNIT_SKY *Uni;
 *   - animation context:
 *       rp5bANIM *Ani;
 * RETURNS: None.
 */
static VOID RP5b_UnitClose( rp5bUNIT_SKY *Uni, rp5bANIM *Ani )
{
  RP5b_RndPrimFree(&Uni->Sky);
} /* End of 'RP5b_Close' function */

/* Unit creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (rp5bUNIT *) pointer to created unit.
 */
rp5bUNIT * RP5b_UnitCreateSky( VOID )
{
  rp5bUNIT *Uni;

  if ((Uni = RP5b_AnimUnitCreate(sizeof(rp5bUNIT_SKY))) == NULL)
    return NULL;

  /* Setup unit methods */
  Uni->Init = (VOID *)RP5b_UnitInit;
  Uni->Close = (VOID *)RP5b_UnitClose;
  Uni->Response = (VOID *)RP5b_UnitResponse;
  Uni->Render = (VOID *)RP5b_UnitRender;
  Uni->DefRender = (VOID *)RP5b_UnitDefRender;

  return Uni;
} /* End of 'RP5b_UnitCreateSky' function */

/* END OF 'u_sky.c' FILE */