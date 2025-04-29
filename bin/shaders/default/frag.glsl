in VS_OUT
{
  vec4 Color;
  vec2 TexCoords;
  vec3 Normal;
  vec3 Pos;
} fs_in;

void main( void )
{
  OutPosId = vec4(fs_in.Pos, 0);
  OutNormalIsShade = vec4(fs_in.Normal, 1);
  OutKaDepth = vec4(Ka, gl_FragCoord.z);

  vec3 diff = Kd; 
  if (Texture0)
  {
    vec4 tc = texture(InColor, fs_in.TexCoords) * (1, -1);
    diff *= tc.rgb;
  }        
  OutKd = vec4(diff, 0);

  OutKsPh = vec4(Ks, Ph);
  OutColor = fs_in.Color;        
}   