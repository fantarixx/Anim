/* FILE NAME: rndbase.c
 * PROGRAMMER: RP5b
 * LAST UPDATE: 13.03.2023
 * PURPOSE: 3D animation project.
 *          Rendering system base.
 *          Rendering handle module.
 */

#include "anim/anim.h"

#pragma comment(lib, "opengl32")

/* Camera setting function.
 * ARGUMENTS:
 *   - Approximate directions:
 *       VEC3 Loc, At, Up;
 * RETURNS: None.
 */
VOID RP5b_RndCamSet( VEC3 Loc, VEC3 At, VEC3 Up )
{
  RP5b_RndMatrView = MatrView(Loc, At, Up);
  RP5b_RndMatrVP = MatrMulMatr(RP5b_RndMatrView, RP5b_RndMatrProj);
  RP5b_RndCamLoc = Loc;
  RP5b_RndCamRight = Vec3Set(RP5b_RndMatrView.A[0][0], RP5b_RndMatrView.A[1][0], RP5b_RndMatrView.A[2][0]);
  RP5b_RndCamAt = At;
  RP5b_RndCamUp = Vec3Set(RP5b_RndMatrView.A[0][1], RP5b_RndMatrView.A[1][1], RP5b_RndMatrView.A[2][1]);
  RP5b_RndCamDir = Vec3Set(-RP5b_RndMatrView.A[0][2], -RP5b_RndMatrView.A[1][2], -RP5b_RndMatrView.A[2][2]);
} /* End of 'RP5b_RndCamSet' function */

/* Render base initialization function.
 * ARGUMENTS:
 *   - window handle:
 *       HWND hWnd;
 * RETURNS:
 *   (BOOL) - true if initialization was correct else - false.
 */
BOOL RP5b_RndInit( HWND hWnd )
{
  INT i;
  PIXELFORMATDESCRIPTOR pfd = {0};
  HGLRC hRC;
  INT PixelAttribs[] =
  {
    WGL_DRAW_TO_WINDOW_ARB, TRUE,
    WGL_SUPPORT_OPENGL_ARB, TRUE,
    WGL_DOUBLE_BUFFER_ARB, TRUE,
    WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
    WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
    WGL_COLOR_BITS_ARB, 32,
    WGL_DEPTH_BITS_ARB, 32,
    0
  };
  INT ContextAttribs[] =
  {
    WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
    WGL_CONTEXT_MINOR_VERSION_ARB, 6,
    WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB,
                                  /* WGL_CONTEXT_CORE_PROFILE_BIT_ARB, */
    0
  };
  UINT nums;

  RP5b_hRndWnd = hWnd;

  /* Prepare frame compatible device context */
  RP5b_hRndDC = GetDC(hWnd);

  /* OpenGl init: pixel format setup */
  pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
  pfd.nVersion = 1;
  pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL;
  pfd.cColorBits = 32;
  pfd.cDepthBits = 32;
  i = ChoosePixelFormat(RP5b_hRndDC, &pfd);
  DescribePixelFormat(RP5b_hRndDC, i, sizeof(pfd), &pfd);
  SetPixelFormat(RP5b_hRndDC, i, &pfd);

  /* Rendering context setup */
  RP5b_hRndGLRC = wglCreateContext(RP5b_hRndDC);
  wglMakeCurrent(RP5b_hRndDC, RP5b_hRndGLRC);

  /* Initialize extensions (trough GLEW) */
  if (glewInit() != GLEW_OK)
    return FALSE;

  /* Debug setup */
  #ifndef NDEBUG
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(glDebugOutput, NULL);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE,
      0, NULL, GL_TRUE);
  #endif /* NDEBUG */

  /* Enable a new OpenGL profile support */
  wglChoosePixelFormatARB(RP5b_hRndDC, PixelAttribs, NULL, 1, &i, &nums);
  hRC = wglCreateContextAttribsARB(RP5b_hRndDC, NULL, ContextAttribs);

  wglMakeCurrent(NULL, NULL);
  wglDeleteContext(RP5b_hRndGLRC);

  RP5b_hRndGLRC = hRC;
  wglMakeCurrent(RP5b_hRndDC, RP5b_hRndGLRC);

  /* Render parametrs setup */
  glClearColor(0.30, 0.47, 0.8, 1);
  glEnable(GL_DEPTH_TEST);

  wglSwapIntervalEXT(0);

  glEnable(GL_PRIMITIVE_RESTART);
  glPrimitiveRestartIndex(-1);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  RP5b_RndResInit();

  /* Set default OpenGl parametrs */
  RP5b_RndProjSize = 0.1;
  RP5b_RndProjDist = RP5b_RndProjSize;
  RP5b_RndProjFarClip = 500;
  RP5b_RndFrameW = 47;
  RP5b_RndFrameH = 47;
  RP5b_RndCamSet(Vec3Set1(5), Vec3Set1(0), Vec3Set(0, 1, 0));

  RP5b_RndTargetInit();
  RP5b_RndLightInit();

  RP5b_RndUBOCamera = RP5b_RndUBOCreate("Matrices", RP5b_RND_UBO_BIND_CAMERA, sizeof(rp5bRND_UBO_MATR) / 16, NULL);
  RP5b_RndUBOApply(RP5b_RndUBOCamera);

  return TRUE;
} /* End of 'RP5b_RndInit' function */

