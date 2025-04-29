/* FILE NAME: mth.h
 * PROGRAMMER: RP5b
 * LAST UPDATE: 03.03.2023
 * PURPOSE: spatial mathematics library.
 */

#ifndef __mth_h_
#define __mth_h_

#include <COMMONDF.H>
#include <math.h>

/* Degrees data*/
#define PI 3.14159265358979323846
#define D2R(A) ((A) * (PI / 180.0))
#define Degree2Radian(a) D2R(a)
#define R2D(A) ((A) * (180.0 / PI))
#define Radian2Degree(a) R2D(a)

/* Multiplication of matrix */
#define MatrMulMatr3(A, B, C) MatrMulMatr(MatrMulMatr((A), (B)), (C))
#define MatrMulMatr4(A, B, C, D) MatrMulMatr(MatrMulMatr3((A), (B), (C)), (D))
#define MatrMulMatr5(A, B, C, D, E) MatrMulMatr(MatrMulMatr4((A), (B), (C), (D)), (E))

/* Basic float type */
typedef DOUBLE DBL;
typedef FLOAT FLT;

/* Vector in the space type by 2 coordinates */
typedef struct tagVEC2
{
  FLT X, Y;
} VEC2;

/* Vector in the space type by 3 coordinates */
typedef struct tagVEC
{
  FLT X, Y, Z;
} VEC3;

/* Vector in the space type by 4 coordinates */
typedef struct tagVEC4
{
  FLT X, Y, Z, W;
} VEC4;

/* Matrix type - array in the structure */
typedef struct tagMATR
{
  FLT A[4][4];
} MATR;

/* Swapping 2 double numbers function.
 * ARGUMENTS:
 *   - 2 numbers:
 *       FLT *A, *B;
 * RETURNS VALUE: None.
 */
__inline VOID NumbersSwapF( FLT *A, FLT *B )
{
  FLT tmp;

  tmp = *A, *A = *B, *B = tmp;
} /* End of 'NumbersSwap1' function */

/* Swapping 2 float numbers function.
 * ARGUMENTS:
 *   - 2 numbers:
 *       DBL *A, *B;
 * RETURNS VALUE: None.
 */
__inline VOID NumbersSwapD( DBL *A, DBL *B )
{
  DBL tmp;

  tmp = *A, *A = *B, *B = tmp;
} /* End of 'NumbersSwap2' function */

/* Rmplementation functions */

/* Radius vector from end point by two coordinates macking function.
 * ARGUMENTS:
 *   - Coordinates:
 *       FLT X, Y;
 * RETURNS:
 *   (VEC3) result radius vector.
 */
__inline VEC2 Vec2Set( FLT X, FLT Y )
{
  VEC2 v = {X, Y};

  return v;
} /* End of 'Vec2Set' function */

/* Radius vector from end point with equal two coordinates macking function.
 * ARGUMENTS:
 *   - Coordinates:
 *       FLT A;
 * RETURNS:
 *   (VEC2) result vector.
 */
__inline VEC2 Vec2Set1( FLT A )
{
  VEC2 v = {A, A};

  return v;
} /* End of 'Vec2Set1' function */

/* Radius vector from end point coordinates macking  function.
 * ARGUMENTS:
 *   - Coordinates:
 *       FLT X, Y, Z, D;
 * RETURNS:
 *   (VEC4) result radius vector.
 */
__inline VEC4 Vec4Set( FLT X, FLT Y, FLT Z, FLT D )
{
  VEC4 v = {X, Y, Z, D};

  return v;
} /* End of 'Vec4Set' function */

/* Radius vector from end point with equal four coordinates macking function.
 * ARGUMENTS:
 *   - Coordinates:
 *       FLT A;
 * RETURNS:
 *   (VEC4) result vector.
 */
__inline VEC4 Vec4Set1( FLT A )
{
  VEC4 v = {A, A, A, A};

  return v;
} /* End of 'Vec4Set1' function */

/* 4 coordinates vector from 3 vector coordinates making function.
 * ARGUMENTS:
 *   - Vector:
 *       VEC3 A;
 *   - Scalar:
 *       FLT B;
 * RETURNS:
 *   (VEC4) result radius vector.
 */
__inline VEC4 Vec4Set3( VEC3 A, FLT B )
{
  VEC4 v = {A.X, A.Y, A.Z, B};

  return v;
} /* End of 'Vec4Set3' function */

