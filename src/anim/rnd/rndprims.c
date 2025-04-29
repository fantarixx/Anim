/* FILE NAME  : rndprims.c
 * PROGRAMMER : RP5b
 * LAST UPDATE: 01.03.2023
 * PURPOSE    : 3D animation project.
 *              Rendering system primitives handle module.
 */

#include <stdio.h>
#include <string.h>

#include "anim/anim.h"

/***
 * Primitives support
 ***/
INT RP5b_RndShdAddonI[2]; /* Primitives params */

/* Create array of primitives function.
 * ARGUMENTS:
 *   - pointer to primitives structure:
 *       rp5bPRIMS *Prs;
 *   - number of primitives to be add:
 *       INT NumOfPrims;
 * RETURNS:
 *   (BOOL) TRUE if successful, FALSE otherwise.
 */
BOOL RP5b_RndPrimsCreate( rp5bPRIMS *Prs, INT NumOfPrims )
{
  memset(Prs, 0, sizeof(rp5bPRIMS));
  if ((Prs->Prims = malloc(sizeof(rp5bPRIM) * NumOfPrims)) == NULL)
    return FALSE;
  memset(Prs->Prims, 0, sizeof(rp5bPRIM) * NumOfPrims);
  Prs->NumOfPrims = NumOfPrims;
  Prs->Trans = MatrIdentity();
  return TRUE;
} /* End of 'RP5b_RndPrimsCreate' function */

/* Delete array of primitives function.
 * ARGUMENTS:
 *   - pointer to primitives structure:
 *       rp5bPRIMS *Prs;
 * RETURNS: None.
 */
VOID RP5b_RndPrimsFree( rp5bPRIMS *Prs )
{
  if (Prs->Prims != NULL)
    free(Prs->Prims);
  memset(Prs, 0, sizeof(rp5bPRIMS));
} /* End of 'RP5b_RndPrimsFree' function */

/* Draw array of primitives function.
 * ARGUMENTS:
 *   - pointer to primitives structure:
 *       rp5bPRIMS *Prs;
 *   - global transformation matrix:
 *       MATR World;
 * RETURNS: None.
 */
VOID RP5b_RndPrimsDraw( rp5bPRIMS *Prs, MATR World )
{
  INT i;
  MATR m = MatrMulMatr(Prs->Trans, World);

  /* Draw all nontransparent primitives */ 
  RP5b_RndShdAddonI[0] = Prs->NumOfPrims;
  for (i = 0; i < Prs->NumOfPrims; i++)
    if (RP5b_RndMtlGet(Prs->Prims[i].MtlNo)->Trans == 1)
    {
      RP5b_RndShdAddonI[1] = i;
      RP5b_RndPrimDraw(&Prs->Prims[i], m);
    }

  /* Draw all transparent primitives */ 
  glEnable(GL_CULL_FACE);

  /* Draw all front-face-culling */ 
  glCullFace(GL_FRONT);
  for (i = 0; i < Prs->NumOfPrims; i++)
    if (RP5b_RndMtlGet(Prs->Prims[i].MtlNo)->Trans != 1)
    {
      RP5b_RndShdAddonI[1] = i;
      RP5b_RndPrimDraw(&Prs->Prims[i], m);
    }

  /* Draw all back-face-culling */ 
  glCullFace(GL_BACK);
  for (i = 0; i < Prs->NumOfPrims; i++)
    if (RP5b_RndMtlGet(Prs->Prims[i].MtlNo)->Trans != 1)
    {
      RP5b_RndShdAddonI[1] = i;
      RP5b_RndPrimDraw(&Prs->Prims[i], m);
    }

  glDisable(GL_CULL_FACE);
} /* End of 'RP5b_RndPrimsDraw' function */

/* Load array of primitives from .G3DM file function.
 * ARGUMENTS:
 *   - pointer to primitives structure:
 *       rp5bPRIMS *Prs;
 *   - file name:
 *       CHAR *FileName;
 * RETURNS:
 *   (BOOL) TRUE if successful, FALSE otherwise.
 */