/* Render base deleting function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID RP5b_RndClose( VOID )
{
  RP5b_RndLightClose();
  RP5b_RndTargetClose();
  RP5b_RndResClose();
  wglMakeCurrent(NULL, NULL);
  wglDeleteContext(RP5b_hRndGLRC);
  ReleaseDC(RP5b_hRndWnd, RP5b_hRndDC);
} /* End of 'RP5b_RndClose' function */

/* View and world matrix remaking function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
static VOID RP5b_RndProjSet( VOID )
{
  FLT rx, ry;

  rx = ry = RP5b_RndProjSize;

  /* Correct aspect ratio */
  if (RP5b_RndFrameW > RP5b_RndFrameH)
    rx *= (FLT)RP5b_RndFrameW / RP5b_RndFrameH;
  else
    ry *= (FLT)RP5b_RndFrameH / RP5b_RndFrameW;

  RP5b_RndMatrProj =
    MatrFrustum(-rx / 2, rx / 2, -ry / 2, ry / 2,
      RP5b_RndProjDist, RP5b_RndProjFarClip);
  RP5b_RndMatrVP = MatrMulMatr(RP5b_RndMatrView, RP5b_RndMatrProj);
} /* End of 'RP5b_RndProjSet' function */

/* Project resize function.
 * ARGUMENTS:
 *  - Screen sizes:
 *      INT W, H;
 * RETURNS: None.
 */
VOID RP5b_RndResize( INT W, INT H )
{
  /* Size saving */
  RP5b_RndFrameW = W;
  RP5b_RndFrameH = H;

  /* Projection remaking */
  RP5b_RndProjSet();
  RP5b_RndTargetResize(W, H);
} /* End of 'RP5b_RndResize' function */

/* Frame coping function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID RP5b_RndCopyFrame( VOID )
{
  SwapBuffers(RP5b_hRndDC);
} /* End of 'RP5b_RndCopyFrame' function */

/* Render */

/* Frame clearing and start drawing function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID RP5b_RndStart( VOID )
{
  rp5bRND_UBO_MATR CamU;
  INT Modes[2];
  static DBL RP5b_RndReloadTime = 0;

  if (RP5b_Anim.GlobalTime - RP5b_RndReloadTime > 3)
  {
    RP5b_RndReloadTime = RP5b_Anim.GlobalTime;
    RP5b_RndShdUpdate();
  }

  /* Set camera */
  CamU.CamLoc = Vec4Set3(RP5b_RndCamLoc, 0);
  CamU.CamDir = Vec4Set3(RP5b_RndCamDir, 0);
  CamU.CamRight = Vec4Set3(RP5b_RndCamRight, 0);
  CamU.CamUp = Vec4Set3(RP5b_RndCamUp, 0);
  CamU.WHProjDistFar = Vec4Set(RP5b_RndFrameW, RP5b_RndFrameH, RP5b_RndProjDist, RP5b_RndProjFarClip);
  CamU.MatrVP = CamU.MatrWVP = RP5b_RndMatrVP;
  CamU.MatrV = RP5b_RndMatrView;
  CamU.MatrW = CamU.MatrWInv = MatrIdentity();
  CamU.TimeGlobalDeltaGlobal =
    Vec4Set(RP5b_Anim.Time, RP5b_Anim.GlobalTime, RP5b_Anim.DeltaTime, RP5b_Anim.GlobalDeltaTime);
  glGetIntegerv(GL_POLYGON_MODE, Modes);
  CamU.WireframeProjSize = Vec4Set(Modes[0] == GL_LINE, RP5b_RndProjSize, 0, 0);
  CamU.LightColor = Vec4Set3(RP5b_RndLightColor, 0);
  CamU.LightDir = Vec4Set3(RP5b_RndLightDir, 0);
  CamU.LightShadowMatr = RP5b_RndLightShadowMatr;

  RP5b_RndUBOUpdate(RP5b_RndUBOCamera, 0, 0, &CamU);

  RP5b_RndTargetStart();
} /* End of 'RP5b_RndStart' function */

/* Part of render base deleting function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID RP5b_RndEnd( VOID )
{
  RP5b_RndTargetEnd();
} /* End of 'RP5b_RndEnd' function */

/* END OF 'rndbase.c' FILE */