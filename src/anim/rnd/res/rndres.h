/* FILE NAME: rndres.h
 * PROGRAMMER: RP5b
 * LAST UPDATE: 13.03.2023
 * PURPOSE: 3D animation project.
 *          Resources declaration handle module.
 */

 #ifndef __rndres_h_
 #define __rndres_h_
 
 #define GLEW_STATIC
 #include <glew.h>
 
 #include <wglew.h>
 #include <gl/wglext.h>
 
 #include "src/def.h"
 
 #define RP5b_STR_MAX 300
 
 /*** Shaders module ***/
 /* Shader program store type */
 typedef struct tagrp5bSHADER
 {
   CHAR Name[RP5b_STR_MAX]; /* Shader filename prefix */
   INT ProgId;             /* Shader program Id */
 } rp5bSHADER;
 
 /* Shaders stock */
 #define RP5b_MAX_SHADERS 30
 
 /* Shaders global data */
 extern rp5bSHADER RP5b_RndShaders[RP5b_MAX_SHADERS]; /* Array of shaders */
 extern INT RP5b_RndShadersSize;                      /* Shadres array store size */
 
 /* Shader storage initialize function.
  * ARGUMENTS: None.
  * RETURNS: None.
  */
 VOID RP5b_RndShdInit( VOID );
 
 /* Shader storage deinitialize function.
  * ARGUMENTS: None.
  * RETURNS: None.
  */
 VOID RP5b_RndShdClose( VOID );
 
 /* Shader storage deinitialize function.
  * ARGUMENTS: None.
  * RETURNS: None.
  */
 VOID RP5b_RndShdUpdate( VOID );
 
 /* Shader storage initialize function.
  * ARGUMENTS:
  *   - shader file path to load:
  *       CHAR *ShaderFileNamePrefix;
  * RETURNS:
  *   (INT) new shader stock number.
  */
 INT RP5b_RndShdAdd( CHAR *ShaderFileNamePrefix );
 
 /*** Texture module ***/
 /* Texture representation type */
 typedef struct tagrp5bTEXTURE
 {
   CHAR Name[RP5b_STR_MAX]; /* Texture name */
   INT W, H;               /* Texture size in pixels */
   UINT TexId;             /* OpenGL texture Id */ 
 } rp5bTEXTURE;
 
 /* Textures stock */
 #define RP5b_MAX_TEXTURES 30
 extern rp5bTEXTURE RP5b_RndTextures[RP5b_MAX_TEXTURES]; /* Array of textures */
 extern INT RP5b_RndTexturesSize;                       /* Textures array store size */
 
 /* Texture storage initialize function.
  * ARGUMENTS: None.
  * RETURNS: None.
  */
 VOID RP5b_RndTexInit( VOID );
 
 /* Texture adding from file function.
  * ARGUMENTS:
  *   - Name of file:
  *       CHAR *FileName;
  * RETURNS:
  *   (INT) Number of texture in array of textures.
  */
 INT RP5b_RndTexAddFromFile( CHAR *FileName );
 
 /* Texture storage deinitialize function.
  * ARGUMENTS: None.
  * RETURNS: None.
  */
 VOID RP5b_RndTexClose( VOID );
 
 /* Add texture by OpenGL low-level format to stock function.
  * ARGUMENTS:
  *   - texture name:
  *       CHAR *Name;
  *   - texture size in pixels:
  *       INT W, H;
  *   - OpenGL texture element data type:
  *       INT GLType;
  * RETURNS:
  *   (INT) texture stock number (0 if error is occured).
  */
 INT RP5b_RndTexAddFmt( CHAR *Name, INT W, INT H, INT GLType );
 
 /*** Material module ***/
 /* Material store type */
 typedef struct tagrp5bMATERIAL
 {
   CHAR Name[RP5b_STR_MAX];  /* Material name */
 
   /* Illumination coefficients */
   VEC3 Ka, Kd, Ks;          /* Ambient, diffuse, specular coefficients */
   FLT Ph;                   /* Phong power coefficient */
 
   FLT Trans;                /* Transparency factor */
 
   INT Tex[8];               /* Texture references from texture table (or -1) */
 
   INT ShdNo;                /* Shader number in shader table */
   INT UBONo;                /* UBO store table number */
 } rp5bMATERIAL;
 
 /* Material stock */
 #define RP5b_MAX_MATERIALS 300
 extern rp5bMATERIAL RP5b_RndMaterials[RP5b_MAX_MATERIALS]; /* Array of materials */
 extern INT RP5b_RndMaterialsSize;                         /* Materials array */
 
 /* Matirial returning function.
  * ARGUMENTS:
  *   - material number:
  *       INT MtlNo;
  * RETURNS:
  *   (rp5bMATERIAL) - current matirial.
  */
 rp5bMATERIAL * RP5b_RndMtlGet( INT MtlNo );
 
 /* Macking default matirial function.
  * ARGUMENTS: None.
  * RETURNS:
  *   (rp5bMATERIAL) - basic matirial.
  */
 rp5bMATERIAL RP5b_RndMtlGetDef( VOID );
 
 /* Material storage initialize function.
  * ARGUMENTS: None.
  * RETURNS: None.
  */
 VOID RP5b_RndMtlInit( VOID );
 
 /* Material storage deinitialize function.
  * ARGUMENTS: None.
  * RETURNS: None.
  */
 VOID RP5b_RndMtlClose( VOID );
 
 /* Getting shaders program identificator function.
  * ARGUMENTS:
  *   Number of material:
  *     INT MtlNo;
  * RETURNS:
  *   (INT) ProgId from shader.
  */
 INT RP5b_RndMtlApply( INT MtlNo );
 
 /* Material adding function.
  * ARGUMENTS: None.
  * RETURNS:
  *   (INT) array numbers material.
  */
 INT RP5b_RndMtlAdd( rp5bMATERIAL *Mtl );
 
 /* Resourses storages initialize function.
  * ARGUMENTS: None.
  * RETURNS: None.
  */
 VOID RP5b_RndResInit( VOID );
 
 /* Resourses storages deinitialize function.
  * ARGUMENTS: None.
  * RETURNS: None.
  */
 VOID RP5b_RndResClose( VOID );
 
 /* Texture adding to storage function.
  * ARGUMENTS:
  *   - Name of tuxture:
  *       CHAR *Name;
  *   - Texture sizes:
  *       INT W, H;
  *   - Resizing coef:
  *       INT C;
  *   - Array of texture pixels:
  *       VOID *Bits;
  * RETURNS:
  *   (INT) Number of texture in array of textures.
  */
 INT RP5b_RndTexAddImg( CHAR *Name, INT W, INT H, INT C, VOID *Bits );
 
 /***
  * Fonts module
  ***/
 
 /* Init font subsystem funtion.
  * ARGUMENTS:
  *   - font name:
  *      CHAR *FileName;
  * RETURNS: None.
  */
 VOID RP5b_RndFntInit( VOID );
 
 /* Load font from .G#DF file function.
  * ARGUMENTS:
  *   - font file name:
  *       CHAR *FileName;
  * RETURNS:
  *   (BOOL) TRUE if succes, FALSE otherwise.
  */
 BOOL RP5b_RndFntLoad( CHAR *FileName );
 
 /* Draw string function.
  * ARGUMENTS:
  *   - string to draw:
  *       CHAR *Str;
  * RETURNS: None.
  */
 VOID RP5b_RndFntDraw( CHAR *Str );
 
 /* Deinit font subsystem funtion.
  * ARGUMENTS: None.
  * RETURNS: None.
  */
 VOID RP5b_RndFntClose( VOID );
 
 
 /***
  * Image handle
  ***/
 
 /* Image representation type */
 typedef struct tagrp5bIMAGE
 {
   INT W, H;      /* Image size */
   DWORD *Pixels; /* Image pixels */
 } rp5bIMAGE;
 
 /* Create image function.
  * ARGUMENTS:
  *   - image data:
  *       rp5bIMAGE *Img;
  *   - new image size:
  *       INT W, H;
  * RETURNS:
  *   (BOOL) TRUE if success, FALSE otherwise.
  */
 BOOL RP5b_ImgCreate( rp5bIMAGE *Img, INT W, INT H );
 
 /* Free image function.
  * ARGUMENTS:
  *   - image data:
  *       rp5bIMAGE *Img;
  * RETURNS: None.
  */
 VOID RP5b_ImgFree( rp5bIMAGE *Img );
 
 /* Load image from file function.
  * ARGUMENTS:
  *   - image data:
  *       rp5bIMAGE *Img;
  *   - image file name:
  *       CHAR *FileName;
  * RETURNS:
  *   (BOOL) TRUE if success, FALSE otherwise.
  */
 BOOL RP5b_ImgLoad( rp5bIMAGE *Img, CHAR *FileName );
 
 /*** UBOs module ***/
 
 /* UBO representation type */
 typedef struct tagrp5bUBO
 {
   CHAR Name[RP5b_STR_MAX]; /* UBO name */
   INT Size;               /* UBO number of 16 bytes blocks */
   UINT UBOId;             /* OpenGL UBO Id */ 
   UINT BindPoint;         /* OpenGL UBO bind point */
 } rp5bUBO;
 
 /* UBOs stock */
 #define RP5b_MAX_UBOS 300
 extern rp5bUBO RP5b_RndUBOs[RP5b_MAX_UBOS]; /* Array of UBO */
 extern INT RP5b_RndUBOsSize;                /* UBO array store size */
 
 /* UBO handle initialization function.
  * ARGUMENTS: None.
  * RETURNS: None.
  */
 VOID RP5b_RndUBOInit( VOID );
 
 /* UBO handle deinitialization function.
  * ARGUMENTS: None.
  * RETURNS: None.
  */
 VOID RP5b_RndUBOClose( VOID );
 
 /* Add UBO to stock function.
  * ARGUMENTS:
  *   - UBO name:
  *       CHAR *Name;
  *   - OpenGL UBO bind point:
  *       UINT BindPoint;
  *   - UBO size in 16 bytes blocks:
  *       INT NumOfBlocks;
  *   - UBO data:
  *       VOID *Bits;
  * RETURNS:
  *   (INT) UBO stock number (0 if error is occured).
  */
 INT RP5b_RndUBOCreate( CHAR *Name, UINT BindPoint, INT NumOfBlocks, VOID *Bits );
 
 /* UBO data update function.
  * ARGUMENTS:
  *   - UBO number in stock:
  *       INT UBONo;
  *   - UBO offset 16 bytes blocks:
  *       INT BlocksOffset;
  *   - UBO size in 16 bytes blocks:
  *       INT NumOfBlocks;
  *   - UBO data:
  *       VOID *Bits;
  * RETURNS: None.
  */
 VOID RP5b_RndUBOUpdate( INT UBONo, INT BlocksOffset, INT NumOfBlocks, VOID *Bits );
 
 /* UBO apply function.
  * ARGUMENTS:
  *   - UBO number in stock:
  *       INT UBONo;
  * RETURNS: None.
  */
 VOID RP5b_RndUBOApply( INT UBONo );
 
 /*** UBO distribution ***/
 
 /* Bind points */
 #define RP5b_RND_UBO_BIND_CAMERA 0
 #define RP5b_RND_UBO_BIND_MATERIAL 1
 #define RP5b_RND_UBO_BIND_PRIM 2
 
 /* UBO matrix type */
 typedef struct tagrp5bRND_UBO_MATR
 {
   MATR MatrWVP;                      /* World * View * Proj matrix */
   MATR MatrW;                        /* World matrix */
   MATR MatrWInv;                     /* World inversion matrix */
   MATR MatrVP;                       /* View * Proj matrix */
   MATR MatrV;                        /* View matrix */
   VEC4 CamLoc;                       /* Camera location */
   VEC4 CamRight;                     /* Camera right direction */
   VEC4 CamUp;                        /* Camera up direction */
   VEC4 CamDir;                       /* Camera forward direction */
   VEC4 WHProjDistFar;                /* Frame size and project dist and project farclip */
   VEC4 TimeGlobalDeltaGlobal;        /* Time/global time, delta/global delta time */
   VEC4 WireframeProjSize;            /* Wireframe flag and project size */
   VEC4 LightDir;                     /* Directional light source */
   VEC4 LightColor;                   /* Light color */
   MATR LightShadowMatr;              /* Shadow matrix */
 } rp5bRND_UBO_MATR;
 
 /* UBO material type */
 typedef struct tagrp5bRND_UBO_MATERIAL
 {
   VEC4 KaTrans;       /* Ambient and transparensy */
   VEC4 Kd;            /* Diffuse */
   VEC4 KsPh;          /* Specular + Phong */
   VEC4 TexFlags0123;  /* Textures 0 - 3 presence flag */
   VEC4 TexFlags4567;  /* Textures 4 - 7 presence flag */
 } rp5bRND_UBO_MATERIAL;
 
 #endif /* __rndres_h_ */
 
 /* END OF 'rndres.h' FILE */