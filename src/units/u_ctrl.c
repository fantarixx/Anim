/* FILE NAME: u_ctrl.c
 * PROGRAMMER: RP5b
 * LAST UPDATE: 17.03.2023
 * PURPOSE: 3D animation project.
 *          Control unit declaration module.
 */

#include <stdio.h>

#include "units.h"

/* Ctrl special type */
typedef struct
{
  RP5b_UNIT_BASE_FIELDS;   /* Unit functions */
  rp5bPRIM Pr;      /* Position */
  BOOL IsWireframe;   /* Filling or linearing */
  VEC3 StartAt,        /* Start at direction */
    StartUp,          /* Start up direction */
    StartLoc;         /* Start position */
} rp5bUNIT_CTRL;

/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       rp5bUNIT_CTRL *Uni;
 *   - animation context:
 *       rp5bANIM *Ani;
 * RETURNS: None.
 */
static VOID RP5b_Init( rp5bUNIT_CTRL *Uni, rp5bANIM *Ani )
{
  rp5bMATERIAL mtl = RP5b_RndMtlGetDef();

  RP5b_RndPrimCreate(&Uni->Pr, RP5b_RND_PRIM_POINTS, NULL, 1, NULL, 0);
  strncpy(mtl.Name, "Debug", RP5b_STR_MAX - 1);
  mtl.ShdNo = RP5b_RndShdAdd("debug");;
  Uni->Pr.MtlNo = RP5b_RndMtlAdd(&mtl);

  Uni->IsWireframe = 0;
  Uni->StartLoc = Vec3Set(1, 30, 0);
  Uni->StartAt = Vec3Set1(0);
  Uni->StartUp = Vec3Set(0, 1, 0);
  RP5b_RndCamSet(Uni->StartLoc, Uni->StartAt, Uni->StartUp);
} /* End of 'RP5b_Init' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       rp5bUNIT_CTRL *Uni;
 *   - animation context:
 *       rp5bANIM *Ani;
 * RETURNS: None.
 */

static VOID RP5b_Close( rp5bUNIT_CTRL *Uni, rp5bANIM *Ani )
{
  RP5b_RndPrimFree(&Uni->Pr);
} /* End of 'RP5b_Close' function */

/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       rp5bUNIT_CTRL *Uni;
 *   - animation context:
 *       rp5bANIM *Ani;
 * RETURNS: None.
 */
static VOID RP5b_Render( rp5bUNIT_CTRL *Uni, rp5bANIM *Ani )
{
  VEC3 scloc = RP5b_RndCamLoc, scat = RP5b_RndCamAt, scup = RP5b_RndCamUp;
  MATR scp = RP5b_RndMatrProj;
  static DBL MesureTime;
  static CHAR Buf[102];

  sprintf(Buf, "FPS: %.5f", Ani->FPS);
  if (MesureTime > 3)
  {
    SetWindowText(RP5b_Anim.hWnd, Buf);
    MesureTime = 0;
  }
  MesureTime += RP5b_Anim.DeltaTime;

  RP5b_RndMatrProj = MatrOrtho(0, Ani->W - 1, 0, Ani->H - 1, -1, 1);
  RP5b_RndMatrView = MatrIdentity();
  RP5b_RndMatrVP = MatrMulMatr(RP5b_RndMatrView, RP5b_RndMatrProj);

  /* Update common camera buffer */
  RP5b_RndUBOUpdate(RP5b_RndUBOCamera, (INT)(&((rp5bRND_UBO_MATR *)0)->MatrV) / 16, 4, RP5b_RndMatrView.A[0]);
  RP5b_RndUBOUpdate(RP5b_RndUBOCamera, (INT)(&((rp5bRND_UBO_MATR *)0)->MatrVP) / 16, 4, RP5b_RndMatrVP.A[0]);

  if (RP5b_RndPass != RP5b_RENDER_PASS_SHADOW)
    RP5b_RndFntDraw(Buf);

  /* Restore common camera buffer */
  RP5b_RndMatrProj = scp;
  RP5b_RndCamSet(scloc, scat, scup);

  RP5b_RndUBOUpdate(RP5b_RndUBOCamera, (INT)(&((rp5bRND_UBO_MATR *)0)->MatrV) / 16, 4, RP5b_RndMatrView.A[0]);
  RP5b_RndUBOUpdate(RP5b_RndUBOCamera, (INT)(&((rp5bRND_UBO_MATR *)0)->MatrVP) / 16, 4, RP5b_RndMatrVP.A[0]);

  glLineWidth(2);
  RP5b_RndPrimDraw(&Uni->Pr, MatrIdentity());
  glLineWidth(1);
} /* End of 'RP5b_Render' function */

/* Unit deffered render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       rp5bUNIT *Uni;
 *   - animation context:
 *       rp5bANIM *Ani;
 * RETURNS: None.
 */
static VOID RP5b_UnitDefRender( rp5bUNIT_CTRL *Uni, rp5bANIM *Ani )
{
} /* End of 'RP5b_UnitDefRender' function */

