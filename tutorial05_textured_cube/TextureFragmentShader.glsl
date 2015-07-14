
#version 330 core

in vec2 UV;

out vec3 color;

uniform sampler2D textureSampler;

void main()
{
	vec2 uv = vec2(UV.x, 1.0f-UV.y);
	color = texture(textureSampler, UV).rgb;
}
