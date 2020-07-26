// Generate a procedural planet and orbiting moon. Use layers of (improved)
// Perlin noise to generate planetary features such as vegetation, gaseous
// clouds, mountains, valleys, ice caps, rivers, oceans. Don't forget about the
// moon. Use `animation_seconds` in your noise input to create (periodic)
// temporal effects.
//
// Uniforms:
uniform mat4 view;
uniform mat4 proj;
uniform float animation_seconds;
uniform bool is_moon;
// Inputs:
in vec3 sphere_fs_in;
in vec3 normal_fs_in;
in vec4 pos_fs_in; 
in vec4 view_pos_fs_in; 
// Outputs:
out vec3 color;
// expects: model, blinn_phong, bump_height, bump_position,
// improved_perlin_noise, tangent
void main()
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code 
  float theta = M_PI  * animation_seconds / 4;
  vec4 temp = view * vec4(-4 * sin(theta), 2, 4 * cos(theta), 1);
  vec3 v = -normalize(view_pos_fs_in.xyz / view_pos_fs_in.w);
  vec3 l = normalize(temp.xyz / temp.w - view_pos_fs_in.xyz / view_pos_fs_in.w);
  float p = 1000;
  
  vec3 ka = vec3(0.05,0.05,0.05);
  vec3 ks = vec3(0.3, 0.3, 0.3);

  vec3 T, B;
  tangent(normalize(sphere_fs_in), T, B);
  vec3 n = normalize(cross((bump_position(is_moon, sphere_fs_in + T * 0.0001) - 
                        bump_position(is_moon, sphere_fs_in))/0.0001, 
                      (bump_position(is_moon, sphere_fs_in + B * 0.0001) - 
                        bump_position(is_moon, sphere_fs_in))/0.0001));
  
  if (is_moon) {
    vec3 kd = vec3(0.55, 0.5, 0.5);
    color = blinn_phong(ka, kd, ks, p, n, v, l);
  }
  else {
    vec3 kd;
    if(bump_height(is_moon, sphere_fs_in) > 0.001){
      float temp = 1 - abs(normalize(sphere_fs_in).y);
      ks = vec3(0.03, 0.03, 0.03);
      kd = vec3(0.2 + 0.4 * temp, 0.6, 0.1);
    }else{
      ks = vec3(1, 1, 1);
      kd = vec3(0.1, 0.16, 0.6);
    }
    color = blinn_phong(ka, kd, ks, p, n, v, l);
  }
  /////////////////////////////////////////////////////////////////////////////
}
