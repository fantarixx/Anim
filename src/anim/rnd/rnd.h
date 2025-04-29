/* FILE NAME: rnd.h
 * PROGRAMMER: RP5b
 * LAST UPDATE: 13.03.2023
 * PURPOSE: 3D animation project.
 *          Rendering system base.
 *          Rendering declaration module.
 */

#ifndef __rnd_h_
#define __rnd_h_

#include "res/rndres.h"

extern HWND RP5b_hRndWnd;                   /* Render work window handle */
extern HDC RP5b_hRndDC;                     /* Render work window device context  */
extern HGLRC RP5b_hRndGLRC;                 /* OpenGL rendering context handle */
extern INT RP5b_RndFrameW, RP5b_RndFrameH;  /* Work window size */

extern FLT
  RP5b_RndProjSize,     /* Project plane fit square */
  RP5b_RndProjDist,     /* Distance to project plane from viewer (near) */
  RP5b_RndProjFarClip;  /* Distance to project far clip plane (far) */

extern MATR
  RP5b_RndMatrView, /* View coordinate system matrix */
  RP5b_RndMatrProj, /* Projection coordinate system matrix */
  RP5b_RndMatrVP;   /* Stored (View * Proj) matrix */

extern VEC3 RP5b_RndCamLoc,  /* Camera location */
  RP5b_RndCamAt,            /* Camera looking direction */
  RP5b_RndCamUp,            /* Camera up direction */
  RP5b_RndCamDir,           /* Camera direction */
  RP5b_RndCamRight;         /* Camera right reference */

extern INT RP5b_RndUBOCamera; /* Camera UBO */

/* Render base initialization function.
 * ARGUMENTS:
 *   - window handle:
 *       HWND hWnd;
 * RETURNS:
 *   (BOOL) - true if initialization was correct else - false.
 */
BOOL RP5b_RndInit( HWND hWnd );

/* Render base deleting function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID RP5b_RndClose( VOID );

/* Project resize function.
 * ARGUMENTS:
 *  - Screen sizes:
 *      INT W, H;
 * RETURNS: None.
 */
VOID RP5b_RndResize( INT W, INT H );

/* Frame coping function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID RP5b_RndCopyFrame( VOID );

/* Frame clearing and start drawing function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID RP5b_RndStart( VOID );

/* Part of render base deleting function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID RP5b_RndEnd( VOID );

/*** PRIMS ***/
typedef struct tagrp5bVERTEX
{
  VEC3 P;   /* Position */
  VEC2 T;  /* Texture coordinate */
  VEC3 N;   /* Normal vector */
  VEC4 C;  /* Color (r,g,b,a) */
} rp5bVERTEX;

/* Primitive type */
typedef enum tagrp5bPRIM_TYPE
{
  RP5b_RND_PRIM_TRIMESH,  /* Triangle mesh - array of triangles */
  RP5b_RND_PRIM_TRISTRIP, /* Triangle strip - array of stripped triangles */
  RP5b_RND_PRIM_LINES,    /* Line segments (by 2 points) */
  RP5b_RND_PRIM_POINTS,   /* Array of points */
  RP5b_RND_PRIM_PATCH,    /* Patches */
} rp5bPRIM_TYPE;

/* Primitive */
typedef struct tagrp5bPRIM
{
  rp5bPRIM_TYPE Type;    /* Primitive type */

  INT NumOfElements;     /* Number of vertices */

  VEC3 MinBB, MaxBB;     /* Minimum and maximum dimensions coordinates */

  MATR Trans;            /* Additional transformation matrix */

  INT VA, VBuf;          /* Vertex buffer */
  INT IA, IBuf;          /* Index buffer */

  INT MtlNo;             /* Material number in material array */

  INT InstanceCnt;       /* Counter for instancing, 0 - not use */
} rp5bPRIM;

/* Primitive collection data type */
typedef struct tagrp5bPRIMS
{
  INT NumOfPrims;    /* Number of primitives in array */
  rp5bPRIM *Prims;   /* Array of primitives */
  VEC3 MinBB, MaxBB;  /* Minimum and maximum dimensions coordinates */
  MATR Trans;        /* Common transformation matrix */
} rp5bPRIMS;

/* Prims data */
extern INT RP5b_RndShdAddonI[2]; /* Primitives params */

