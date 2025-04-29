/* FILE NAME: rndprim.c
 * PROGRAMMER: RP5b
 * LAST UPDATE: 13.03.2023
 * PURPOSE: 3D animation sample project.
 *          Rendering system base.
 *          Prim handle module.
 */

#include <stdio.h>
#include <time.h>
#include <string.h>

#include "anim/anim.h"

/* Normal normalizing function.
 * ARGUMENTS:
 *   - Vertex array:
 *       rp5bVERTEX *V;
 *   - Index array:
 *       INT *I;
 *   - Number of vertex:
 *       INT NoofV;
 *   - Number of indexes:
 *       INT NoofI;
 * RETURNS: None.
 */

static VOID RP5b_RndPrimAutonormalize( rp5bVERTEX *V, INT *Ind, INT NoofV, INT NoofI )
{
  INT i;

  for (i = 0; i < NoofV; i++)
    V[i].N = Vec3Set(0, 0, 0);

  for (i = 0; i < NoofI; i += 3)
  {
    VEC3
      p0 = V[Ind[i]].P,
      p1 = V[Ind[i + 1]].P,
      p2 = V[Ind[i + 2]].P,
      N = VecNormalize(VecCrossVec(VecSubVec(p1, p0), VecSubVec(p2, p0)));

    V[Ind[i]].N = VecAddVec(V[Ind[i]].N, N);
    V[Ind[i + 1]].N = VecAddVec(V[Ind[i + 1]].N, N);
    V[Ind[i + 2]].N = VecAddVec(V[Ind[i + 2]].N, N);
  }

  for (i = 0; i < NoofV; i++)
    V[i].N = VecNormalize(V[i].N);
} /* End of 'RP5b_RndPrimAutonormalize' function */

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
VOID RP5b_RndPrimEvalBB( rp5bPRIM *Pr, rp5bVERTEX *V, INT NumofV )
{
  INT i;

  if (NumofV == 0 || V == NULL)
    return;

  Pr->MinBB = Pr->MaxBB = V[0].P;

  for (i = 0; i < NumofV; i++)
  {
    if (Pr->MinBB.X > V[i].P.X)
      Pr->MinBB.X = V[i].P.X;
    if (Pr->MinBB.Y > V[i].P.Y)
      Pr->MinBB.Y = V[i].P.Y;
    if (Pr->MinBB.Z > V[i].P.Z)
      Pr->MinBB.Z = V[i].P.Z;

    if (Pr->MaxBB.X < V[i].P.X)
      Pr->MaxBB.X = V[i].P.X;
    if (Pr->MaxBB.Y < V[i].P.Y)
      Pr->MaxBB.Y = V[i].P.Y;
    if (Pr->MaxBB.Z < V[i].P.Z)
      Pr->MaxBB.Z = V[i].P.Z;
  }
} /* End of 'RP5b_RndPrimEvalBB' function */

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
VOID RP5b_RndPrimCreate( rp5bPRIM *Pr, rp5bPRIM_TYPE Type, rp5bVERTEX *V, INT NoofV, INT *I, INT NoofI )
{
  memset(Pr, 0, sizeof(rp5bPRIM));

  if (V != NULL && NoofV != 0)
  {
    glGenBuffers(1, &Pr->VBuf);
    glGenVertexArrays(1, &Pr->VA);

    /* Activating vertex array */
    glBindVertexArray(Pr->VA);

    /* Macking buffer active */
    glBindBuffer(GL_ARRAY_BUFFER, Pr->VBuf);
    /* Adding data (NumOfV - vertex number, V - vertex array) */
    glBufferData(GL_ARRAY_BUFFER, sizeof(rp5bVERTEX) * NoofV, V, GL_STATIC_DRAW);

    /* Adding data buffer to vertex the array */
    glBindBuffer(GL_ARRAY_BUFFER, Pr->VBuf);

    /*                    layout (attribute number),
     *                       number of components,
     *                          type,
     *                                   need to normalize,
     *                                       stride size in byte,
     *                                                  offset in bytes befor the start of the data */
    glVertexAttribPointer(0, 3, GL_FLOAT, FALSE, sizeof(rp5bVERTEX),
                          (VOID *)0); /* Position */
    glVertexAttribPointer(1, 2, GL_FLOAT, FALSE, sizeof(rp5bVERTEX),
                          (VOID *)sizeof(VEC3)); /* Texture coordinates */
    glVertexAttribPointer(2, 3, GL_FLOAT, FALSE, sizeof(rp5bVERTEX),
                          (VOID *)(sizeof(VEC3) + sizeof(VEC2))); /* Normal vector */
    glVertexAttribPointer(3, 4, GL_FLOAT, FALSE, sizeof(rp5bVERTEX),
                          (VOID *)(sizeof(VEC3) * 2 + sizeof(VEC2))); /* Color */


    /* Turning on layouts */
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);

    /* Turnng off vertex array */
    glBindVertexArray(0);
  }

  if (NoofI != 0 && I != NULL)
  {
    glGenBuffers(1, &Pr->IBuf);

    /* Making active buffer */
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Pr->IBuf);
    /* Coping data */ 
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(INT) * NoofI, I, GL_STATIC_DRAW);
    Pr->NumOfElements = NoofI;
  }
  else
    Pr->NumOfElements = NoofV, Pr->IBuf = -30;
  Pr->Type = Type;
  Pr->Trans = MatrIdentity();
  Pr->MaxBB = Pr->MinBB = Vec3Set1(0);
} /* End of RP5b_RndPrimCreate' function */

