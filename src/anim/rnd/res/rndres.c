/* FILE NAME: rndres.c
 * PROGRAMMER: RP5b
 * LAST UPDATE: 16.02.2023
 * PURPOSE: 3D animation project.
 *          Resourses handle module.
 */

#include <anim/rnd/res/rndres.h>

/* Resourses storages initialize function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID RP5b_RndResInit( VOID )
{
  RP5b_RndShdInit();
  RP5b_RndTexInit();
  RP5b_RndMtlInit();
  RP5b_RndFntInit();
  RP5b_RndUBOInit();
} /* End of 'RP5b_RndResInit' function */

/* Resourses storages deinitialize function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID RP5b_RndResClose( VOID )
{
  RP5b_RndUBOClose();
  RP5b_RndFntClose();
  RP5b_RndMtlClose();
  RP5b_RndTexClose();
  RP5b_RndShdClose();
} /* End of 'RP5b_RndResClose' function */

/* END OF 'rndres.c' FILE */