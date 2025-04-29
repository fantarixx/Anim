/* FILE NAME: rndtrg.c
 * PROGRAMMER: RP5b
 * LAST UPDATE: 13.03.2023
 * PURPOSE: 3D animation project.
 *              Rendering system target handle module.
 *          Rendering handle module.
 */

#include "anim/anim.h"

/*** Target semiglobal data ***/

/* Number of render target attachments */
#define RP5b_RND_TARGETS 6

/* Target frame buffer Id */
static UINT RP5b_RndTargetFBO;

/* Reference to render target attachment textures */
static INT RP5b_RndTargetTexNo[RP5b_RND_TARGETS];

/* Depth render buffer Id */
static INT RP5b_RndTargetRndBuf;

/* Full screen render target primitive */
static rp5bPRIM RP5b_RndTargetScreenPrim;
static rp5bPRIM RP5b_RndLightAmbientPrim;
static rp5bPRIM RP5b_RndLightDirectionalPrim;

/* Render target create frame buffer function.
 * ARGUMENTS:
 *   - frame buffer size (in pixels):
 *       INT W, H;
 * RETURNS: None.
 */
static VOID RP5b_RndTargetCreate( INT W, INT H )
{
  INT i, status;
  INT DrawBuffer[RP5b_RND_TARGETS];
  rp5bTEXTURE *Tex = &RP5b_RndTextures[RP5b_RndMaterials[RP5b_RndTargetScreenPrim.MtlNo].Tex[0]];

  /* Create FBO */
  glGenFramebuffers(1, &RP5b_RndTargetFBO);
  glBindFramebuffer(GL_FRAMEBUFFER, RP5b_RndTargetFBO);

  /* Attach textures */
  for (i = 0; i < RP5b_RND_TARGETS; i++)
  {
    /* Resize target texture */
    glDeleteTextures(1, &Tex[i].TexId);
    glGenTextures(1, &Tex[i].TexId);
    glBindTexture(GL_TEXTURE_2D, Tex[i].TexId);
    glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA32F, W, H);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, 0);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, Tex[i].TexId, 0);
    DrawBuffer[i] = GL_COLOR_ATTACHMENT0 + i;
  }
  glDrawBuffers(RP5b_RND_TARGETS, DrawBuffer);

  /* Attach render buffer (depth) */
  glGenRenderbuffers(1, &RP5b_RndTargetRndBuf);
  glBindRenderbuffer(GL_RENDERBUFFER, RP5b_RndTargetRndBuf);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, W, H);
  glBindRenderbuffer(GL_RENDERBUFFER, 0);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, RP5b_RndTargetRndBuf);

  status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
  if (status != GL_FRAMEBUFFER_COMPLETE)
  {
    OutputDebugString("\nError create frame buffer\n");
  }
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
} /* End of 'RP5b_RndTargetCreate' function */

/* Render target free frame buffer function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
static VOID RP5b_RndTargetFree( VOID )
{
  INT i;

  glBindFramebuffer(GL_FRAMEBUFFER, RP5b_RndTargetFBO);
  /* Detach textures */
  for (i = 0; i < RP5b_RND_TARGETS; i++)
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, 0, 0);
  /* Detach render buffer (depth) */
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, 0);
  glDeleteRenderbuffers(1, &RP5b_RndTargetRndBuf);
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glDeleteFramebuffers(1, &RP5b_RndTargetFBO);
  RP5b_RndTargetFBO = 0;
  RP5b_RndTargetRndBuf = 0;
} /* End of 'RP5b_RndTargetFree' function */

