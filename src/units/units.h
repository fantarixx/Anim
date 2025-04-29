/* FILE NAME: units.h
 * PROGRAMMER: RP5b
 * LAST UPDATE: 13.03.2023
 * PURPOSE: 3D animation project.
 *          Animation objects declaration module.
 */

#ifndef __rp5b_h_
#define __rp5b_h_

#include "src/anim/anim.h"

/* Cow creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (rp5bUNIT *) pointer to created unit.
 */
rp5bUNIT * RP5b_UnitCowCreate( VOID );

/* Unit ball creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (rp5bUNIT *) pointer to created unit.
 */
rp5bUNIT * RP5b_UnitCreateBall( VOID );

/* G3DM Romeo creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (rp5bUNIT *) pointer to created unit.
 */
rp5bUNIT * RP5b_UnitCreateRomeo( VOID );

/* Unit creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (rp5bUNIT *) pointer to created unit.
 */
rp5bUNIT * RP5b_UnitCtrlCreate( VOID );

/* Unit creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (rp5bUNIT *) pointer to created unit.
 */
rp5bUNIT * RP5b_UnitCreateSky( VOID );

/* Unit creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (rp5bUNIT *) pointer to created unit.
 */
rp5bUNIT * RP5b_UnitCreateMap( VOID );

/* Unit creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (rp5bUNIT *) pointer to created unit.
 */
rp5bUNIT * RP5b_UnitCreateG3DM( VOID );

/* Unit creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (rp5bUNIT *) pointer to created unit.
 */
rp5bUNIT * RP5b_UnitCreateSmoke( VOID );

#endif /* __units_h_ */

/* END OF 'units.h' FILE */