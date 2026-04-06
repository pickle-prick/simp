#version 450
// bloom_up.frag

layout(location = 0) in vec2 in_uv;
layout(set = 0, binding = 0) uniform sampler2D src_texture; // The smaller mip level

layout(push_constant) uniform PushConstants {
  vec2 src_texel_size;
  float filter_radius; // Controls how wide the glow spreads (try 0.005)
} pc;

layout(location = 0) out vec4 out_color;

void main() {
  // The filter radius dictates the distance between samples
  float x = pc.filter_radius*pc.src_texel_size.x;
  float y = pc.filter_radius*pc.src_texel_size.y;

  // Take 9 samples around the current pixel
  vec3 a = texture(src_texture, vec2(in_uv.x - x, in_uv.y + y)).rgb;
  vec3 b = texture(src_texture, vec2(in_uv.x,     in_uv.y + y)).rgb;
  vec3 c = texture(src_texture, vec2(in_uv.x + x, in_uv.y + y)).rgb;

  vec3 d = texture(src_texture, vec2(in_uv.x - x, in_uv.y)).rgb;
  vec3 e = texture(src_texture, vec2(in_uv.x,     in_uv.y)).rgb;
  vec3 f = texture(src_texture, vec2(in_uv.x + x, in_uv.y)).rgb;

  vec3 g = texture(src_texture, vec2(in_uv.x - x, in_uv.y - y)).rgb;
  vec3 h = texture(src_texture, vec2(in_uv.x,     in_uv.y - y)).rgb;
  vec3 i = texture(src_texture, vec2(in_uv.x + x, in_uv.y - y)).rgb;

  // Apply tent filter weights
  vec3 upsample = e*4.0;
  upsample += (b+d+f+h)*2.0;
  upsample += (a+c+g+i)*1.0;
  upsample *= 1.0 / 16.0;

  out_color = vec4(upsample, 1.0);
}
