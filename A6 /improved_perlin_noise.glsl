// Given a 3d position as a seed, compute an even smoother procedural noise
// value. "Improving Noise" [Perlin 2002].
//
// Inputs:
//   st  3D seed
// Values between  -½ and ½ ?
//
// expects: random_direction, improved_smooth_step
float improved_perlin_noise( vec3 st) 
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code 
  vec3 corners[8];
  corners[0] = vec3(floor(st.x), floor(st.y), floor(st.z));
  corners[1] = vec3(ceil(st.x), floor(st.y), floor(st.z));
  corners[2] = vec3(floor(st.x), ceil(st.y), floor(st.z));
  corners[3] = vec3(ceil(st.x), ceil(st.y), floor(st.z));
  corners[4] = vec3(floor(st.x), floor(st.y), ceil(st.z));
  corners[5] = vec3(ceil(st.x), floor(st.y), ceil(st.z));
  corners[6] = vec3(floor(st.x), ceil(st.y), ceil(st.z));
  corners[7] = vec3(ceil(st.x), ceil(st.y), ceil(st.z));

  float product[8];
  for(int i = 0; i < 8; i++){
    vec3 gradient = random_direction(corners[i]);
    vec3 vector = st - corners[i];
    product[i] = dot(gradient, vector);
  }

  vec3 temp = smooth_step(fract(st));

  float itp1 = mix(product[0], product[1], temp.x);
  float itp2 = mix(product[2], product[3], temp.x);
  float itp3 = mix(product[4], product[5], temp.x);
  float itp4 = mix(product[6], product[7], temp.x); 
  float itp5 = mix(itp1, itp2, temp.y);
  float itp6 = mix(itp3, itp4, temp.y);
  float itp7 = mix(itp5, itp6, temp.z);

  return 0.5 * itp7/sqrt(3);
  /////////////////////////////////////////////////////////////////////////////
}

