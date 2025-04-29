/* FILE NAME: units.c
 * PROGRAMMER: RP5b
 * LAST UPDATE: 10.03.2023
 * PURPOSE: 3D animation project.
 *          Units handle module.
 */

#include "anim/anim.h"

/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       rp5bUNIT *Uni;
 *   - animation context:
 *       rp5bANIM *Ani;
 * RETURNS: None.
 */
static VOID RP5b_UnitInit( rp5bUNIT *Uni, rp5bANIM *Ani )
{
} /* End of 'RP5b_UnitInit' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       rp5bUNIT *Uni;
 *   - animation context:
 *       rp5bANIM *Ani;
 * RETURNS: None.
 */
static VOID RP5b_UnitClose( rp5bUNIT *Uni, rp5bANIM *Ani )
{
} /* End of 'RP5b_UnitClose' function */
 
/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       rp5bUNIT *Uni;
 *   - animation context:
 *       rp5bANIM *Ani;
 * RETURNS: None.
 */
static VOID RP5b_UnitResponse( rp5bUNIT *Uni, rp5bANIM *Ani )
{
} /* End of 'RP5b_UnitResponse' function */

/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       rp5bUNIT *Uni;
 *   - animation context:
 *       rp5bANIM *Ani;
 * RETURNS: None.
 */
static VOID RP5b_UnitRender( rp5bUNIT *Uni, rp5bANIM *Ani )
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
static VOID RP5b_UnitDefRender( rp5bUNIT *Uni, rp5bANIM *Ani )
{
} /* End of 'RP5b_UnitDefRender' function */

/* Unit creation function.
 * ARGUMENTS:
 *   - unit structure size in bytes:
 *       INT Size;
 * RETURNS:
 *   (rp5bUNIT *) pointer to created unit.
 */
rp5bUNIT * RP5b_AnimUnitCreate( INT Size )
{
  rp5bUNIT *Uni;

  /* Memory allocation */
  if (Size < sizeof(rp5bUNIT) || (Uni = malloc(Size)) == NULL)
    return NULL;

  /* Setup unit methods */
  Uni->Init = RP5b_UnitInit;
  Uni->Close = RP5b_UnitClose;
  Uni->Response = RP5b_UnitResponse;
  Uni->Render = RP5b_UnitRender;
  Uni->DefRender = RP5b_UnitDefRender;

  return Uni;
} /* End of 'RP5b_AnimUnitCreate' function */

/* END OF 'units.c' FILE */