void main( void )
{
  OutColor = vec4(texelFetch(InColor, ivec2(gl_FragCoord.xy), 0).rgb, 1);
}