/* Prim drawing function.
 * ARGUMENTS:
 *   - Prim:
 *       rp5bPRIM *Pr;
 *   - World matrix:
 *       MATR World;
 * RETURNS: None.
 */
VOID RP5b_RndPrimDraw( rp5bPRIM *Pr, MATR World )
{
  MATR
    w = MatrMulMatr(Pr->Trans, World),
    winv = MatrTranspose(MatrInverse(w)),
    wvp = MatrMulMatr(w, RP5b_RndMatrVP);
  INT loc, ProgId = RP5b_RndMtlApply(Pr->MtlNo),
    gl_prim_type = Pr->Type == RP5b_RND_PRIM_LINES ? GL_LINES :
    Pr->Type == RP5b_RND_PRIM_TRIMESH ? GL_TRIANGLES :
    Pr->Type == RP5b_RND_PRIM_TRISTRIP ? GL_TRIANGLE_STRIP :
    Pr->Type == RP5b_RND_PRIM_PATCH ? GL_PATCHES :
    GL_POINTS;

  if (ProgId != 0)
  {
    glUseProgram(ProgId);
    RP5b_RndUBOUpdate(RP5b_RndUBOCamera, (INT)(&((rp5bRND_UBO_MATR *)0)->MatrW) / 16, 4, w.A[0]);
    RP5b_RndUBOUpdate(RP5b_RndUBOCamera, (INT)(&((rp5bRND_UBO_MATR *)0)->MatrWInv) / 16, 4, winv.A[0]);
    RP5b_RndUBOUpdate(RP5b_RndUBOCamera, (INT)(&((rp5bRND_UBO_MATR *)0)->MatrWVP) / 16, 4, wvp.A[0]);
    RP5b_RndUBOUpdate(RP5b_RndUBOCamera, (INT)(&((rp5bRND_UBO_MATR *)0)->LightShadowMatr) / 16, 4, RP5b_RndLightShadowMatr.A[0]);
    RP5b_RndUBOApply(RP5b_RndUBOCamera);

    if ((loc = glGetUniformLocation(ProgId, "AddonI0")) != -1)
      glUniform1i(loc, RP5b_RndShdAddonI[0]);
    if ((loc = glGetUniformLocation(ProgId, "AddonI1")) != -1)
      glUniform1i(loc, RP5b_RndShdAddonI[1]);

    /* Build projection */
    glLoadMatrixf(wvp.A[0]);

    /* Activating vertex array */
    glBindVertexArray(Pr->VA);
    if (Pr->InstanceCnt < 2)
      if (Pr->IBuf != -30)
      {
        /* Activating index array */
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Pr->IBuf);
        /* Drawing */
        glDrawElements(gl_prim_type, Pr->NumOfElements, GL_UNSIGNED_INT, NULL);
        /* Macking index not active */
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
      }
      else
        glDrawArrays(gl_prim_type, 0, Pr->NumOfElements);
    else
      if (Pr->IBuf != -30)
      {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Pr->IBuf);
        glDrawElementsInstanced(gl_prim_type, Pr->NumOfElements, GL_UNSIGNED_INT, NULL,
          Pr->InstanceCnt);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
      }
      else
        glDrawArraysInstanced(gl_prim_type, 0, Pr->NumOfElements, Pr->InstanceCnt);
    /* Macking vertex array not active */
    glBindVertexArray(0);
  }
  glUseProgram(0);
} /* End of 'RP5b_RndPrimDraw' function */

