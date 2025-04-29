/* FILE NAME: rndgrid.h
 * PROGRAMMER: RP5b
 * LAST UPDATE: 01.03.2023
 * PURPOSE: 3D animation project.
 *          Grid handle module.
 */

#include "anim/rnd/rnd.h"

/* Create grid function.
 * ARGUMENTS:
 *   - grid data:
 *       rp5bGRID *G;
 *   - grid size:
 *       INT W, H;
 * RETURNS:
 *   (BOOL) TRUE if success, FALSE otherwise.
 */
BOOL RP5b_RndGridCreate( rp5bGRID *G, INT W, INT H )
{
  INT i, j;

  G->H = H;
  G->W = W;

  if ((G->V = malloc(sizeof(rp5bVERTEX) * W * H)) == NULL)
    return FALSE;

  memset(G->V, 0, sizeof(rp5bVERTEX) * W * H);
  for (i = 0;  i < H; i++)
    for (j = 0; j < W; j++)
    {
      G->V[W * i + j].N = Vec3Set(0, 1, 0);
      G->V[W * i + j].C = Vec4Set(0.7, 0.4, 0.2, 1);
      G->V[W * i + j].T = Vec2Set(j / (G->W - 1.0), i / (G->H - 1.0));
    }
  return TRUE;
} /* End of 'RP5b_RndGridCreate' function */

/* Free grid function.
 * ARGUMENTS:
 *   - grid data: 
 *       rp5bGRID *G;
 * RETURNS: None.
 */
VOID RP5b_RndGridFree( rp5bGRID *G )
{
  if (G->V != NULL)
    free(G->V);
} /* End of 'RP5b_RndGridFree' function */

/* Build grid normals function.
 * ARGUMENTS:
 *   - grid data:
 *       rp5bGRID *G;
 * RETURNS: None.
 */
static VOID RP5b_RndGridAutoNormals( rp5bGRID *G )
{
  INT i, j;

  for (i = 0; i < G->W * G->H; i++)
    G->V[i].N = Vec3Set(0, 0, 0);

  for (i = 0; i < G->H - 1; i++)
    for (j = 0; j < G->W - 1; j++)
    {
      rp5bVERTEX
        *P00 = G->V + i * G->W + j,
        *P01 = G->V + i * G->W + j + 1,
        *P10 = G->V + (i + 1) * G->W + j,
        *P11 = G->V + (i + 1) * G->W + j + 1;
      VEC3 N;

      N = VecNormalize(VecCrossVec(VecSubVec(P00->P, P10->P),
                                   VecSubVec(P11->P, P10->P)));
      P00->N = VecAddVec(P00->N, N);
      P10->N = VecAddVec(P10->N, N);
      P11->N = VecAddVec(P11->N, N);

      N = VecNormalize(VecCrossVec(VecSubVec(P11->P, P01->P),
                                   VecSubVec(P00->P, P01->P)));
      P00->N = VecAddVec(P00->N, N);
      P01->N = VecAddVec(P01->N, N);
      P11->N = VecAddVec(P11->N, N);
    }

  for (i = 0; i < G->W * G->H; i++)
    G->V[i].N = VecNormalize(G->V[i].N);
} /* End of 'RP5b_RndGridAutoNormals' function */

/* Create primitive from grid function.
 * ARGUMENTS:
 *   - primitive to be create:
 *       rp5bPRIM *Pr;
 *   - grid data:
 *       rp5bGRID *G;
 * RETURNS:
 *   (BOOL) in case of success.
 */
BOOL RP5b_RndPrimFromGrid( rp5bPRIM *Pr, rp5bGRID *G )
{
  INT i, k, j, *Ind;

  memset(Pr, 0, sizeof(rp5bPRIM));
  if ((Ind = malloc(sizeof(INT) * ((G->H - 1) * (G->W * 2 + 1) - 1))) == NULL)
    return FALSE;

  for (i = 0, k = 0; i < G->H - 1; i++)
  {
    for (j = 0; j < G->W; j++)
    {
      Ind[k++] = (i + 1) * G->W + j;
      Ind[k++] = i * G->W + j;
    }
    if (i != G->H - 2)
      Ind[k++] = -1;
  }
  RP5b_RndPrimCreate(Pr, RP5b_RND_PRIM_TRISTRIP, G->V, G->W * G->H, Ind, (G->H - 1) * (G->W * 2 + 1) - 1);

  free(Ind);
  return TRUE;
} /* End of 'RP5b_RndPrimFromGrid' function */

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
VOID RP5b_RndGridCreateSphere( rp5bGRID *G, FLT R, INT W, INT H )
{
  INT i, j;
  FLT theta, phi;

  for (i = 0, theta = PI; i < H; i++, theta -= PI / (H - 1))
    for (j = 0, phi = 0; j < W; j++, phi += 2 * PI / (W - 1))
    {
      G->V[i * W + j].P = Vec3Set(-R * sin(theta) * sin(phi), R * cos(theta), -R * sin(theta) * cos(phi));
      G->V[i * W + j].N = Vec3Set(-sin(theta) * sin(phi), cos(theta), -sin(theta) * cos(phi));
      G->V[i * W + j].C = Vec4Set(fabs(sin(theta)) * 100, fabs(cos(theta)) * 50, fabs(cos(phi)) * 200, 1);
    }
  for (i = 0; i < G->W * G->H; i++)
    G->V[i].N = VecNormalize(G->V[i].N);
} /* End of 'RP5b_RndGridCreateSphere' function */

/* Create rectangle grid function.
 * ARGUMENTS:
 *   - grid data:
 *       rp5bGRID *G;
 *   - grid size:
 *       INT W, H;
 * RETURNS: None.
 */
VOID RP5b_RndGridCreateRectangle( rp5bGRID *G, INT W, INT H, INT X, INT Y )
{
  INT i, j;

  for (i = 0; i < H; i++)
    for (j = 0; j < W; j++)
    {
      G->V[i * W + j].P = Vec3Set(1, 1, 1);
      G->V[i * W + j].C = Vec4Set(100, 250, 0, 1);
    }

  for (i = 0; i < G->W * G->H; i++)
    G->V[i].N = VecNormalize(G->V[i].N);
} /* End of 'RP5b_RndGridCreateSphere' function */

/* END OF 'rndgrid.c' FILE */