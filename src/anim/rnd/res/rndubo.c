  /* FILE NAME: rndubo.c
 * PROGRAMMER: RP5b
 * LAST UPDATE: 01.03.2023
 * PURPOSE: 3D animation project.
 *          UBO handle module.
 */

#include <anim/rnd/res/rndres.h>

/* UBOs stock */
rp5bUBO RP5b_RndUBOs[RP5b_MAX_UBOS]; /* Array of UBO */
INT RP5b_RndUBOsSize;                /* UBO array store size */

/* UBO handle initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID RP5b_RndUBOInit( VOID )
{
  RP5b_RndUBOsSize = 0;
} /* End of 'RP5b_RndUBOInit' function */

/* UBO handle deinitialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID RP5b_RndUBOClose( VOID )
{
  INT i;

  for (i = 0; i < RP5b_RndUBOsSize; i++)
    glDeleteBuffers(1, &RP5b_RndUBOs[i].UBOId);
  RP5b_RndUBOsSize = 0;
} /* End of 'RP5b_RndUBOClose' function */

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
INT RP5b_RndUBOCreate( CHAR *Name, UINT BindPoint, INT NumOfBlocks, VOID *Bits )
{
  if (RP5b_RndUBOsSize >= RP5b_MAX_UBOS)
    return -1;
  /* Setup OpenGL UBO */
  glGenBuffers(1, &RP5b_RndUBOs[RP5b_RndUBOsSize].UBOId);
  glBindBuffer(GL_UNIFORM_BUFFER, RP5b_RndUBOs[RP5b_RndUBOsSize].UBOId);
  glBufferData(GL_UNIFORM_BUFFER, NumOfBlocks * 16, NULL, GL_STATIC_DRAW);

  if (Bits != NULL)
    glBufferSubData(GL_UNIFORM_BUFFER, 0, NumOfBlocks * 16, Bits);
  glBindBuffer(GL_UNIFORM_BUFFER, 0);

  /* Add to stock */
  RP5b_RndUBOs[RP5b_RndUBOsSize].Size = NumOfBlocks;
  RP5b_RndUBOs[RP5b_RndUBOsSize].BindPoint = BindPoint;
  strncpy(RP5b_RndUBOs[RP5b_RndUBOsSize].Name, Name, RP5b_STR_MAX - 1);
  return RP5b_RndUBOsSize++;
} /* End of 'RP5b_RndUBOAdd' function */

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
VOID RP5b_RndUBOUpdate( INT UBONo, INT BlocksOffset, INT NumOfBlocks, VOID *Bits )
{
  if (UBONo < 0 || UBONo >= RP5b_RndUBOsSize)
    return;

  /* Update UBO data */
  if (BlocksOffset >= RP5b_RndUBOs[UBONo].Size)
    return;
  if (BlocksOffset < 0)
    BlocksOffset = 0;
  if (NumOfBlocks == 0)
    NumOfBlocks = RP5b_RndUBOs[UBONo].Size;
  if (BlocksOffset + NumOfBlocks >= RP5b_RndUBOs[UBONo].Size)
    NumOfBlocks = RP5b_RndUBOs[UBONo].Size - BlocksOffset;

  glBindBuffer(GL_UNIFORM_BUFFER, RP5b_RndUBOs[UBONo].UBOId);
  glBufferSubData(GL_UNIFORM_BUFFER, BlocksOffset * 16, NumOfBlocks * 16, Bits);
  glBindBuffer(GL_UNIFORM_BUFFER, 0);
} /* End of 'RP5b_RndUBOUpdate' function */

/* UBO apply function.
 * ARGUMENTS:
 *   - UBO number in stock:
 *       INT UBONo;
 * RETURNS: None.
 */
VOID RP5b_RndUBOApply( INT UBONo )
{
  if (UBONo < 0 || UBONo >= RP5b_RndUBOsSize)
    return;

  glBindBufferBase(GL_UNIFORM_BUFFER, RP5b_RndUBOs[UBONo].BindPoint,
    RP5b_RndUBOs[UBONo].UBOId);
} /* End of 'RP5b_RndUBOApply' function */

/* END OF 'rndubo.c' FILE */