/* Radius vector from end point coordinates macking  function.
 * ARGUMENTS:
 *   - Coordinates:
 *       FLT X, Y, Z;
 * RETURNS:
 *   (VEC3) result radius vector.
 */
__inline VEC3 Vec3Set( FLT X, FLT Y, FLT Z )
{
  VEC3 v = {X, Y, Z};

  return v;
} /* End of 'Vec3Set' function */

/* Radius vector from end point with equal coordinates macking function.
 * ARGUMENTS:
 *   - Coordinates:
 *       FLT A;
 * RETURNS:
 *   (VEC3) result vector.
 */
__inline VEC3 Vec3Set1( FLT A )
{
  VEC3 v = {A, A, A};

  return v;
} /* End of 'Vec3Set1' function */

/* One vector to another adding function.
 * ARGUMENTS:
 *   - Vectors:
 *       VEC3 V1, V2;
 * RETURNS:
 *   (VEC3) result vector.
 */
__inline VEC3 VecAddVec( VEC3 V1, VEC3 V2 )
{
  return Vec3Set(V1.X + V2.X, V1.Y + V2.Y, V1.Z + V2.Z);
} /* End of 'VecAddVec' function */

/* One vector from another subtracting function.
 * ARGUMENTS:
 *   - Vectors:
 *       VEC3 V1, V2;
 * RETURNS:
 *   (VEC3) result vector.
 */
__inline VEC3 VecSubVec( VEC3 V1, VEC3 V2 )
{
  return Vec3Set(V1.X - V2.X, V1.Y - V2.Y, V1.Z - V2.Z);
} /* End of 'VecSubVec' function */

/* Vector multiplying by number function.
 * ARGUMENTS:
 *   - Vector:
 *       VEC3 V1;
 *   - Number:
 *       FLT N;
 * RETURNS:
 *   (VEC3) result vector.
 */
__inline VEC3 VecMulNum( VEC3 V1, FLT N )
{
  return Vec3Set(V1.X * N, V1.Y * N, V1.Z * N);
} /* End of 'VecMulNum' function */

/* Vector dividing by number function.
 * ARGUMENTS:
 *   - Vector:
 *       VEC3 V1;
 *   - Number:
 *       FLT N;
 * RETURNS:
 *   (VEC3) result vector.
 */
__inline VEC3 VecDivNum( VEC3 V1, FLT N )
{
  return Vec3Set(V1.X / N, V1.Y / N, V1.Z / N);
} /* End of 'VecDivNum' function */

/* Vector invertion function.
 * ARGUMENTS:
 *   - Vector:
 *       VEC3 V1;
 *   - Number:
 *       FLT N;
 * RETURNS:
 *   (VEC3) result vector.
 */
__inline VEC3 VecNeg( VEC3 V )
{
  return Vec3Set(-V.X, -V.Y, -V.Z);
} /* End of 'VecNeg' function */

/* Dot producting function.
 * ARGUMENTS:
 *   - Vectors:
 *       VEC3 V1, V2;
 * RETURNS:
 *   (FLT) result number.
 */
__inline FLT VecDotVec( VEC3 V1, VEC3 V2 )
{
  return V1.X * V2.X + V1.Y * V2.Y + V1.Z * V2.Z; 
} /* End of 'VecDotVec' function */

/* Cross producting function.
 * ARGUMENTS:
 *   - Vectors:
 *       VEC3 V1, V2;
 * RETURNS:
 *   (VEC3) result vector.
 */
__inline VEC3 VecCrossVec( VEC3 V1, VEC3 V2 )
{
  return Vec3Set(V1.Y * V2.Z - V1.Z * V2.Y, V1.Z * V2.X - V1.X * V2.Z, V1.X * V2.Y - V1.Y * V2.X);
} /* End of 'VecCrossVec' function */

/* Vector length counting function.
 * ARGUMENTS:
 *   - Vector:
 *       VEC3 V1;
 * RETURNS:
 *   (FLT) result length.
 */
__inline FLT VecLen( VEC3 V )
{
  FLT len = VecDotVec(V, V);

  if (len == 1 || len == 0)
    return len;
  return sqrt(len);
} /* End of 'VecLen' function */

/* Vector length square counting function.
 * ARGUMENTS:
 *   - Vector:
 *       VEC3 V1;
 * RETURNS:
 *   (FLT) result length square.
 */
