layout(quads, fractional_even_spacing) in;

uniform mat4 MatrWVP;
uniform float AddonFlt0;

out vec3 DC;

void main( void )
{
  float
    t = gl_TessCoord.y * acos(-1),
    p = gl_TessCoord.x * 2 * acos(-1);
  vec3 pp =
    vec3(sin(t) * sin(p),
         cos(t),
         sin(t) * cos(p));

  gl_Position = MatrWVP * vec4(pp * AddonFlt0, 1);
  DC = pp;
}
