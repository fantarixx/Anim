#ifdef RP5b_VERTEX_SHADER
layout(location = 0) in vec3 InPosition;
layout(location = 1) in vec2 InTexCoord;
layout(location = 2) in vec3 InNormal;
layout(location = 3) in vec4 InColor;
#endif // RP5b_VERTEX_SHADER
 
#ifdef RP5b_FRAGMENT_SHADER
layout(location = 0) out vec4 OutColor;
layout(location = 1) out vec4 OutPosId;
layout(location = 2) out vec4 OutNormalIsShade;
layout(location = 3) out vec4 OutKaDepth;
layout(location = 4) out vec4 OutKd;
layout(location = 5) out vec4 OutKsPh;
 
layout(binding = 0) uniform sampler2D InColor;
layout(binding = 1) uniform sampler2D InPosId;
layout(binding = 2) uniform sampler2D InNormalIsShade;
layout(binding = 3) uniform sampler2D InKaDepth;
layout(binding = 4) uniform sampler2D InKd;
layout(binding = 5) uniform sampler2D InKsPh;
 
layout(binding = 0) uniform sampler2D InTextures[6];
#endif // RP5b_FRAGMENT_SHADER

layout (std140, binding = 0) uniform Matrices
{
  mat4 MatrWVP;                /* World * View * Proj matrix */
  mat4 MatrW;                  /* World matrix */
  mat4 MatrWInv;               /* World inversion matrix */
  mat4 MatrVP;                 /* View * Proj matrix */
  mat4 MatrV;                  /* View matrix */
  vec4 CamLoc4;                /* Camera location */
  vec4 CamRight4;              /* Camera right direction */
  vec4 CamUp4;                 /* Camera up direction */
  vec4 CamDir4;                /* Camera forward direction */
  vec4 FrameWHProjDistFar;     /* Frame size and project dist and project farclip */
  vec4 TimeGlobalDeltaGlobal;  /* Time/global time, delta/global delta time */
  vec4 WireframeProjectSize;   /* Wireframe flag and project size */
  vec4 LightDir4;              /* Directional light source */
  vec4 LightColor4;            /* Light color */
  mat4 ShadowMatr;              /* Shadow matrix */
};

#define LightDir LightDir4.xyz
#define LightColor LightColor4.xyz
#define CamLoc CamLoc4.xyz
#define CamRight CamRight4.xyz
#define CamDir CamDir4.xyz
#define CamUp CamUp4.xyz
#define IsWireframe (WireframeProjectSize.x != 0)
#define ProjSize WireframeProjectSize.y
#define Time TimeGlobalDeltaGlobal.x
#define GTime TimeGlobalDeltaGlobal.y
#define FrameW FrameWHProjDistFar.x
#define FrameH FrameWHProjDistFar.y
#define ProjDist FrameWHProjDistFar.z

layout (std140, binding = 1) uniform Material
{
  vec4 KaTrans4;       /* Ambient and transparensy */
  vec4 Kd4;            /* Diffuse */
  vec4 KsPh4;          /* Specular + Phong */
  vec4 TexFlags0123;   /* Textures 0 - 3 presence flag */
  vec4 TexFlags4567;   /* Textures 4 - 7 presence flag */
};

#define Ka KaTrans4.xyz
#define Kd Kd4.xyz
#define Ks KsPh4.xyz
#define Ph KsPh4.w
#define Trans KaTrans4.w
#define Texture0 TexFlags0123.x != 0
#define Texture1 TexFlags0123.y != 0
#define Texture2 TexFlags0123.z != 0
#define Texture3 TexFlags0123.w != 0
#define Texture4 TexFlags4567.x != 0
#define Texture5 TexFlags4567.y != 0
#define Texture6 TexFlags4567.z != 0
#define Texture7 TexFlags4567.w != 0

mat4 ortho( float Left, float Right, float Bottom, float Top, float Near, float Far )
{
  return mat4(vec4(2 / (Right - Left), 0, 0, 0),
    vec4(0, 2 / (Top - Bottom), 0, 0),
    vec4(0, 0, -2 / (Far - Near), 0),
    vec4(-1 * (Right + Left) / (Right - Left), -1 * (Top + Bottom) / (Top - Bottom), -1 * (Far + Near) / (Far - Near), 1));
}

mat4 MatrScale( vec3 S )
{
  return mat4(S.x, 0, 0, 0,
                 0, S.y, 0, 0,
                 0, 0, S.z, 0,
                 0, 0, 0, 1);
}

mat4 MatrTranslate( vec3 T )
{
  return mat4(1, 0, 0, 0,
                 0, 1, 0, 0,
                 0, 0, 1, 0,
                 T.x, T.y, T.z, 1);
}