__inline FLT VecLen2( VEC3 V )
{
  FLT len = VecDotVec(V, V);

  return len;
} /* End of 'VecLen2' function */

/* Vector normalizing function.
 * ARGUMENTS:
 *   - Vector:
 *       VEC3 V1;
 * RETURNS:
 *   (VEC3) result vector.
 */
__inline VEC3 VecNormalize( VEC3 V )
{
  FLT len = VecDotVec(V, V);

  if (len == 1 || len == 0)
    return V;
  return VecDivNum(V, sqrt(len));
} /* End of 'VecNormalize' function */

/* Point transform function.
 * ARGUMENTS:
 *   - Vector:
 *       VEC3 V1;
 *   - Matrix:
 *       MATR M;
 * RETURNS:
 *   (VEC3) result vector.
 */
__inline VEC3 PointTransform( VEC3 V, MATR M )
{
  return Vec3Set(V.X * M.A[0][0] + V.Y * M.A[1][0] + V.Z * M.A[2][0] + M.A[3][0],
    V.X * M.A[0][1] + V.Y * M.A[1][1] + V.Z * M.A[2][1] + M.A[3][1],
    V.X * M.A[0][2] + V.Y * M.A[1][2] + V.Z * M.A[2][2] + M.A[3][2]);
} /* End of 'PointTransform' function */

/* Vector transform function.
 * ARGUMENTS:
 *   - Vector:
 *       VEC3 V1;
 *   - Matrix:
 *       MATR M;
 * RETURNS:
 *   (VEC3) result vector.
 */
__inline VEC3 VectorTransform( VEC3 V, MATR M )
{
  return Vec3Set(V.X * M.A[0][0] + V.Y * M.A[1][0] + V.Z * M.A[2][0],
    V.X * M.A[0][1] + V.Y * M.A[1][1] + V.Z * M.A[2][1],
    V.X * M.A[0][2] + V.Y * M.A[1][2] + V.Z * M.A[2][2]);
} /* End of 'VectorTransform' function */

/* Vector by matrix multiplication (with homogenious devide) function.
 * ARGUMENTS:
 *   - source vector:
 *       VEC3 V;
 *   - multiplied matrix:
 *       MATR M;
 * RETURNS:
 *   (VEC3) result vector.
 */
__inline VEC3 VecMulMatr( VEC3 V, MATR M )
{
  FLT w = V.X * M.A[0][3] + V.Y * M.A[1][3] + V.Z * M.A[2][3] + M.A[3][3];

  return Vec3Set((V.X * M.A[0][0] + V.Y * M.A[1][0] + V.Z * M.A[2][0] + M.A[3][0]) / w,
                (V.X * M.A[0][1] + V.Y * M.A[1][1] + V.Z * M.A[2][1] + M.A[3][1]) / w,
                (V.X * M.A[0][2] + V.Y * M.A[1][2] + V.Z * M.A[2][2] + M.A[3][2]) / w);
} /* End of 'VecMulMatr' function */

/* Identity matrix */
static MATR UnitMatrix =
{
  {
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1}
  }
};

/* Identity matrix initialization function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (MATR) result matrix.
 */
static __inline MATR MatrIdentity( VOID )
{
  MATR I = UnitMatrix;
  return I;
} /* End of 'MatIdentity' function */

/* Matrix initialization function.
 * ARGUMENTS: 
 *   - Elements of matrix:
 *       FLT A00, A01, A02, A03,
 *        A10, A11, A12, A13,
 *         A20, A21, A22, A23,
 *         A30, A31, A32, A33;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrSet( FLT A00, FLT A01, FLT A02, FLT A03,
              FLT A10, FLT A11, FLT A12, FLT A13,
              FLT A20, FLT A21, FLT A22, FLT A23,
              FLT A30, FLT A31, FLT A32, FLT A33 )
{
  MATR m =
  {
    {
      {A00, A01, A02, A03},
      {A10, A11, A12, A13},
      {A20, A21, A22, A23},
      {A30, A31, A32, A33},
    }
  };

  return m;
} /* End of 'MatrSet' function */

/* Matrix translation function.
 * ARGUMENTS: 
 *   - Vector:
 *       VEC3 T;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrTranslate( VEC3 T )
{
  return MatrSet(1, 0, 0, 0,
                 0, 1, 0, 0,
                 0, 0, 1, 0,
                 T.X, T.Y, T.Z, 1);
} /* End of 'MatrTranslate' functin */

