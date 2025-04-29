/* FILE NAME: rnddata.c
 * PROGRAMMER: RP5b
 * LAST UPDATE: 08.03.2023
 * PURPOSE: 3D animation project.
 *          Rendering data handle module.
 */

#include "anim/rnd/rnd.h"

HWND RP5b_hRndWnd;                    /* Work window handle */
HDC RP5b_hRndDC;                      /* Work window device context  */
HGLRC RP5b_hRndGLRC;                  /* OpenGL rendering context handle */
INT RP5b_RndFrameW, RP5b_RndFrameH;   /* Render frame size */

FLT
  RP5b_RndProjSize,     /* Project plane fit square */
  RP5b_RndProjDist,     /* Distance to project plane from viewer (near) */
  RP5b_RndProjFarClip;  /* Distance to project far clip plane (far) */

MATR
  RP5b_RndMatrView, /* View coordinate system matrix */
  RP5b_RndMatrProj, /* Projection coordinate system matrix */
  RP5b_RndMatrVP;   /* Stored (View * Proj) matrix */

VEC3 RP5b_RndCamLoc, /* Camera location */
  RP5b_RndCamAt,     /* Camera looking direction */
  RP5b_RndCamUp,     /* Camera up direction */
  RP5b_RndCamDir,    /* Camera direction */
  RP5b_RndCamRight;  /* Camera right reference */

INT RP5b_RndUBOCamera; /* Camera UBO */
/* END OF 'rnddata.c' FILE */