/* Render target initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID RP5b_RndTargetInit( VOID )
{
  rp5bMATERIAL mtl = RP5b_RndMtlGetDef();
  INT i;
  CHAR Name[] = "Target0";

  for (i = 0; i < RP5b_RND_TARGETS; i++)
  {
    Name[6] = '0' + i;
    mtl.Tex[i] = RP5b_RndTexAddFmt(Name, RP5b_RndFrameW, RP5b_RndFrameH, GL_RGBA32F);
  }
  RP5b_RndPrimCreate(&RP5b_RndTargetScreenPrim, RP5b_RND_PRIM_POINTS, NULL, 1, NULL, 0);
  strncpy(mtl.Name, "Target material", RP5b_STR_MAX);
  mtl.ShdNo = RP5b_RndShdAdd("target0");
  RP5b_RndTargetScreenPrim.MtlNo = RP5b_RndMtlAdd(&mtl);
  RP5b_RndTargetCreate(RP5b_RndFrameW, RP5b_RndFrameH);

  RP5b_RndPrimCreate(&RP5b_RndLightAmbientPrim, RP5b_RND_PRIM_POINTS, NULL, 1, NULL, 0);
  strncpy(mtl.Name, "Light: Ambient material", RP5b_STR_MAX);
  mtl.ShdNo = RP5b_RndShdAdd("lights/ambient");
  RP5b_RndLightAmbientPrim.MtlNo = RP5b_RndMtlAdd(&mtl);

  RP5b_RndPrimCreate(&RP5b_RndLightDirectionalPrim, RP5b_RND_PRIM_POINTS, NULL, 1, NULL, 0);
  strncpy(mtl.Name, "Light: Directional material", RP5b_STR_MAX);
  mtl.ShdNo = RP5b_RndShdAdd("lights/directional");
  RP5b_RndLightDirectionalPrim.MtlNo = RP5b_RndMtlAdd(&mtl);
} /* End of 'RP5b_RndTargetInit' function */

/* Render target deinitialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID RP5b_RndTargetClose( VOID )
{
  RP5b_RndTargetFree();
  RP5b_RndPrimFree(&RP5b_RndTargetScreenPrim);
  RP5b_RndPrimFree(&RP5b_RndLightAmbientPrim);
  RP5b_RndPrimFree(&RP5b_RndLightDirectionalPrim);
} /* End of 'RP5b_RndTargetClose' function */

/* Render target resize function.
 * ARGUMENTS:
 *   - new render target size (in pixels):
 *       INT W, H;
 * RETURNS: None.
 */
VOID RP5b_RndTargetResize( INT W, INT H )
{
  RP5b_RndTargetFree();
  RP5b_RndTargetCreate(W, H);
  glViewport(0, 0, W, H);
} /* End of 'RP5b_RndTargetResize' function */

/* Start render target usage function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID RP5b_RndTargetStart( VOID )
{
  INT i;
  FLT dv = 1;
  VEC4 Col0 = {0};

  glBindFramebuffer(GL_FRAMEBUFFER, RP5b_RndTargetFBO);
  for (i = 0; i < RP5b_RND_TARGETS; i++)
    glClearBufferfv(GL_COLOR, i, &Col0.X);
  glClearBufferfv(GL_DEPTH, 0, &dv);
  glViewport(0, 0, RP5b_RndFrameW, RP5b_RndFrameH);
} /* End of 'RP5b_RndTargetStart' function */

/* Finalize render target output function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID RP5b_RndTargetEnd( VOID )
{
  VEC3 Col = {0};
  INT Modes[2], i;

  glGetIntegerv(GL_POLYGON_MODE, Modes);

  /* Finilize G-Buffer filling */
  glFinish();
  RP5b_RndLightShadow();
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glViewport(0, 0, RP5b_RndFrameW, RP5b_RndFrameH);

  glClearBufferfv(GL_COLOR, 0, &Col.X);

  glDisable(GL_DEPTH_TEST);

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  glActiveTexture(GL_TEXTURE0 + 8);
  glBindTexture(GL_TEXTURE_2D, RP5b_RndTextures[RP5b_RndShadowTexNo].TexId);

  glBlendFunc(GL_ONE, GL_ONE);
  RP5b_RndPrimDraw(&RP5b_RndLightAmbientPrim, MatrIdentity());
  RP5b_RndPrimDraw(&RP5b_RndLightDirectionalPrim, MatrIdentity());
  glBlendFunc(GL_ONE, GL_ZERO);

  glPolygonMode(GL_FRONT, Modes[0]);
  glPolygonMode(GL_BACK, Modes[1]);

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  for (i = 0; i < RP5b_Anim.NumOfUnits; i++)
    RP5b_Anim.Units[i]->DefRender(RP5b_Anim.Units[i], &RP5b_Anim);
  glBlendFunc(GL_ONE, GL_ZERO);

  glEnable(GL_DEPTH_TEST);

  glFinish();
} /* End of 'RP5b_RndTargetEnd' function */

/* END OF 'rndtrg.c' FILE */