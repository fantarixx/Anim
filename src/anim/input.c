/* FILE NAME: input.c
 * PROGRAMMER: RP5b
 * LAST UPDATE: 16.02.2023
 * PURPOSE: 3D animation project.
 *          Input devices handle module.
 */

#include "anim/anim.h"
#include <string.h>
#include <mmsystem.h>

#pragma comment(lib, "winmm")


/***
 * Keyboard request.
 ***/
static BYTE RP5b_OldKeys[256]; /* Old status of keyboard */

/* Keyboard responsing function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
static VOID RP5b_AnimKeyboardResponse( VOID )
{
  INT i;

  GetKeyboardState(RP5b_Anim.Keys);

  for (i = 0; i < 256; i++)
  {
    RP5b_Anim.Keys[i] >>= 7;
    RP5b_Anim.KeysClick[i] = RP5b_Anim.Keys[i] && !RP5b_OldKeys[i];
  }

  memcpy(RP5b_OldKeys, RP5b_Anim.Keys, 256);
} /* End of 'RP5b_AnimKeyboardResponse' function */

/* Keyboard initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
static VOID RP5b_AnimKeyboardInit( VOID )
{
  INT i;

  GetKeyboardState(RP5b_Anim.Keys);
  for (i = 0; i < 256; i++)
    RP5b_Anim.Keys[i] >>= 7;
  memcpy(RP5b_OldKeys, RP5b_Anim.Keys, 256);
} /* End of 'RP5b_AnimKeyboardInit' function */

/***
 * Mouse request.
 ***/
INT RP5b_MouseWheel; /* Mouse wheel global data */

/* Mouse initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
static VOID RP5b_AnimMouseInit( VOID )
{
  POINT pt;

  /* Obtain position */
  GetCursorPos(&pt);
  ScreenToClient(RP5b_Anim.hWnd, &pt);

  /* Delta (relative) values */
  RP5b_Anim.Mdx = 0;
  RP5b_Anim.Mdy = 0;

  /* Absolute value */
  RP5b_Anim.Mx = pt.x;
  RP5b_Anim.My = pt.y;

  /* Wheel (Z) */
  RP5b_MouseWheel = RP5b_Anim.Mdz = RP5b_Anim.Mz = 0;
} /* End of 'RP5b_AnimMouseInit' function */

/* Mouse responsing function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
static VOID RP5b_AnimMouseResponse( VOID )
{
  POINT pt;

  GetCursorPos(&pt);
  ScreenToClient(RP5b_Anim.hWnd, &pt);

  RP5b_Anim.Mdx = pt.x - RP5b_Anim.Mx;
  RP5b_Anim.Mdy = pt.y - RP5b_Anim.My;
  RP5b_Anim.Mdz = RP5b_MouseWheel;

  RP5b_Anim.Mx = pt.x;
  RP5b_Anim.My = pt.y;
  RP5b_Anim.Mz += RP5b_MouseWheel;
  RP5b_MouseWheel = 0;
} /* End of 'RP5b_AnimMouseResponse' function */

/***
 * Joystick request.
 ***/

#define RP5b_GET_JOYSTIC_AXIS(A) \
  (2.0 * (ji.dw ## A ## pos - jc.w ## A ## min) / (jc.w ## A ## max - jc.w ## A ## min) - 1)

/* Joystick initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
static VOID RP5b_AnimJoystickInit( VOID )
{
} /* End of 'RP5b_AnimJoystickInit' function */

/* Joystick responsing function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
static VOID RP5b_AnimJoystickResponse( VOID )
{
  INT i;

  if (joyGetNumDevs() > 0)
  {
    JOYCAPS jc;

    /* Get joystick info */
    if (joyGetDevCaps(JOYSTICKID1, &jc, sizeof(jc)) == JOYERR_NOERROR)
    {
      JOYINFOEX ji;

      ji.dwSize = sizeof(JOYINFOEX);
      ji.dwFlags = JOY_RETURNALL;
      if (joyGetPosEx(JOYSTICKID1, &ji) == JOYERR_NOERROR)
      {
        /* Buttons */
        for (i = 0; i < 32; i++)
        {
          RP5b_Anim.JBut[i] = (ji.dwButtons >> i) & 1;
          RP5b_Anim.JButClick[i] = RP5b_Anim.JBut[i] && !RP5b_Anim.JButOld[i];
          RP5b_Anim.JButOld[i] = RP5b_Anim.JBut[i];
        }
        /* Axes */
        RP5b_Anim.JX = RP5b_GET_JOYSTIC_AXIS(X);
        RP5b_Anim.JY = RP5b_GET_JOYSTIC_AXIS(Y);
        RP5b_Anim.JZ = RP5b_GET_JOYSTIC_AXIS(Z);
        RP5b_Anim.JR = RP5b_GET_JOYSTIC_AXIS(R);
        /* Point of view */ 
        RP5b_Anim.JPov = ji.dwPOV == 0xFFFF ? -1 : ji.dwPOV / 4500;
      }
    }
  }
} /* End of 'RP5b_AnimJoystickResponse' function */

/* Input initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID RP5b_AnimInputInit( VOID )
{
  RP5b_AnimKeyboardInit();
  RP5b_AnimMouseInit();
  RP5b_AnimJoystickInit();
} /* End of 'RP5b_AnimInputInit' function */

/* Input responsing function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID RP5b_AnimInputResponse( VOID )
{
  RP5b_AnimKeyboardResponse();
  RP5b_AnimMouseResponse();
  RP5b_AnimJoystickResponse();
} /* End of 'RP5b_AnimInputResponse' function */

/* END OF 'input.c' FILE */