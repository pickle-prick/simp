#version 450
// bloom_down.frag

layout(location = 0) in vec2 in_uv;
layout(binding = 0) uniform sampler2D src_texture;

layout(push_constant) uniform PushConstants {
  vec2 src_texel_size; // 1.0 / (width, height) of the SOURCE texture
  float threshold;
} pc;

layout(location = 0) out vec4 out_color;

void main()
{
  vec2 src_uv = in_uv;
  float x = pc.src_texel_size.x;
  float y = pc.src_texel_size.y;

  // Take 13 samples around the center.
  // We rely on hardware bilinear filtering, so we actually get info from 36 pixels!
  vec3 a = texture(src_texture, vec2(src_uv.x - 2*x, src_uv.y + 2*y)).rgb;
  vec3 b = texture(src_texture, vec2(src_uv.x,       src_uv.y + 2*y)).rgb;
  vec3 c = texture(src_texture, vec2(src_uv.x + 2*x, src_uv.y + 2*y)).rgb;

  vec3 d = texture(src_texture, vec2(src_uv.x - 2*x, src_uv.y)).rgb;
  vec3 e = texture(src_texture, vec2(src_uv.x,       src_uv.y)).rgb;
  vec3 f = texture(src_texture, vec2(src_uv.x + 2*x, src_uv.y)).rgb;

  vec3 g = texture(src_texture, vec2(src_uv.x - 2*x, src_uv.y - 2*y)).rgb;
  vec3 h = texture(src_texture, vec2(src_uv.x,       src_uv.y - 2*y)).rgb;
  vec3 i = texture(src_texture, vec2(src_uv.x + 2*x, src_uv.y - 2*y)).rgb;

  vec3 j = texture(src_texture, vec2(src_uv.x - x, src_uv.y + y)).rgb;
  vec3 k = texture(src_texture, vec2(src_uv.x + x, src_uv.y + y)).rgb;
  vec3 l = texture(src_texture, vec2(src_uv.x - x, src_uv.y - y)).rgb;
  vec3 m = texture(src_texture, vec2(src_uv.x + x, src_uv.y - y)).rgb;

  // Apply specific weights to smooth out the image
  vec3 downsample = e*0.125;
  downsample += (a+c+g+i)*0.03125;
  downsample += (b+d+f+h)*0.0625;
  downsample += (j+k+l+m)*0.125;

  // Optional Thresholding: If this is the VERY FIRST downsample (Mip 0 to Mip 1),
  // you would optionally subtract 1.0 from downsample here so ONLY bright things glow.
  if(pc.threshold > 0.0)
  {
    float brightness = max(downsample.r, max(downsample.g, downsample.b));
    float contribution = max(0.0, brightness-pc.threshold);
    contribution /= max(brightness, 0.00001);
    downsample *= contribution;
  }

  out_color = vec4(downsample, 1.0);
}
