layout(location = 0) in vec3 aPos;
layout(location = 1) in vec4 aColor;
layout(location = 2) in vec2 aUV;
layout(location = 3) in float aTexIndex;

out vec4 v_Color;
out vec2 v_UV;
out float v_TexIndex;

uniform mat4 u_ViewProjection;

void main()
{
    v_Color = aColor;
    v_UV = aUV;
    v_TexIndex = aTexIndex;
    gl_Position = u_ViewProjection * vec4(aPos, 1.0);
}
