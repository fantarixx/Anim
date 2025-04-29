/* FILE NAME: main.c
 * PROGRAMMER: RP5b
 * LAST UPDATE: 17.03.2023
 * PURPOSE: 3D animation sample project.
 *            WinApi handle module.
 */

#include "src/units/units.h"

/* Window class name */
#define RP5b_WND_CLASS_NAME "My Winter Camp Main Window Class Name"

/* Forward reference */
LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam );

/* The main program function.
 * ARGUMENTS:
 *   - handle of application instance:
 *       HINSTANCE hInstance;
 *   - dummy handle of previous application instance (not used):
 *       HINSTANCE hPrevInstance;
 *   - command line string:
 *       CHAR *CmdLine;
 *   - show window command parameter (see SW_***):
 *       INT CmdShow;
 * RETURNS:
 *   (INT) Error level for operation system (0 for success).
 */
INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    CHAR *CmdLine, INT ShowCmd )
{
  WNDCLASS wc;
  HWND hWnd;
  MSG msg;

  SetDbgMemHooks();

  /* Fill window class description structure */
  wc.style = CS_HREDRAW | CS_VREDRAW;      /* Window class style (see CS_***) */
  wc.cbClsExtra = 0;                       /* Extra class memory size in bytes */
  wc.cbWndExtra = 0;                       /* Extra window memory size in bytes */
  wc.hbrBackground = (HBRUSH)COLOR_WINDOW; /* Background brush */
  wc.hCursor = LoadCursor(NULL, IDC_HAND); /* Cursor handle */
  wc.hIcon = LoadIcon(NULL, IDI_SHIELD);   /* Icon handle */
  wc.lpszMenuName = NULL;                  /* Menu resource name */
  wc.hInstance = hInstance;                /* Instance handle */
  wc.lpfnWndProc = MyWindowFunc;           /* Window message handle functionpointer  */
  wc.lpszClassName = RP5b_WND_CLASS_NAME;       /* Window class name */


  /* Register window class */
  if (!RegisterClass(&wc))
  {
    MessageBox(NULL, "Error register window class", "ERROR",
      MB_OK | MB_ICONERROR);
    return 0;
  }

  /* Window creation */
  hWnd =
    CreateWindow(RP5b_WND_CLASS_NAME,    /* Window class name */
      "Anim",                      /* Window caption */
      WS_OVERLAPPEDWINDOW,          /* Window styles */
      CW_USEDEFAULT, CW_USEDEFAULT,
      CW_USEDEFAULT, CW_USEDEFAULT,
      NULL,                         /* Owner window handle */
      NULL,                         /* Menu handle */
      hInstance,                    /* Instance handle */
      NULL);                        /* Pointer to window extra data */

  /* Show and update window */
  ShowWindow(hWnd, ShowCmd);
  UpdateWindow(hWnd);

  RP5b_AnimUnitAdd(RP5b_UnitCreateSky());
  //RP5b_AnimUnitAdd(RP5b_UnitCowCreate());
  //RP5b_AnimUnitAdd(RP5b_UnitCreateBall());
  RP5b_AnimUnitAdd(RP5b_UnitCreateMap());
  //RP5b_AnimUnitAdd(RP5b_UnitCreateRomeo());
  //RP5b_AnimUnitAdd(RP5b_UnitCreateG3DM());
  RP5b_AnimUnitAdd(RP5b_UnitCreateSmoke());
  RP5b_AnimUnitAdd(RP5b_UnitCtrlCreate());

  /* Main message loop (wait for 'WM_QUIT' message) */
  while (TRUE)
  {
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
      if (msg.message == WM_QUIT)
        break;
      DispatchMessage(&msg);
    }
    else
    {
      RP5b_AnimRender();
      RP5b_AnimCopyFrame();
    }
  }
  return msg.wParam;
} /* End of 'WinMain' function */

/* Window message handle function (CALLBACK version).
 *   - window handle:
 *       HWND hWnd;
 *   - message identifier (see WM_***):
 *       UINT Msg;
 *   - message first parameter ('word' param):
 *       WPARAM wParam;
 *   - message second parameter ('long' param):
 *       LPARAM lParam;
 * RETURNS:
 *   (LRESULT) message return code (depended to Msg type).
 */
LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam )
{
  MINMAXINFO *minmax;
  PAINTSTRUCT ps;
  HDC hDC;

  switch (Msg)
  {
  case WM_GETMINMAXINFO:
    minmax = (MINMAXINFO *)lParam;
    minmax->ptMaxTrackSize.y = GetSystemMetrics(SM_CYMAXTRACK) +
      GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYBORDER) * 2;
    return 0;
  case WM_CREATE:
    SetTimer(hWnd, 47, 2, NULL);
    if (!RP5b_AnimInit(hWnd))
      break;
    return 0;
  case  WM_ERASEBKGND:
    return 1;
  case WM_SIZE:
    RP5b_AnimResize(LOWORD(lParam), HIWORD(lParam));
    RP5b_AnimCopyFrame();
    return 0;
  case WM_TIMER:
    RP5b_AnimRender();
    RP5b_AnimCopyFrame();
    return 0;
  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);
    EndPaint(hWnd, &ps);
    return 0;
  case WM_LBUTTONDOWN:
    SendMessage(hWnd, WM_TIMER, 47, 0);
    return 0;
  case WM_MOUSEWHEEL:
    RP5b_MouseWheel += (SHORT)HIWORD(wParam);
    return 0;
  case WM_DESTROY:
    RP5b_AnimClose();
    KillTimer(hWnd, 47);
    PostQuitMessage(30);
    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
} /* End of 'MyWindowFunc' function */

/* END OF 'main.c' FILE*/