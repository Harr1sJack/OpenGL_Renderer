#version 330 core

out vec4 FragColor;

in vec3 color;
in vec2 texCoord;
in vec3 Normal;
in vec3 crntPos;


uniform sampler2D diffuse0;
uniform sampler2D specular0;
uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;
uniform vec3 bgColor;

vec4 PointLight()
{
	vec3 lightvec = lightPos - crntPos;
	float dist = length(lightvec);
	float a = 0.1;
	float b = 0.1;
	float  intensity = 1 / (a * dist * dist * b * dist + 1.0f);

	float ambient = 0.2f;
	float specularLight = 0.5f;

	vec3 normals = normalize(Normal);
	vec3 lightdir = normalize(lightvec);
	float diffuse = max(dot(normals,lightdir),0.0f); 

	vec3 viewdir = normalize(camPos - crntPos);
	vec3 reflectiondir = reflect(-lightdir,normals);
	float specAmount = pow(max(dot(viewdir,reflectiondir),0.0f),16);
	float specular = specAmount * specularLight;
	return texture(diffuse0,texCoord) * lightColor * (diffuse * intensity + ambient) 
	+ texture(specular0,texCoord).r * specular * intensity;
}

vec4 DirectionalLight()
{
	float ambient = 0.2f;
	float specularLight = 0.5f;

	vec3 normals = normalize(Normal);
	vec3 lightdir = normalize(vec3(1.0f,1.0f,0.0f));
	float diffuse = max(dot(normals,lightdir),0.0f); 

	vec3 viewdir = normalize(camPos - crntPos);
	vec3 reflectiondir = reflect(-lightdir,normals);
	float specAmount = pow(max(dot(viewdir,reflectiondir),0.0f),16);
	float specular = specAmount * specularLight;
	return texture(diffuse0,texCoord) * lightColor * (diffuse + ambient) + texture(specular0,texCoord).r * specular;
}

vec4 SpotLight()
{
	float outercone = 0.90f;
	float innercone = 0.95f;
	float ambient = 0.2f;
	float specularLight = 0.5f;

	vec3 normals = normalize(Normal);
	vec3 lightdir = normalize(lightPos - crntPos);
	float diffuse = max(dot(normals,lightdir),0.0f); 

	vec3 viewdir = normalize(camPos - crntPos);
	vec3 reflectiondir = reflect(-lightdir,normals);
	float specAmount = pow(max(dot(viewdir,reflectiondir),0.0f),16);
	float specular = specAmount * specularLight;
	float angle = dot(vec3(0.0f,-1.0f,0.0f),-lightdir);
	float intensity = clamp((angle-outercone)/(innercone-outercone),0.0f,1.0f);

	return texture(diffuse0,texCoord) * lightColor * (diffuse * intensity + ambient) +
	texture(specular0,texCoord).r * specular * intensity;
}

float near = 0.01f;
float far = 100.0f;

float LinearizeDepth(float depth)
{
	return (3.0f * near * far ) / (far + near - (depth * 2.0f - 1.0f) * (far - near));
}

float LogisticDepth(float depth,float steepness = 0.5f,float offset = 5.0f) 
{
	float zVal = LinearizeDepth(depth);
	return (1 / (1 + exp(-steepness * (zVal - offset))));
}

void main()
{
	float depth = LogisticDepth(gl_FragCoord.z);
	FragColor = PointLight(); // * (1.0f - depth) + vec4(depth * bgColor,1.0f);
}

