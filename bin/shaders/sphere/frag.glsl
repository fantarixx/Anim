in vec4 DrawColor;
in vec3 DrawPos;
in vec3 DrawNormal;
in vec2 DrawTexCoord;

in vec3 DC;
in vec2 UV;

uniform vec3 CamLoc, CamDir;

void main( void )
{
  if (IsWireframe)
  {
    OutColor = vec4(1, 1, 1, 1);
    return;
  }
  float nl = max(0.1, dot(DC, normalize(-vec3(CamDir))));
  OutColor = vec4(vec3(nl) * vec3(1, 0, 0), 1);
}

