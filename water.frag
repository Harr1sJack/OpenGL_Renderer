#version 330 core

out vec4 FragColor;

in vec3 color;
in vec2 texCoord;
in vec3 Normal;
in vec3 crntPos;

uniform vec4 lightColor;

vec4 waterColor = vec4(0.173f, 0.216f, 0.230f,1.0f);

vec4 DirectionalLight()
{
	float ambient = 0.2f;
	float specularLight = 0.5f;

	vec3 normals = normalize(Normal);
	vec3 lightdir = normalize(vec3(0.0f,1.0f,0.0f));
	float diffuse = max(dot(normals,lightdir),0); 

	return waterColor * lightColor * (diffuse + ambient);
}

void main()
{
	vec3 normals = normalize(Normal);
    FragColor = waterColor * lightColor;
}