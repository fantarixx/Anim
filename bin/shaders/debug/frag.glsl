in vec4 DrawColor;

void main( void )
{
  OutPosId = vec4(0, 0, 0, 0);
  OutNormalIsShade = vec4(0, 0, 1, 0);
  OutKaDepth = vec4(1, 1, 1, 0);
 
  OutKd = vec4(0, 0, 0, 0);

  OutKsPh = vec4(0, 0, 0, 0);
  	
  OutColor = DrawColor;
}