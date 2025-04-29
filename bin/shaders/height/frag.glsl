in VS_OUT
{
  vec2 TexCoord;
  vec3 Normal;
  vec3 Pos;
} fs_in;

void main( void )
{
  OutPosId = vec4(fs_in.Pos, 0);
  OutNormalIsShade = vec4(fs_in.Normal, 1);

  OutKaDepth = vec4(Ka, gl_FragCoord.z);
  OutKd = vec4(texture(InColor, fs_in.TexCoord).xyz, 0); 
  OutKsPh = vec4(Ks, Ph);            

  if (IsWireframe)
    OutColor = vec4(1, 1, 1, 1);
  else
    OutColor = vec4(0);  
}   