/* Prim deleting function.
 * ARGUMENTS:
 *   - Prim:
 *       rp5bPRIM *Pr;
 * RETURNS: None.
 */
VOID RP5b_RndPrimFree( rp5bPRIM *Pr )
{
  /* Making vertex array active */
  glBindVertexArray(Pr->VA);
  /* Deleting buffer */
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glDeleteBuffers(1, &Pr->VBuf);
  /* Making vertex array not active */
  glBindVertexArray(0);
  glDeleteVertexArrays(1, &Pr->VA);

  memset(Pr, 0, sizeof(rp5bPRIM));
} /* End of 'RP5b_RndPrimFree' function */

/* Load prim from 'Obj' function.
 * ARGUMENTS:
 *   - Prim to load:
 *       rp5bPRIM *Pr;
 *   - File name:
 *       CHAR *FileName;
 * RETURNS:
 *   - (BOOL)
 */
BOOL RP5b_RndPrimLoad( rp5bPRIM *Pr, CHAR *FileName )
{
  FILE *F;
  INT nv = 0, nf = 0, nvv, *I, size;
  rp5bVERTEX *V;
  static CHAR Buf[10000];

  memset(Pr, 0, sizeof(rp5bPRIM));
  if ((F = fopen(FileName, "r")) == NULL)
    return FALSE;

  /* Count data */
  while (fgets(Buf, sizeof(Buf) - 1, F) != NULL)
    if (Buf[0] == 'v' && Buf[1] == ' ')
      nv++;
    else if (Buf[0] == 'f' && Buf[1] == ' ')
    {
      INT n = 0;
      CHAR *ptr = Buf + 2, old = ' ';

      while (*ptr != 0)
        n += *ptr != ' ' && old == ' ', old = *ptr++;

      nf += n - 2;
    }

  /* Memory bulk */
  size = sizeof(rp5bVERTEX) * nv + sizeof(INT) * nf * 3;

  if ((V = malloc(size)) == NULL)
  {
    fclose(F);
    return FALSE;
  }
  I = (INT *)(V + nv);
  memset(V, 0, size);

  /* Real data */
  rewind(F);
  nvv = nv;
  nv = nf = 0;

  while (fgets(Buf, sizeof(Buf) - 1, F) != NULL)
    if (Buf[0] == 'v' && Buf[1] == ' ')
    {
      FLT x, y, z;

      sscanf(Buf + 2, "%f%f%f", &x, &y, &z);
      V[nv++].P = Vec3Set(x, y, z);
    }
    else if (Buf[0] == 'f' && Buf[1] == ' ')
    {
      INT n = 0, c0 = 0, c1 = 0, c = 0, c2 = 0;
      CHAR *ptr = Buf + 2, Old = ' ';

      while (*ptr != 0)
      {
        if (*ptr != ' ' && Old == ' ')
        {
          sscanf(ptr, "%d", &c);
          if (c < 0)
            c = nvv + c;
          else
            c--;
          if (n == 0)
            c0 = c;
          else if (n == 1)
            c1 = c;
          else if (n == 2)
          {
            /* Triangle is completed */
            I[nf++] = c0;
            I[nf++] = c1;
            I[nf++] = c;
            c2 = c;
          }
          else
          {
            /* Rectangle is completed */
            I[nf++] = c2;
            I[nf++] = c;
            I[nf++] = c0;
          }
          n++;
        }
        Old = *ptr++;
      }
    }
  Pr->Trans = MatrMulMatr3(MatrScale(Vec3Set1(0.26)),
    MatrTranslate(Vec3Set(2, 2 * fabs(sin(2 * clock() / 1000.0)), 0)), MatrRotateY(47 * sin(clock() / 1000.0)));
  RP5b_RndPrimAutonormalize(V, I, nvv, nf);

  RP5b_RndPrimCreate(Pr, RP5b_RND_PRIM_TRIMESH, V, nvv, I, nf );
  RP5b_RndPrimEvalBB(Pr, V, nvv);

  if (V != NULL)
    free(V);
  fclose(F);
  return TRUE;
} /* End of 'RP5b_RndPrimLoad' function */

/* END OF 'rndprim.c' FILE */