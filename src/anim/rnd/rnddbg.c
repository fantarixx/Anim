/* FILE NAME: rnddbg.h
 * PROGRAMMER: RP5b
 * LAST UPDATE: 16.02.2023
 * PURPOSE: 3D animation project.
 *          Debug handle module.
 */

#include <stdio.h>

#include "anim/rnd/rnd.h"

/* Debug output function.
 * ARGUMENTS:
 *   - source APi or device:
 *      UINT Source;
 *   - error type:
 *      UINT Type;
 *   - error message id:
 *      UINT Id, 
 *   - message severity:
 *      UINT severity, 
 *   - message text length:
 *      INT Length, 
 *   - message text:
 *      CHAR *Message, 
 *   - user addon parameters pointer:
 *      VOID *UserParam;
 * RETURNS: None.
 */
VOID APIENTRY glDebugOutput( UINT Source, UINT Type, UINT Id, UINT Severity,
                             INT Length, const CHAR *Message, const VOID *UserParam )
{
  INT len = 0;
  static CHAR Buf[10000];

  /* Ignore non-significant error/warning codes */
  if (Id == 131169 || Id == 131185 || Id == 131218 || Id == 131204)
    return;
  len += sprintf(Buf + len, "Debug message (%i) %s\n", Id, Message);

  switch (Source)
  {
  case GL_DEBUG_SOURCE_API:
    len += sprintf(Buf + len, "Source: API\n");
    break;
  case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
    len += sprintf(Buf + len, "Source: Window System\n");
    break;
  case GL_DEBUG_SOURCE_SHADER_COMPILER:
    len += sprintf(Buf + len, "Source: Shader Compiler\n");
    break;
  case GL_DEBUG_SOURCE_THIRD_PARTY:
    len += sprintf(Buf + len, "Source: Third Party\n");
    break;
  case GL_DEBUG_SOURCE_APPLICATION:
    len += sprintf(Buf + len, "Source: Application");
    break;
  case GL_DEBUG_SOURCE_OTHER:
    len += sprintf(Buf + len, "Source: Other");
    break;
  }
  len += sprintf(Buf + len, "\n");

  switch (Type)
  {
  case GL_DEBUG_TYPE_ERROR:
    len += sprintf(Buf + len, "Type: Error");
    break;
  case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
    len += sprintf(Buf + len, "Type: Deprecated Behaviour");
    break;
  case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
    len += sprintf(Buf + len, "Type: Undefined Behaviour");
    break; 
  case GL_DEBUG_TYPE_PORTABILITY:
    len += sprintf(Buf + len, "Type: Portability");
    break;
  case GL_DEBUG_TYPE_PERFORMANCE:
    len += sprintf(Buf + len, "Type: Performance");
    break;
  case GL_DEBUG_TYPE_MARKER:
    len += sprintf(Buf + len, "Type: Marker");
    break;
  case GL_DEBUG_TYPE_PUSH_GROUP:
    len += sprintf(Buf + len, "Type: Push Group");
    break;
  case GL_DEBUG_TYPE_POP_GROUP:
    len += sprintf(Buf + len, "Type: Pop Group");
    break;
  case GL_DEBUG_TYPE_OTHER:
    len += sprintf(Buf + len, "Type: Other");
    break;
  }
  len += sprintf(Buf + len, "\n");

  switch (Severity)
  {
  case GL_DEBUG_SEVERITY_HIGH:
    len += sprintf(Buf + len, "Severity: high");
    break;
  case GL_DEBUG_SEVERITY_MEDIUM:
    len += sprintf(Buf + len, "Severity: medium");
    break;
  case GL_DEBUG_SEVERITY_LOW:
    len += sprintf(Buf + len, "Severity: low");
    break;
  case GL_DEBUG_SEVERITY_NOTIFICATION:
    len += sprintf(Buf + len, "Severity: notification");
    break;
  }
  len += sprintf(Buf + len, "\n\n");

  OutputDebugString(Buf);
} /* End of 'glDebugOutput' function */

/* END OF 'rnddbg.c' FILE */