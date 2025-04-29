layout(points) in;
layout(line_strip, max_vertices = 128) out;

out vec4 DrawColor;

vec4 Set( vec3 p )
{
  return MatrWVP * inverse(ShadowMatr) * vec4(p, 1);
}


void main( void )
{
  DrawColor = vec4(1, 0, 0, 1);
  gl_Position = MatrWVP * vec4(0, 0, 0, 1);
  EmitVertex();
  gl_Position = MatrWVP * vec4(1, 0, 0, 0);
  EmitVertex();
  EndPrimitive();

  DrawColor = vec4(0, 1, 0, 1);
  gl_Position = MatrWVP * vec4(0, 0, 0, 1);
  EmitVertex();
  gl_Position = MatrWVP * vec4(0, 8, 0, 1);
  EmitVertex();
  EndPrimitive();

  DrawColor = vec4(0, 0, 1, 1);
  gl_Position = MatrWVP * vec4(0, 0, 0, 1);
  EmitVertex();
  gl_Position = MatrWVP * vec4(0, 0, 8, 0);
  EmitVertex();
  EndPrimitive();

  DrawColor = vec4(0.5, 0.8, 0.5, 1);
  int r = 11;
  for (int i = -r; i <= r; i++)
  {
    float h = 0.1;
    gl_Position = MatrWVP * vec4(-r, h, i, 1);
    EmitVertex();
    gl_Position = MatrWVP * vec4(r, h, i, 1);
    EmitVertex();
    EndPrimitive();
    gl_Position = MatrWVP * vec4(i, h, r, 1);
    EmitVertex();
    gl_Position = MatrWVP * vec4(i, h, -r, 1);
    EmitVertex();
    EndPrimitive();
  }


  DrawColor = vec4(1, 1, 0, 1);
  vec3
    p[8] =
    {
      vec3(-1, -1, -1),
      vec3(1, -1, -1),
      vec3(-1, -1, 1),
      vec3(1, -1, 1),

      vec3(-1, 1, -1),
      vec3(1, 1, -1),
      vec3(-1, 1, 1),
      vec3(1, 1, 1),
    };
  int e[] =
  {
    0, 1,
    1, 3,
    3, 2,
    2, 0,

    4, 5,
    5, 7,
    7, 6,
    6, 4,

    0, 4,
    1, 5,
    2, 6,
    3, 7,
  };
  for (int i = 0; i < e.length(); i++)
  {
    gl_Position = Set(p[e[i]]);
    EmitVertex();
    i++;
    gl_Position = Set(p[e[i]]);
    EmitVertex();
    EndPrimitive();
  }
}