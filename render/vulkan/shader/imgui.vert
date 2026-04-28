#version 450

layout(location = 0) in vec2 in_pos;
layout(location = 1) in vec2 in_uv;
layout(location = 2) in vec4 in_col;

layout(location = 0) out vec2 frag_uv;
layout(location = 1) out vec4 frag_col;

layout(push_constant) uniform Push
{
  vec2 display_pos;
  vec2 display_size;
  vec2 framebuffer_scale;
  vec2 _pad0;
} pc;

void main()
{
  vec2 p = (in_pos - pc.display_pos) / pc.display_size;
  gl_Position = vec4(p * 2.0 - 1.0, 0.0, 1.0);

  frag_uv = in_uv;
  frag_col = in_col;
}