/* Matrix multiplication by number function.
 * ARGUMENTS: 
 *   - Matrix:
 *       MATR M;
 *   - Number:
 *       INT d;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrMulNum( MATR M, INT d )
{
  INT i, j;
  MATR r = {{{0}}};

  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++)
        r.A[i][j] = M.A[i][j] * d;

  return r;
} /* End of 'MatrTranslate' functin */

/* Matrix scalling function.
 * ARGUMENTS:
 *   - Vector:
 *       VEC3 S;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrScale( VEC3 S )
{
  return MatrSet(S.X, 0, 0, 0,
                 0, S.Y, 0, 0,
                 0, 0, S.Z, 0,
                 0, 0, 0, 1);
} /* End of 'MatrTranslate' functin */

/* Matrix rotating around X axis function.
 * ARGUMENTS:
 *   - Angle:
 *       FLT AngleInDegree;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrRotateX( FLT AngleInDegree )
{
  FLT co = cos(Degree2Radian(AngleInDegree)), si = sin(Degree2Radian(AngleInDegree));

  return MatrSet(1, 0, 0, 0,
                 0, co, si, 0,
                 0, -si, co, 0,
                 0, 0, 0, 1);
} /* End of 'MatrRotateX' function */

/* Matrix rotating around Y axis function.
 * ARGUMENTS:
 *   - Angle:
 *       FLT AngleInDegree;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrRotateY( FLT AngleInDegree )
{
  FLT co = cos(Degree2Radian(AngleInDegree)), si = sin(Degree2Radian(AngleInDegree));

  return MatrSet(co, 0, -si, 0,
                 0, 1, 0, 0,
                 si, 0, co, 0,
                 0, 0, 0, 1);
} /* End of 'MatrRotateY' function */

/* Matrix rotating around Z axis function.
 * ARGUMENTS:
 *   - Angle:
 *       FLT AngleInDegree;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrRotateZ( FLT AngleInDegree )
{
  FLT co = cos(Degree2Radian(AngleInDegree)), si = sin(Degree2Radian(AngleInDegree));

  return MatrSet(co, si, 0, 0,
                 -si, co, 0, 0,
                 0, 0, 1, 0,
                 0, 0, 0, 1);
} /* End of 'MatrRotateZ' function */

/* Matrix rotating function.
 * ARGUMENTS:
 *   - Angle:
 *       FLT AngleInDegree;
 *   - Vector:
 *       VEC3 R;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrRotate( FLT AngleInDegree, VEC3 R )
{
  FLT A = D2R(AngleInDegree), si = sin(A), co = cos(A);
  VEC3 V = VecNormalize(R);
  MATR M =
  {
    {
      {co + V.X * V.X * (1 - co),
        V.X * V.Y * (1 - co) + V.Z * si, R.Z * R.X * (1 - co) - R.Y * si, 0},
      {V.X * V.Y * (1 - co) - V.Z * si,
        co + V.Y * V.Y * (1 - co),
        V.Y * V.Z * (1 - co) + V.X * si, 0},
      {V.Z * V.X * (1 - co) + V.Y * si,
        V.Z * V.Y * (1 - co) - V.X * si,
        co + V.Z * V.Z * (1 - co), 0},
      {0, 0, 0, 1}
    }
  };
  return M;
} /* End of 'MatrRotate' function */

/* Matrix multiplying another matrix function.
 * ARGUMENTS:
 *   - Matrix:
 *       MATR M1, M2;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrMulMatr( MATR M1, MATR M2 )
{
  INT i, j, k;
  MATR r = {{{0}}};

  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++)
      for (k = 0; k < 4; k++)
        r.A[i][j] += M1.A[i][k] * M2.A[k][j];

  return r;
} /* End of 'MatrMulMatr' function */

/* Matrix transposing function.
 * ARGUMENTS:
 *   - Matrix:
 *       MATR M;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrTranspose( MATR M )
{
  INT i, j;

  for (i = 0; i < 4; i++)
    for (j = i; j < 4; j++)
        NumbersSwapF(&M.A[i][j], &M.A[j][i]);

  return M;
} /* End of 'MatrTransponse' function */

