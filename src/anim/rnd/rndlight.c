/* FILE NAME: rndlight.c
 * PROGRAMMER: RP5b
 * LAST UPDATE: 09.03.2023
 * PURPOSE: 3D animation project.
 *              Rendering system Light handle module.
 */

#include "anim/anim.h"

/***
 * Light source support
 ***/

/* Shadow map size */
#define RP5b_RND_SHADOW_MAP_SIZE 256

/* Light source direction */
VEC3 RP5b_RndLightDir;

/* Light source color */
VEC3 RP5b_RndLightColor;

/* Render pass value */
rp5bRENDER_PASS RP5b_RndPass;

/* Light sources array and fill size */
rp5bLIGHT RP5b_RndLights[RP5b_RND_MAX_LIGHTS];
INT RP5b_RndLightsSize;

/* Shadow map matrix */
MATR RP5b_RndLightShadowMatr;

/*** Shadow support ***/

/* Shadow render buffer */
UINT RP5b_RndShadowTexNo;

/* Shadow FBO */
static UINT RP5b_RndShadowFBO;

/* Shadow render target size */
static INT RP5b_RndShadowSize = 1024 * 2;

/* Light system initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID RP5b_RndLightInit( VOID )
{
  INT status;

  /* Set default light source */
  RP5b_RndLightDir = VecNormalize(Vec3Set(12, 8, -4));
  RP5b_RndLightColor = Vec3Set(1, 1, 1);

  /* Create shdow FBO */
  glGenFramebuffers(1, &RP5b_RndShadowFBO);
  glBindFramebuffer(GL_FRAMEBUFFER, RP5b_RndShadowFBO);

  RP5b_RndShadowTexNo = RP5b_RndTexAddFmt("Shadow Map", RP5b_RND_SHADOW_MAP_SIZE, RP5b_RND_SHADOW_MAP_SIZE, GL_DEPTH_COMPONENT24);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, RP5b_RndTextures[RP5b_RndShadowTexNo].TexId, 0);

  status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
  if (status != GL_FRAMEBUFFER_COMPLETE)
    OutputDebugString("\nError create frame buffer\n");
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
} /* End of 'RP5b_RndLightInit' function */

/* Light system deinitialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID RP5b_RndLightClose( VOID )
{
  glBindBuffer(GL_FRAMEBUFFER, RP5b_RndShadowFBO);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, 0, 0);
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glDeleteFramebuffers(1, &RP5b_RndShadowFBO);
} /* End of 'RP5b_RndLightClose' function */

/* Draw shadow map function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID RP5b_RndLightShadow( VOID )
{
  VEC3 scloc = RP5b_RndCamLoc, scat = RP5b_RndCamAt, scup = RP5b_RndCamUp;
  MATR scp = RP5b_RndMatrProj;
  FLT size = 8, far_dist = 300, clear_depth = 1;
  INT i;

  /* Set camera from light source */
  RP5b_RndMatrProj = MatrOrtho(-size, size, -size, size, -size, far_dist);
  RP5b_RndCamSet(RP5b_RndCamAt, VecSubVec(RP5b_RndCamAt, RP5b_RndLightDir), Vec3Set(0, 1, 0));
  RP5b_RndLightShadowMatr = RP5b_RndMatrVP;

  RP5b_RndUBOUpdate(RP5b_RndUBOCamera, (INT)(&((rp5bRND_UBO_MATR *)0)->MatrV) / 16, 4, RP5b_RndMatrView.A[0]);
  RP5b_RndUBOUpdate(RP5b_RndUBOCamera, (INT)(&((rp5bRND_UBO_MATR *)0)->MatrVP) / 16, 4, RP5b_RndMatrVP.A[0]);

  /* Set shadow map frame buffer */
  glBindFramebuffer(GL_FRAMEBUFFER, RP5b_RndShadowFBO);

  /* Clear depth */
  glClearBufferfv(GL_DEPTH, 0, &clear_depth);
  glViewport(0, 0, RP5b_RND_SHADOW_MAP_SIZE, RP5b_RND_SHADOW_MAP_SIZE);

  /* Redraw all scene */
  RP5b_RndPass = RP5b_RENDER_PASS_SHADOW;
  glEnable(GL_POLYGON_OFFSET_FILL);
  glPolygonOffset(4, 4);
  for (i = 0; i < RP5b_Anim.NumOfUnits; i++)
    RP5b_Anim.Units[i]->Render(RP5b_Anim.Units[i], &RP5b_Anim);
  glDisable(GL_POLYGON_OFFSET_FILL);
  RP5b_RndPass = RP5b_RENDER_PASS_BASE;
  glFinish();

  /* Restore main frame buffer */
  glBindBuffer(GL_FRAMEBUFFER, 0);

  /* Restore camera data */
  RP5b_RndMatrProj = scp;
  RP5b_RndCamSet(scloc, scat, scup);

  RP5b_RndUBOUpdate(RP5b_RndUBOCamera, (INT)(&((rp5bRND_UBO_MATR *)0)->MatrV) / 16, 4, RP5b_RndMatrView.A[0]);
  RP5b_RndUBOUpdate(RP5b_RndUBOCamera, (INT)(&((rp5bRND_UBO_MATR *)0)->MatrVP) / 16, 4, RP5b_RndMatrVP.A[0]);
} /* End of 'RP5b_RndLightShadow' function */

/* END OF 'rndlight.c' FILE */