/* Create array of primitives function.
 * ARGUMENTS:
 *   - pointer to primitives structure:
 *       vg4PRIMS *Prs;
 *   - number of primitives to be add:
 *       INT NumOfPrims;
 * RETURNS:
 *   (BOOL) TRUE if successful, FALSE otherwise.
 */
BOOL RP5b_RndPrimsCreate( rp5bPRIMS *Prs, INT NumOfPrims );

/* Delete array of primitives function.
 * ARGUMENTS:
 *   - pointer to primitives structure:
 *       vg4PRIMS *Prs;
 * RETURNS: None.
 */
VOID RP5b_RndPrimsFree( rp5bPRIMS *Prs );

/* Draw array of primitives function.
 * ARGUMENTS:
 *   - pointer to primitives structure:
 *       vg4PRIMS *Prs;
 *   - global transformation matrix:
 *       MATR World;
 * RETURNS: None.
 */
VOID RP5b_RndPrimsDraw( rp5bPRIMS *Prs, MATR World );

/* Prim creating function.
 * ARGUMENTS:
 *   - Prim:
 *       rp5bPRIM *Pr;
 *   - Vertex array:
 *       rp5bVERTEX *V;
 *   - Index array:
 *       INT *I;
 *   - Number of vertex:
 *       INT NoofV;
 *   - Number of indexes:
 *       INT NoofI;
 *   - Primitive type:
 *       rp5bPRIM_TYPE Type;
 * RETURNS: None.
 */
VOID RP5b_RndPrimCreate( rp5bPRIM *Pr, rp5bPRIM_TYPE Type, rp5bVERTEX *V, INT NoofV, INT *I, INT NoofI );

/* Load array of primitives from .G3DM file function.
 * ARGUMENTS:
 *   - pointer to primitives structure:
 *       rp5bPRIMS *Prs;
 *   - file name:
 *       CHAR *FileName;
 * RETURNS:
 *   (BOOL) TRUE if successful, FALSE otherwise.
 */
BOOL RP5b_RndPrimsLoad( rp5bPRIMS *Prs, CHAR *FileName );

/* Camera setting function.
 * ARGUMENTS:
 *   - Approximate directions:
 *       VEC3 Loc, At, Up;
 * RETURNS: None.
 */
VOID RP5b_RndCamSet( VEC3 Loc, VEC3 At, VEC3 Up );

/* Prim drawing function.
 * ARGUMENTS:
 *   - Prim:
 *       rp5bPRIM *Pr;
 *   - World matrix:
 *       MATR World;
 * RETURNS: None.
 */
VOID RP5b_RndPrimDraw( rp5bPRIM *Pr, MATR World );

/* Prim deleting function.
 * ARGUMENTS:
 *   - Prim:
 *       rp5bPRIM *Pr;
 * RETURNS: None.
 */
VOID RP5b_RndPrimFree( rp5bPRIM *Pr );

/* Load prim from 'Obj' function.
 * ARGUMENTS:
 *   - Prim to load:
 *       rp5bPRIM *Pr;
 *   - File name:
 *       CHAR *FileName;
 * RETURNS:
 *   - (BOOL)
 */
BOOL RP5b_RndPrimLoad( rp5bPRIM *Pr, CHAR *FileName );

/* Minimum and maximum dimensions coordinates getting function.
 * ARGUMENTS:
 *   - Prim:
 *       rp5bPRIM *Pr;
 *   - Vertex array:
 *       rp5bVERTEX *V;
 *   - Number of vertex:
 *       INT NumofV;
 * RETURNS: None.
 */
VOID RP5b_RndPrimEvalBB( rp5bPRIM *Pr, rp5bVERTEX *V, INT NumofV );

/*** Grid module ***/
/* Grid topology representation type */
typedef struct tagrp5bGRID
{
  INT W, H;       /* Grid size (in vertices) */
  rp5bVERTEX *V;  /* Array (2D) of vertex */
} rp5bGRID;

/* Free grid function.
 * ARGUMENTS:
 *   - grid data: 
 *       rp5bGRID *G;
 * RETURNS: None.
 */
VOID RP5b_RndGridFree( rp5bGRID *G );

/* Create grid function.
 * ARGUMENTS:
 *   - grid data:
 *       rp5bGRID *G;
 *   - grid size:
 *       INT W, H;
 * RETURNS:
 *   (BOOL) TRUE if success, FALSE otherwise.
 */
