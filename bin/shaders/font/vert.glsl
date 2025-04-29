out vec2 DrawTexCoord;

void main( void )
{                                                                                                            
  gl_Position = MatrTranslate(vec3(1.37, 0, 0)) * ortho(0, FrameW, -FrameH, 0, -1, 1) * MatrScale(vec3(66)) * MatrW * vec4(InPosition, 1); 
  DrawTexCoord = InTexCoord;
}
