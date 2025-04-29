out VS_OUT
{
  vec2 TexCoord;
  vec3 Normal;
  vec3 Pos;
} vs_out;

void main( void )
{
  gl_Position = MatrWVP * vec4(InPosition, 1);
  vs_out.Pos = (MatrW * vec4(InPosition, 1)).xyz;
  vs_out.Normal = mat3(MatrWInv) * InNormal;
  vs_out.TexCoord = InTexCoord;
}
