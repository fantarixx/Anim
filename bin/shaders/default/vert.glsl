out VS_OUT
{
  vec4 Color;
  vec2 TexCoords;
  vec3 Normal;
  vec3 Pos;
} vs_out;

void main( void )
{
  gl_Position = MatrWVP * vec4(InPosition, 1);
  vs_out.Color = InColor;
  vs_out.Pos = (MatrW * vec4(InPosition, 1)).xyz;
  vs_out.Normal = mat3(MatrWInv) * InNormal;
  vs_out.TexCoords = InTexCoord;
}