/* Matrix 3x3 determinate counting function.
 * ARGUMENTS:
 *   - Matrix:
 *       MATR M;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline FLT MatrDeterm3x3( FLT A11, FLT A12, FLT A13,
                   FLT A21, FLT A22, FLT A23,
                   FLT A31, FLT A32, FLT A33 )
{
  return A11 * A22 * A33 + A12 * A23 * A31 + A13 * A21 * A32 -
         A11 * A23 * A32 - A12 * A21 * A33 - A13 * A22 * A31;
} /* End of 'MatrDeterm3x3' function */

/* Matrix 4x4 determinate counting function.
 * ARGUMENTS:
 *   - Matrix:
 *       MATR M;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline FLT MatrDeterm4x4( MATR M )
{
  return
    +M.A[0][0] * MatrDeterm3x3(M.A[1][1], M.A[1][2], M.A[1][3],
                               M.A[2][1], M.A[2][2], M.A[2][3],
                               M.A[3][1], M.A[3][2], M.A[3][3]) +
    -M.A[0][1] * MatrDeterm3x3(M.A[1][0], M.A[1][2], M.A[1][3],
                               M.A[2][0], M.A[2][2], M.A[2][3],
                               M.A[3][0], M.A[3][2], M.A[3][3]) +
    +M.A[0][2] * MatrDeterm3x3(M.A[1][0], M.A[1][1], M.A[1][3],
                               M.A[2][0], M.A[2][1], M.A[2][3],
                               M.A[3][0], M.A[3][1], M.A[3][3]) +
    -M.A[0][3] * MatrDeterm3x3(M.A[1][0], M.A[1][1], M.A[1][2],
                               M.A[2][0], M.A[2][1], M.A[2][2],
                               M.A[3][0], M.A[3][1], M.A[3][2]);
} /* End of 'MatrDeterm4x4' function */

/* Matrix inversing function.
 * ARGUMENTS:
 *   - Matrix:
 *       MATR M;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrInverse( MATR M )
{
  FLT det = MatrDeterm4x4(M);
  MATR r;

  if (det == 0)
    return MatrIdentity();

  /* build adjoint matrix */
  r.A[0][0] =
    +MatrDeterm3x3(M.A[1][1], M.A[1][2], M.A[1][3],
                   M.A[2][1], M.A[2][2], M.A[2][3],
                   M.A[3][1], M.A[3][2], M.A[3][3]) / det;

  r.A[1][0] =
    -MatrDeterm3x3(M.A[1][0], M.A[1][2], M.A[1][3],
                   M.A[2][0], M.A[2][2], M.A[2][3],
                   M.A[3][0], M.A[3][2], M.A[3][3]) / det;

  r.A[2][0] =
    +MatrDeterm3x3(M.A[1][0], M.A[1][1], M.A[1][3],
                   M.A[2][0], M.A[2][1], M.A[2][3],
                   M.A[3][0], M.A[3][1], M.A[3][3]) / det;

  r.A[3][0] =
    -MatrDeterm3x3(M.A[1][0], M.A[1][1], M.A[1][2],
                   M.A[2][0], M.A[2][1], M.A[2][2],
                   M.A[3][0], M.A[3][1], M.A[3][2]) / det;

  r.A[0][1] =
    -MatrDeterm3x3(M.A[0][1], M.A[0][2], M.A[0][3],
                   M.A[2][1], M.A[2][2], M.A[2][3],
                   M.A[3][1], M.A[3][2], M.A[3][3]) / det;

  r.A[1][1] =
    +MatrDeterm3x3(M.A[0][0], M.A[0][2], M.A[0][3],
                   M.A[2][0], M.A[2][2], M.A[2][3],
                   M.A[3][0], M.A[3][2], M.A[3][3]) / det;

  r.A[2][1] =
    -MatrDeterm3x3(M.A[0][0], M.A[0][1], M.A[0][3],
                   M.A[2][0], M.A[2][1], M.A[2][3],
                   M.A[3][0], M.A[3][1], M.A[3][3]) / det;

  r.A[3][1] =
    +MatrDeterm3x3(M.A[0][0], M.A[0][1], M.A[0][2],
                   M.A[2][0], M.A[2][1], M.A[2][2],
                   M.A[3][0], M.A[3][1], M.A[3][2]) / det;

  r.A[0][2] =
    +MatrDeterm3x3(M.A[0][1], M.A[0][2], M.A[0][3],
                   M.A[1][1], M.A[1][2], M.A[1][3],
                   M.A[3][1], M.A[3][2], M.A[3][3]) / det;

  r.A[1][2] =
    -MatrDeterm3x3(M.A[0][0], M.A[0][2], M.A[0][3],
                   M.A[1][0], M.A[1][2], M.A[1][3],
                   M.A[3][0], M.A[3][2], M.A[3][3]) / det;

  r.A[2][2] =
    +MatrDeterm3x3(M.A[0][0], M.A[0][1], M.A[0][3],
                   M.A[1][0], M.A[1][1], M.A[1][3],
                   M.A[3][0], M.A[3][1], M.A[3][3]) / det;

  r.A[3][2] =
    -MatrDeterm3x3(M.A[0][0], M.A[0][1], M.A[0][2],
                   M.A[1][0], M.A[1][1], M.A[1][2],
                   M.A[3][0], M.A[3][1], M.A[3][2]) / det;

  r.A[0][3] =
    -MatrDeterm3x3(M.A[0][1], M.A[0][2], M.A[0][3],
                   M.A[1][1], M.A[1][2], M.A[1][3],
                   M.A[2][1], M.A[2][2], M.A[2][3]) / det;

  r.A[1][3] =
    +MatrDeterm3x3(M.A[0][0], M.A[0][2], M.A[0][3],
                   M.A[1][0], M.A[1][2], M.A[1][3],
                   M.A[2][0], M.A[2][2], M.A[2][3]) / det;

  r.A[2][3] =
    -MatrDeterm3x3(M.A[0][0], M.A[0][1], M.A[0][3],
                   M.A[1][0], M.A[1][1], M.A[1][3],
                   M.A[2][0], M.A[2][1], M.A[2][3]) / det;

  r.A[3][3] =
    +MatrDeterm3x3(M.A[0][0], M.A[0][1], M.A[0][2],
                   M.A[1][0], M.A[1][1], M.A[1][2],
                   M.A[2][0], M.A[2][1], M.A[2][2]) / det;

  return r;
} /* End of 'MatrInverse' function */

