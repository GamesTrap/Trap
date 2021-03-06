#language glsl
#shader vertex
layout(location = 0) in vec3 Position;
layout(location = 1) in vec4 Color;
layout(location = 2) in vec2 UV;

layout(location = 3) out vec4 vColor;
layout(location = 4) out vec2 vUV;

layout(std140, binding = 0) uniform MatrixBuffer
{
	mat4 sys_ProjectionMatrix;
	mat4 sys_ViewMatrix;
	mat4 sys_ModelMatrix;
} Matrices;

void main()
{
	gl_Position = Matrices.sys_ProjectionMatrix * Matrices.sys_ViewMatrix * Matrices.sys_ModelMatrix * vec4(Position, 1.0f);
	vColor = Color;
	vUV = UV;
}

#shader fragment
layout(location = 0) out vec4 FragColor;

layout(location = 3) in vec4 vColor;
layout(location = 4) in vec2 vUV;

layout(binding = 0) uniform sampler2D Texture;

void main()
{
	FragColor = texture(Texture, vUV);
}