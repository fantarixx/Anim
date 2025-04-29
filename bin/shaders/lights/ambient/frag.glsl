void main( void )
{
  ivec2 sc = ivec2(gl_FragCoord.xy); 
  vec4 Nis = texelFetch(InNormalIsShade, sc, 0);
  if (Nis.w == 0)
    return;
  else
    OutColor = vec4(min(texelFetch(InKaDepth, sc, 0).xyz, vec3(0.1)) , 1);
}  