/* Setting up observer pos function.
 * ARGUMENTS:
 *   - Vec:
 *       VEC3 Loc, At, Up1;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrView( VEC3 Loc, VEC3 At, VEC3 Up1 )
{
  VEC3 Dir = VecNormalize(VecSubVec(At, Loc)),
    Right = VecNormalize(VecCrossVec(Dir, Up1)),
    Up = VecCrossVec(Right, Dir);
  MATR m =
  {
    {
      {Right.X, Up.X, -Dir.X, 0},
      {Right.Y, Up.Y, -Dir.Y, 0},
      {Right.Z, Up.Z, -Dir.Z, 0},
      {-VecDotVec(Loc, Right), -VecDotVec(Loc, Up), VecDotVec(Loc, Dir), 1}
    }
  };

  return m;
} /* End of 'MatrView' function */

/* Setting ortho projection function.
 * ARGUMENTS:
 *   - References:
 *       FLT Left, Right, Bottom, Top, Near, Far;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrOrtho( FLT Left, FLT Right, FLT Bottom, FLT Top, FLT Near, FLT Far )
{
  return MatrSet(2 / (Right - Left), 0, 0, 0,
    0, 2 / (Top - Bottom), 0, 0,
    0, 0, -2 / (Far - Near), 0,
    -1 * (Right + Left) / (Right - Left), -1 * (Top + Bottom) / (Top - Bottom), - 1 * (Far + Near) / (Far - Near), 1);
} /* End of 'MatrOrtho' function */

/* Setting frustum projection function.
 * ARGUMENTS:
 *   - References:
 *       FLT Left, Right, Bottom, Top, Near, Far;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrFrustum( FLT Left, FLT Right, FLT Bottom, FLT Top, FLT Near, FLT Far )
{
  return MatrSet(2 * Near / (Right - Left), 0, 0, 0,
    0, 2  * Near / (Top - Bottom), 0, 0,
    (Right + Left) / (Right - Left), (Top + Bottom) / (Top - Bottom), -1 * (Far + Near) / (Far - Near), -1,
    0, 0, -2 * Near * Far/ (Far - Near), 0);
} /* End of 'MatrFrustum' function */

#endif /* __mth_h_ */

/* END OF 'mth.h' FILE */