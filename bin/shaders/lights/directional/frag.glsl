layout(location = 8) uniform sampler2D ShadowMap;

void main( void )
{
  ivec2 sc = ivec2(gl_FragCoord.xy);
  vec4 Nis = texelFetch(InNormalIsShade, sc, 0);
  vec4 Color = texelFetch(InColor, sc, 0);
  if (Nis.w == 0)
    OutColor = Color;
  else
  {
    vec3 Pos = texelFetch(InPosId, sc, 0).xyz;
    vec3 N = normalize(Nis.xyz);
    vec3 MtlKd = texelFetch(InKd, sc, 0).xyz;
    vec4 MtlKsPh = texelFetch(InKsPh, sc, 0);
    vec3 MtlKs = MtlKsPh.xyz;
    float MtlPh = MtlKsPh.w;

    vec3 L = normalize(vec3(1, 2, 3));                     
    vec3 LC = vec3(1, 1, 1);
                               
    vec3 color = vec3(0);                                  
    vec3 V = normalize(Pos - CamLoc);                        
    N = faceforward(N, V, N);
                                                                                        
    // Diffuse                                                 
    color += max(0, dot(N, L)) * MtlKd * LC;                
                                                           
    // Specular                                            
    vec3 R = reflect(V, N);                                
    color += pow(max(0, dot(R, L)), MtlPh) * MtlKs * LC;         
    
    // Shadow cast
    vec3 p = ((ShadowMatr * vec4(Pos.xyz, 1)).xyz + 1) / 2;
    float shadow = 1;
    if (p.x > 0 && p.y > 0 && p.x < 1 && p.y < 1 && p.z > 0 && p.z < 1)
    {
      shadow = 0.8;
      if (texture(ShadowMap, p.xy).r > p.z)
        shadow = 0.29;
    }
    OutColor = vec4(color * shadow, 1);
  }  
}  
