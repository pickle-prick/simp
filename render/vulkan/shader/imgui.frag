#version 450

layout(location = 0) in vec2 frag_uv;
layout(location = 1) in vec4 frag_col;

layout(location = 0) out vec4 out_color;

layout(set = 0, binding = 0) uniform sampler2D tex_sampler;

vec3 srgb_to_linear(vec3 c)
{
  return mix(c / 12.92, pow((c + 0.055) / 1.055, vec3(2.4)), greaterThan(c, vec3(0.04045)));
}

void main()
{
  vec4 tex = texture(tex_sampler, frag_uv);

  vec4 col;
  col.rgb = srgb_to_linear(frag_col.rgb) * tex.rgb;
  col.a = frag_col.a * tex.a;

  out_color = col;
}
