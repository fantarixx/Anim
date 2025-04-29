/* FILE NAME: anim.c
 * PROGRAMMER: RP5b
 * LAST UPDATE: 10.03.2023
 * PURPOSE: 3D animation project.
 *          Animation handle module.
 */

#include "anim/anim.h"

/* global animation context store data */
rp5bANIM RP5b_Anim;

/* Animation object adding function.
 * ARGUMENTS:
 *  - Pointer to animation object:
 *      UNIT *Uni;
 * RETURNS: None.
 */
VOID RP5b_AnimUnitAdd( rp5bUNIT *Uni )
{
  if (RP5b_Anim.NumOfUnits < RP5b_MAX_UNITS)
    RP5b_Anim.Units[RP5b_Anim.NumOfUnits++] = Uni, Uni->Init(Uni, &RP5b_Anim);
} /* End of 'AnimUnitAdd' function */

/* Animation initialization function.
 * ARGUMENTS:
 *  - Window handle:
 *      HWND hWnd;
 * RETURNS:
 *   (BOOL) - true if initialization was correct else - false.
 */
BOOL RP5b_AnimInit( HWND hWnd )
{
  memset(&RP5b_Anim, 0, sizeof(rp5bANIM));

  RP5b_AnimInputInit();
  RP5b_Anim.hWnd = hWnd;
  if (!RP5b_RndInit(hWnd))
    return FALSE;
  RP5b_Anim.hDC = RP5b_hRndDC;
  RP5b_Anim.H = RP5b_RndFrameH;
  RP5b_Anim.W = RP5b_RndFrameW;
  RP5b_AnimTimerInit();

  return TRUE;
} /* End of 'RP5b_AnimInit' function */

/* Animation deinitialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID RP5b_AnimClose( VOID )
{
  INT i;

  for (i = 0; i < RP5b_Anim.NumOfUnits; i++)
  {
    RP5b_Anim.Units[i]->Close(RP5b_Anim.Units[i], &RP5b_Anim);
    free(RP5b_Anim.Units[i]);
  }
  RP5b_RndClose();
  memset(&RP5b_Anim, 0, sizeof(rp5bANIM));

} /* End of 'RP5b_AnimClose' function */

/* Frame building function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID RP5b_AnimRender( VOID )
{
  INT i;

  /* Timer request */
  RP5b_AnimTimerResponse();

  /* Device request */
  RP5b_AnimInputResponse();

  for (i = 0; i < RP5b_Anim.NumOfUnits; i++)
    RP5b_Anim.Units[i]->Response(RP5b_Anim.Units[i], &RP5b_Anim);

  RP5b_RndStart();
  for (i = 0; i < RP5b_Anim.NumOfUnits; i++)
    RP5b_Anim.Units[i]->Render(RP5b_Anim.Units[i], &RP5b_Anim);
  RP5b_RndEnd();

  /*for (i = 0; i < RP5b_Anim.NumOfUnits; i++)
    RP5b_Anim.Units[i]->DefRender(RP5b_Anim.Units[i], &RP5b_Anim);
  */
} /* End of 'RP5b_AnimRender' function */

/* Frame changing function.
 * ARGUMENTS:
 *  - Screen sizes:
 *      INT W, H;
 * RETURNS: None.
 */
VOID RP5b_AnimResize( INT W, INT H )
{
  RP5b_Anim.H = H;
  RP5b_Anim.W = W;
  RP5b_RndResize(W, H);

  RP5b_AnimRender();
} /* End of 'RP5b_AnimResize' function */

/* Frame coping function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID RP5b_AnimCopyFrame( VOID )
{
  RP5b_RndCopyFrame();
} /* End of 'RP5b_RndCopyFrame' function */

/* Exit from animation function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID RP5b_AnimDoExit( VOID )
{
  static BOOL IsFinalizeStart = FALSE;

  if (IsFinalizeStart)
    return;
  IsFinalizeStart = TRUE;
  if (MessageBox(RP5b_Anim.hWnd, "Are you sure want to exit?",
       "Exit", MB_OKCANCEL | MB_ICONQUESTION | MB_DEFBUTTON2) != IDOK)
  {
    IsFinalizeStart = FALSE;
    return;
  }
  PostMessage(RP5b_Anim.hWnd, WM_DESTROY, 0, 0);
} /* End of 'RP5b_AnimDoExit' function */

/* Flip full screen function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID RP5b_AnimFlipFullScreen( VOID )
{
  static BOOL IsFullScreen = FALSE; /* store current mode */
  static RECT SaveRC;               /* save old window size */

  if (!IsFullScreen)
  {
    HMONITOR hMon;
    MONITORINFOEX moninfo;
    RECT rc;

    IsFullScreen = TRUE;

    /* Save old window size and position */
    GetWindowRect(RP5b_Anim.hWnd, &SaveRC);

    /* Get closest monitor */
    hMon = MonitorFromWindow(RP5b_Anim.hWnd, MONITOR_DEFAULTTONEAREST);
    moninfo.cbSize = sizeof(moninfo);
    GetMonitorInfo(hMon, (MONITORINFO *)&moninfo);

    rc = moninfo.rcMonitor;
    AdjustWindowRect(&rc, GetWindowLong(RP5b_Anim.hWnd, GWL_STYLE), FALSE);


    /* Restore window size and position */
    SetWindowPos(RP5b_Anim.hWnd, HWND_TOP,
      rc.left, rc.top,
      rc.right - rc.left, rc.bottom - rc.top,
      SWP_NOOWNERZORDER);
  }
  else
  {
    IsFullScreen = FALSE;

    /* Restore window size and position */
    SetWindowPos(RP5b_Anim.hWnd, HWND_NOTOPMOST,
      SaveRC.left, SaveRC.top,
      SaveRC.right - SaveRC.left, SaveRC.bottom - SaveRC.top,
      SWP_NOOWNERZORDER);
  }
} /* End of 'RP5b_AnimFlipFullScreen' function */

/* END OF 'anim.c' FILE */