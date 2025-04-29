layout(vertices = 4) out;

uniform mat4 MatrW;
uniform vec3 CamLoc;
uniform float AddonFlt0;

void main( void )
{
  float
    d = distance(CamLoc, vec3(MatrW[3])) - AddonFlt0,
    a = 1, b = 5,
    minn = 5, maxn = 30,
    n = d > b ? minn : d < a ? maxn : (d - a) / (b - a) * (minn - maxn) + maxn;

  gl_out[gl_InvocationID].gl_Position =  gl_in[gl_InvocationID].gl_Position;
  gl_TessLevelOuter[0] = n;
  gl_TessLevelOuter[1] = n;
  gl_TessLevelOuter[2] = n;
  gl_TessLevelOuter[3] = n;
  gl_TessLevelInner[0] = n;
  gl_TessLevelInner[1] = n;
  /*
  int n = 20;
  gl_TessLevelOuter[0] = n;
  gl_TessLevelOuter[1] = n;
  gl_TessLevelOuter[2] = n;
  gl_TessLevelOuter[3] = n;
  gl_TessLevelInner[0] = n;
  gl_TessLevelInner[1] = n;
  */
}
