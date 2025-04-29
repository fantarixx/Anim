/* FILE NAME: anim.h
 * PROGRAMMER: RP5b
 * LAST UPDATE: 13.03.2023
 * PURPOSE: 3D animation project.
 *          Animation declaration module.
 */

#ifndef __anim_h_
#define __anim_h_

#include "rnd/rnd.h"

/***
 * Main animation support.
 ***/

/* Maximum of units */
#define RP5b_MAX_UNITS 3000

/* Unit functions */
#define RP5b_UNIT_BASE_FIELDS \
  VOID (*Init)( rp5bUNIT *Uni, rp5bANIM *Ani );      \
  VOID (*Close)( rp5bUNIT *Uni, rp5bANIM *Ani );     \
  VOID (*Response)( rp5bUNIT *Uni, rp5bANIM *Ani );  \
  VOID (*Render)( rp5bUNIT *Uni, rp5bANIM *Ani );    \
  VOID (*DefRender)( rp5bUNIT *Uni, rp5bANIM *Ani )

/* Types forward declarations */
typedef struct tagrp5bUNIT rp5bUNIT;

/* Animation type */
typedef struct tagrp5bANIM
{
  HWND hWnd;                       /* window */
  HDC hDC;                         /* memory context */
  INT W, H;                        /* wondos size */

  rp5bUNIT *Units[RP5b_MAX_UNITS]; /* Animation objects array */
  INT NumOfUnits;                  /* Current amount of animation objects */

  DBL
    GlobalTime, GlobalDeltaTime,   /* Global time and interframe interval */
    Time, DeltaTime,               /* Time with pause and interframe interval */
    FPS;                           /* Frames per second value */
  BOOL
    IsPause;                       /* Pause flag */

  /* Keyboard handle data */
  BYTE
    Keys[256],                     /* Keyboard state (true if key pressed) */
    KeysClick[256];                /* Key 'one-click' info */

  /* Mouse handle data */
  INT
    Mx, My, Mz,                    /* Absolute mouse coordinates */
    Mdx, Mdy, Mdz;                 /* Relative mouse coordinates */

  /* Joystick handle data */
  FLT
    JX, JY, JZ, JR;                /* Joystick axes */
  BYTE
    JBut[32], JButOld[32], JButClick[32];       /* Joystick buttons */
  INT JPov;

} rp5bANIM;

/* Unit struct */
typedef struct tagrp5bUNIT
{
  RP5b_UNIT_BASE_FIELDS;
};

/* Mouse wheel counter */

/* global animation context store data */
extern rp5bANIM RP5b_Anim;

/* Animation object adding function.
 * ARGUMENTS:
 *  - Pointer to animation object:
 *      UNIT *Uni;
 * RETURNS: None.
 */
VOID RP5b_AnimUnitAdd( rp5bUNIT *Uni );

/* Unit creation function.
 * ARGUMENTS:
 *   - unit structure size in bytes:
 *       INT Size;
 * RETURNS:
 *   (rp5bUNIT *) pointer to created unit.
 */
rp5bUNIT * RP5b_AnimUnitCreate( INT Size );

/* Animation initialization function.
 * ARGUMENTS:
 *  - Window handle:
 *      HWND hWnd;
 * RETURNS:
 *   (BOOL) - true if initialization was correct else - false.
 */
BOOL RP5b_AnimInit( HWND hWnd );

/* Animation deinitialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID RP5b_AnimClose( VOID );

/* Frame building function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID RP5b_AnimRender( VOID );

/* Frame changing function.
 * ARGUMENTS:
 *  - Screen sizes:
 *      INT W, H;
 * RETURNS: None.
 */
VOID RP5b_AnimResize( INT W, INT H );

/* Frame coping function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID RP5b_AnimCopyFrame( VOID );

/* Exit from animation function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID RP5b_AnimDoExit( VOID );

/* Flip full screen function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID RP5b_AnimFlipFullScreen( VOID );

/*** Timer ***/
/* Timer initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID RP5b_AnimTimerInit( VOID );

/* Timer update function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID RP5b_AnimTimerResponse( VOID );

extern INT RP5b_MouseWheel; /* Mouse wheel global data */

/* Input initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID RP5b_AnimInputInit( VOID );

/* Input responsing function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID RP5b_AnimInputResponse( VOID );


#endif /* __anim_h_ */

/* END OF 'anim.h' FILE */