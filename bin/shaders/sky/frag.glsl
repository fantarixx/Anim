void main( void )
{
  float Wp, Hp;

  Wp = Hp = ProjSize;
  if (FrameW > FrameH)
    Wp *= float(FrameW) / FrameH;
  else
    Hp *= FrameH / float(FrameW);

  float 
    xp = gl_FragCoord.x * Wp / FrameW - Wp / 2,
    yp = gl_FragCoord.y * Hp / FrameH - Hp / 2;

  vec3 D = normalize(CamDir * ProjDist + CamRight * xp + CamUp * yp);
  
  vec2 uv = vec2(atan(D.x, D.z) / (2 * acos(-1)), acos(-D.y) / acos(-1));
  OutKaDepth = vec4(Ka, gl_FragCoord.z);
  OutKd = vec4(Kd, 0);
  OutPosId = vec4(0);
  OutNormalIsShade = vec4(0);
            
  OutKsPh = vec4(Ks, Ph);
  OutColor = vec4(texture(InColor, uv).xyz, 1);
}   
