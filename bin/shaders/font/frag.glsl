in vec2 DrawTexCoord;

void main( void )
{  
  OutPosId = vec4(0);
  OutNormalIsShade = vec4(0);
  OutKaDepth = vec4(Ka, gl_FragCoord.z);

  vec4 tc = texture(InColor, DrawTexCoord);
  if (tc.a < 0.1)
    discard;
  OutKd = vec4(0); 

  OutKsPh = vec4(0);
  OutColor = vec4(tc.rgb, 0);          

  if (IsWireframe)
  {
    OutColor = vec4(1, 1, 1, 1);
    return;
  }
}   