/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       rp5bUNIT_CTRL *Uni;
 *   - animation context:
 *       rp5bANIM *Ani;
 * RETURNS: None.
 */
static VOID RP5b_UnitResponse( rp5bUNIT_CTRL *Uni, rp5bANIM *Ani )
{
  if (Ani->Keys[VK_LCONTROL])
  {
    FLT Dist = VecLen(VecSubVec(RP5b_RndCamAt, RP5b_RndCamLoc)),
      CosT = (RP5b_RndCamLoc.Y - RP5b_RndCamAt.Y) / Dist,
      SinT = sqrt(1 - CosT * CosT),
      Plen = Dist * SinT,
      CosP = (RP5b_RndCamLoc.Z - RP5b_RndCamAt.Z) / Plen,
      SinP = (RP5b_RndCamLoc.X - RP5b_RndCamAt.X) / Plen,
      Azimuth = R2D(atan2(SinP, CosP)),
      Elevator = R2D(atan2(SinT, CosT));

    Azimuth += Ani->GlobalDeltaTime * 3 *
      (-30 * Ani->Keys[VK_LBUTTON] * Ani->Mdx + 47 * (Ani->Keys[VK_LEFT] - Ani->Keys[VK_RIGHT]));

    Elevator += Ani->GlobalDeltaTime * 3 *
      (-30 * Ani->Keys[VK_LBUTTON] * Ani->Mdy + 47 * (Ani->Keys[VK_UP] - Ani->Keys[VK_DOWN]));
    if (Elevator < 0.08)
      Elevator = 0.08;
    else if (Elevator > 178.9)
      Elevator = 178.9;

    Dist += Ani->GlobalDeltaTime * (1 + Ani->Keys[VK_SHIFT] * 27) *
      (10 * Ani->Mdz + 8 * (Ani->Keys[VK_NEXT] - Ani->Keys[VK_PRIOR]));
    if (Dist < 0.1)
      Dist = 0.1;

    if (Ani->Keys[VK_RBUTTON])
    {
      FLT Wp, Hp, sx, sy;
      VEC3 dv;

      Wp = RP5b_RndProjSize;
      Hp = RP5b_RndProjSize;
      if (Ani->W > Ani->H)
        Wp *= (FLT)Ani->W / Ani->H;
      else
        Hp *= (FLT)Ani->H / Ani->W;
      sx = -Ani->Mdx * Wp / Ani->W * Dist / RP5b_RndProjDist;
      sy = Ani->Mdy * Hp / Ani->H * Dist / RP5b_RndProjDist;

      dv = VecAddVec(VecMulNum(RP5b_RndCamRight, sx),
        VecMulNum(RP5b_RndCamUp, sy));
      RP5b_RndCamAt = VecAddVec(RP5b_RndCamAt, dv);
      RP5b_RndCamLoc = VecAddVec(RP5b_RndCamLoc, dv);
    }

    /* Camera result */
    RP5b_RndCamSet(PointTransform(Vec3Set(0, Dist, 0),
      MatrMulMatr3(MatrRotateX(Elevator), MatrRotateY(Azimuth), MatrTranslate(RP5b_RndCamAt))),
      RP5b_RndCamAt, Vec3Set(0, 1, 0));
  }


  if (Ani->Keys[VK_SHIFT] && Ani->KeysClick['P'])
    Ani->IsPause = !Ani->IsPause;
  if (Ani->Keys[VK_LCONTROL] && Ani->KeysClick[VK_F11])
    RP5b_AnimFlipFullScreen();
  if (Ani->Keys[VK_LCONTROL] && Ani->KeysClick['R'])
    RP5b_RndCamSet(Uni->StartLoc, Uni->StartAt, Uni->StartUp);
  if (Ani->Keys[VK_ESCAPE])
    RP5b_AnimDoExit();
  if (Ani->Keys[VK_SHIFT] && Ani->KeysClick['W'])
  {
    INT modes[2];

    glGetIntegerv(GL_POLYGON_MODE, modes);
    if (modes[0] == GL_LINE)
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    else
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  }
} /* End of 'RP5b_UnitResponse' function */

/* Unit creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (rp5bUNIT *) pointer to created unit.
 */
rp5bUNIT * RP5b_UnitCtrlCreate( VOID )
{
  rp5bUNIT *Uni;

  if ((Uni = RP5b_AnimUnitCreate(sizeof(rp5bUNIT_CTRL))) == NULL)
    return NULL;

  /* Setup unit methods */
  Uni->Init = (VOID *)RP5b_Init;
  Uni->Close = (VOID *)RP5b_Close;
  Uni->Response = (VOID *)RP5b_UnitResponse;
  Uni->Render = (VOID *)RP5b_Render;
  Uni->DefRender = (VOID *)RP5b_UnitDefRender;

  return Uni;
} /* End of 'RP5b_UnitCtrlCreate' function */

/* END OF 'u_ctrl.c' FILE */