BOOL RP5b_RndPrimsLoad( rp5bPRIMS *Prs, CHAR *FileName )
{
  FILE *F;
  INT flen, p, m, t;
  BYTE *mem, *ptr;
  DWORD Sign; /* == "G3DM" */
  DWORD NumOfPrims;
  DWORD NumOfMaterials;
  DWORD NumOfTextures;

  /* Open file */
  if ((F = fopen(FileName, "rb")) == NULL)
    return FALSE;

  /* Obtain file length */
  fseek(F, 0, SEEK_END);
  flen = ftell(F);
  rewind(F);

  /* Allocate memory and load whole file to memory */
  if ((mem = malloc(flen)) == NULL)
  {
    fclose(F);
    return FALSE;
  }
  fread(mem, 1, flen, F);
  fclose(F);

  ptr = mem;
  /* Signature */
  Sign = *(DWORD *)ptr;
  ptr += 4;
  if (Sign != *(DWORD *)"G3DM")
  {
    free(mem);
    return FALSE;
  }
  NumOfPrims = *(DWORD *)ptr;
  ptr += 4;
  NumOfMaterials = *(DWORD *)ptr;
  ptr += 4;
  NumOfTextures = *(DWORD *)ptr;
  ptr += 4;

  if (!RP5b_RndPrimsCreate(Prs, NumOfPrims))
  {
    free(mem);
    return FALSE;
  }
  /* Load primitives */
  for (p = 0; p < NumOfPrims; p++)
  {
    DWORD NumOfVertexes;
    DWORD NumOfFacetIndexes;  /* num of facets * 3 */
    DWORD MtlNo;              /* Material number in table below (in material section) */
    rp5bVERTEX *V;
    INT *Ind;

    NumOfVertexes = *(DWORD *)ptr;
    ptr += 4;
    NumOfFacetIndexes = *(DWORD *)ptr;
    ptr += 4;
    MtlNo = *(DWORD *)ptr;
    ptr += 4;

    V = (rp5bVERTEX *)ptr;
    ptr += sizeof(rp5bVERTEX) * NumOfVertexes;
    Ind = (INT *)ptr;
    ptr += sizeof(INT) * NumOfFacetIndexes;

    RP5b_RndPrimCreate(&Prs->Prims[p], RP5b_RND_PRIM_TRIMESH, V, NumOfVertexes, Ind, NumOfFacetIndexes);
    Prs->Prims[p].MtlNo = RP5b_RndMaterialsSize + MtlNo;
    if (p == 0)
      Prs->MinBB = Prs->Prims[p].MinBB, Prs->MaxBB = Prs->Prims[p].MaxBB;
    else
    {
      if (Prs->MinBB.X > Prs->Prims[p].MinBB.X)
        Prs->MinBB.X = Prs->Prims[p].MinBB.X;
      if (Prs->MaxBB.X < Prs->Prims[p].MaxBB.X)
        Prs->MaxBB.X = Prs->Prims[p].MaxBB.X;

      if (Prs->MinBB.Y > Prs->Prims[p].MinBB.Y)
        Prs->MinBB.Y = Prs->Prims[p].MinBB.Y;
      if (Prs->MaxBB.Y < Prs->Prims[p].MaxBB.Y)
        Prs->MaxBB.Y = Prs->Prims[p].MaxBB.Y;

      if (Prs->MinBB.Z > Prs->Prims[p].MinBB.Z)
        Prs->MinBB.Z = Prs->Prims[p].MinBB.Z;
      if (Prs->MaxBB.Z < Prs->Prims[p].MaxBB.Z)
        Prs->MaxBB.Z = Prs->Prims[p].MaxBB.Z;
    }
  }

  /* Load materials */
  for (m = 0; m < NumOfMaterials; m++)
  {
    struct
    {
      CHAR Name[300]; /* Material name */
      /* Illumination coefficients */
      VEC3 Ka, Kd, Ks;     /* Ambient, diffuse, specular coefficients */
      FLT Ph;             /* Phong power coefficient – shininess */
      FLT Trans;          /* Transparency factor */
      DWORD Tex[8];       /* Texture references 
                           * (8 time: texture number in G3DM file, -1 if no texture) */
      /* Shader information */
      CHAR ShaderString[300]; /* Additional shader information */
      DWORD Shader;       /* Shader number (uses after load into memory) */
    } *fmat;
    rp5bMATERIAL mtl;

    fmat = (VOID *)ptr;
    ptr += sizeof(*fmat);
    strncpy(mtl.Name, fmat->Name, RP5b_STR_MAX);
    mtl.Ka = fmat->Ka;
    mtl.Kd = fmat->Kd;
    mtl.Ks = fmat->Ks;
    mtl.Ph = fmat->Ph;
    mtl.Trans = fmat->Trans;
    for (t = 0; t < 8; t++)
      mtl.Tex[t] = fmat->Tex[t] == -1 ? -1 : RP5b_RndTexturesSize + fmat->Tex[t];
    RP5b_RndMtlAdd(&mtl);
  }

  /* Load textures */
  for (t = 0; t < NumOfTextures; t++)
  {
    CHAR *Name;
    DWORD W, H, C;

    Name = (CHAR *)ptr;
    ptr += 300;
    W = *(DWORD *)ptr;
    ptr += 4;
    H = *(DWORD *)ptr;
    ptr += 4;
    C = *(DWORD *)ptr;
    ptr += 4;
    RP5b_RndTexAddImg(Name, W, H, C, ptr);
    ptr += W * H * C;
  }

  free(mem);
  return TRUE;
} /* End of 'RP5b_RndPrimsLoad' function */

/* END OF 'rndprims.c' FILE */