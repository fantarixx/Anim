/* FILE NAME: timer.c
 * PROGRAMMER: RP5b
 * LAST UPDATE: 16.02.2023
 * PURPOSE: 3D animation project.
 *          Timer declaration module.
 */

#include "anim/anim.h"

/* Global timer data */
  static DBL
    RP5b_GlobalTime, RP5b_GlobalDeltaTime, /* Global time and interframe interval */
    RP5b_Time, RP5b_DeltaTime,             /* Time with pause and interframe interval */
    RP5b_FPS;                         /* Frames per second value */
  static BOOL
    RP5b_IsPause;                     /* Pause flag */

/* Local timer data */
static UINT64
  RP5b_StartTime,    /* Start program time */
  RP5b_OldTime,      /* Previous frame time */
  RP5b_OldTimeFPS,   /* Old time FPS measurement */
  RP5b_PauseTime,    /* Time during pause period */
  RP5b_TimePerSec,   /* Timer resolution */
  RP5b_FrameCounter; /* Frames counter */

/* Timer initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID RP5b_AnimTimerInit( VOID )
{
  LARGE_INTEGER t;	

  QueryPerformanceFrequency(&t);
  RP5b_TimePerSec = t.QuadPart;
  QueryPerformanceCounter(&t);
  RP5b_StartTime = RP5b_OldTime = RP5b_OldTimeFPS = t.QuadPart;
  RP5b_FrameCounter = 0;
  RP5b_Anim.IsPause = RP5b_IsPause = FALSE;
  RP5b_FPS = 30.0;
  RP5b_PauseTime = 0;
} /* End of 'RP5b_AnimTimerInit' function */

/* Timer update function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID RP5b_AnimTimerResponse( VOID )
{
  LARGE_INTEGER t;

  QueryPerformanceCounter(&t);
  /* Global time */
  RP5b_GlobalTime = (DBL)(t.QuadPart - RP5b_StartTime) / RP5b_TimePerSec;
  RP5b_GlobalDeltaTime = (DBL)(t.QuadPart - RP5b_OldTime) / RP5b_TimePerSec;
  /* Time with pause */
  if (RP5b_IsPause)
  {
    RP5b_DeltaTime = 0;
    RP5b_PauseTime += t.QuadPart - RP5b_OldTime;
  }
  else
  {
    RP5b_DeltaTime = RP5b_GlobalDeltaTime;
    RP5b_Time = (DBL)(t.QuadPart - RP5b_PauseTime - RP5b_StartTime) / RP5b_TimePerSec;
  }
  /* FPS */
  RP5b_FrameCounter++;
  if (t.QuadPart - RP5b_OldTimeFPS > RP5b_TimePerSec)
  {
    RP5b_FPS = RP5b_FrameCounter * RP5b_TimePerSec / (DBL)(t.QuadPart - RP5b_OldTimeFPS);
    RP5b_OldTimeFPS = t.QuadPart;
    RP5b_FrameCounter = 0;
  }
  RP5b_OldTime = t.QuadPart;

  RP5b_Anim.GlobalTime = RP5b_GlobalTime;
  RP5b_Anim.GlobalDeltaTime = RP5b_GlobalDeltaTime;
  RP5b_Anim.DeltaTime = RP5b_DeltaTime;
  RP5b_Anim.Time = RP5b_Time;
  RP5b_Anim.FPS = RP5b_FPS;
} /* End of 'RP5b_AnimTimerResponse' function */

/* END OF 'timer.c' FILE */ 