BOOL RP5b_RndGridCreate( rp5bGRID *G, INT W, INT H );

/* Create primitive from grid function.
 * ARGUMENTS:
 *   - primitive to be create:
 *       rp5bPRIM *Pr;
 *   - grid data:
 *       rp5bGRID *G;
 * RETURNS:
 *   (BOOL) in case of success.
 */
BOOL RP5b_RndPrimFromGrid( rp5bPRIM *Pr, rp5bGRID *G );

/* Create sphere grid function.
 * ARGUMENTS:
 *   - grid data:
 *       rp5bGRID *G;
 *   - sphere radius:
 *       FLT R;
 *   - grid size:
 *       INT W, H;
 * RETURNS: None.
 */
VOID RP5b_RndGridCreateSphere( rp5bGRID *G, FLT R, INT W, INT H );

/*** Render target handle declaration module ***/

/* Render target initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID RP5b_RndTargetInit( VOID );

/* Render target deinitialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID RP5b_RndTargetClose( VOID );

/* Render target resize function.
 * ARGUMENTS:
 *   - new render target size (in pixels):
 *       INT W, H;
 * RETURNS: None.
 */
VOID RP5b_RndTargetResize( INT W, INT H );

/* Start render target usage function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID RP5b_RndTargetStart( VOID );

/* Finalize render target output function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID RP5b_RndTargetEnd( VOID );

/*** DEBUG handle ***/

/* Debug output function.
 * ARGUMENTS:
 *   - source APi or device:
 *      UINT Source;
 *   - error type:
 *      UINT Type;
 *   - error message id:
 *      UINT Id, 
 *   - message severity:
 *      UINT severity, 
 *   - message text length:
 *      INT Length, 
 *   - message text:
 *      CHAR *Message, 
 *   - user addon parameters pointer:
 *      VOID *UserParam;
 * RETURNS: None.
 */
VOID APIENTRY glDebugOutput( UINT Source, UINT Type, UINT Id, UINT Severity,
                             INT Length, const CHAR *Message, const VOID *UserParam );

/***
 * Light support
 ***/

/* Render pass data type */
typedef enum tagrp5bRENDER_PASS
{
  RP5b_RENDER_PASS_BASE,   /* Basiz render pass (store illumination coefficients) */
  RP5b_RENDER_PASS_SHADOW, /* Shadow render pass (substitute alternate shdaaer) */
} rp5bRENDER_PASS;

/* Light source direction */
VEC3 RP5b_RndLightDir;

/* Light source color */
VEC3 RP5b_RndLightColor;

/* Render pass value */
extern rp5bRENDER_PASS RP5b_RndPass;

/* Shadow render buffer */
UINT RP5b_RndShadowTexNo;

/* Shadow map matrix */
extern MATR RP5b_RndLightShadowMatr;

/* Light source type */
typedef enum tagrp5bLIGHT_TYPE
{
  RP5b_LIGHT_AMBIENT = 0,  /* Ambient light source */
  RP5b_LIGHT_POINT = 1,    /* Point light source */
  RP5b_LIGHT_DIR = 2,      /* Directional light source */
  RP5b_LIGHT_SPOT = 3,     /* Sopt light source */
} rp5bLIGHT_TYPE;

/* Light source representation type */
typedef struct ragrp5bLIGHT
{
  rp5bLIGHT_TYPE Type;  /* Light source type */
  VEC3
    Pos,                /* Point and spot light source position */
    Dir,                /* Directional and spot light source direction */
    Color,              /* Light source color */
    Att;                /* Attenuation by distance coefficients: CC CL CQ */
  VEC2 CutOffAngle;     /* Start and end cut-off angle cosinuses for spot light source */
  VEC2 CutOffDist;      /* Start and end distance for point and spot light source */
} rp5bLIGHT;

/* Light source array and fill size */
#define RP5b_RND_MAX_LIGHTS 1000
extern rp5bLIGHT RP5b_RndLights[RP5b_RND_MAX_LIGHTS];
extern INT RP5b_RndLightsSize;

/* Light system initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID RP5b_RndLightInit( VOID );

/* Light system deinitialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID RP5b_RndLightClose( VOID );

/* Draw shadow map function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID RP5b_RndLightShadow( VOID );

#endif /* __rnd_h_ */

/* END OF 'rnd.h' FILE */