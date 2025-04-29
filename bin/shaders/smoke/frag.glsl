in VS_OUT
{
  vec2 TexCoord;
  vec4 Color;
} fs_in;   

void main( void )
{
  if (IsWireframe)
  {
    OutColor = vec4(1);
    return;
  }
  OutPosId = vec4(0);          
  OutNormalIsShade = vec4(0);
  OutKaDepth = vec4(Ka, gl_FragCoord.z);           
  OutKd = vec4(Kd, 0);             
  OutKsPh = vec4(Ks, Ph);         
  vec4 tc = texture(InColor, fs_in.TexCoord);      
  OutColor = tc * fs_in.Color;  
}                