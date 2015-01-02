#define GE_LIGHT_HAVE_SHADOW 1

struct ge_struct_Light {
	int flags;
	vec4 position;
	vec4 target;
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	float spotCutoff;
	float spotCosCutoff;
	float spotExponent;
	float attenuation;
	vec3 vector;
	vec3 targetVector;
	float CosOuterConeAngle;
	float CosInnerMinusOuterAngle;
};
struct ge_struct_material {
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
};

// Lights
uniform int ge_DynamicLightsCount;
uniform int ge_StaticLightsCount;
uniform ge_struct_Light ge_StaticLights[8];
uniform ge_struct_Light ge_DynamicLights[];
uniform sampler2DArray ge_LightShadows[8];

// Materials
uniform ge_struct_material ge_FrontMaterial;
uniform sampler2D ge_Texture;

uniform float ge_Time;
uniform float ge_ScreenRatio;
uniform int ge_HasTexture;
uniform vec3 ge_CameraPosition;

smooth in vec3 ge_TexCoord0;
out vec4 ge_FragColor;

smooth in vec4 ge_Color;
#define ge_FragData gl_FragData
#define ge_FragCoord gl_FragCoord