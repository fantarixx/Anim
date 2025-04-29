#define N 25

layout(points) in;
layout(triangle_strip, max_vertices = N * 4) out;

out VS_OUT
{
  vec2 TexCoord;
  vec4 Color;
} vs_out;

vec3 Rot( float X, float Y, float Alpha )
{
  float a = radians(Alpha);

  return (cos(a) * X - sin(a) * Y) * CamRight + (sin(a) * X + cos(a) * Y) * CamUp;
}

void main( void )
{
  float
    s = 1, a = 0,
    max_height = 6,
    full_time = 5,
    alpha_border = 0.18,
    col[2] = {0.2, 0.3};
  vec3 p1 = gl_in[0].gl_Position.xyz, p,
    colors[3] = {vec3(1, 1, 0), vec3(1, 0, 0), vec3(0.1)};

  for (int i = 0; i < N; i++)
  {
    p = p1 + vec3(0, max_height / full_time, 0) * mod(Time + full_time * i / N, full_time);
    float t = mod(Time + full_time * i / N, full_time) / full_time;
    
    a = Time * (47 + 8 * sin(i + 0.12 * sin(Time * 0.2))) * (i % 2 * 2 - 1);
    
    if (t < col[0])
      vs_out.Color.rgb = mix(colors[0], colors[1] / col[0], t / col[0]); 
    else if (t < col[1])
      vs_out.Color.rgb = mix(colors[1], colors[2], (t - col[0]) / (col[1] - col[0])); 
    else
      vs_out.Color.rgb = colors[2];

    if (t < 0.2)
      vs_out.Color.a = t / 0.2;
    else if (t < alpha_border)
      vs_out.Color.a = 1;
    else
      vs_out.Color.a = 1 - (t - alpha_border) / (1 - alpha_border);
    
    if (t < 0.5)
      s = mix(0.11, 1.0, t / 0.5);
    else
      s = mix(1.0, 2.0, (t - 0.5) / 0.5);
    
    vs_out.TexCoord = vec2(0, 1);
    gl_Position = MatrWVP * vec4(p + Rot(-1, 1, a) * s, 1);
    EmitVertex();
    vs_out.TexCoord = vec2(0, 0);
    gl_Position = MatrWVP * vec4(p + Rot(-1, -1, a) * s, 1);
    EmitVertex();
    vs_out.TexCoord = vec2(1, 1);
    gl_Position = MatrWVP * vec4(p + Rot(1, 1, a) * s, 1);
    EmitVertex();
    vs_out.TexCoord = vec2(1, 0);
    gl_Position = MatrWVP * vec4(p + Rot(1, -1, a) * s, 1);
    EmitVertex();
    EndPrimitive();
    p += vec3(0, 0.5, 0);
  }
}
	