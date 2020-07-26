// Create a bumpy surface by using procedural noise to generate a height (
// displacement in normal direction).
//
// Inputs:
//   is_moon  whether we're looking at the moon or centre planet
//   s  3D position of seed for noise generation
// Returns elevation adjust along normal (values between -0.1 and 0.1 are
//   reasonable.
float bump_height( bool is_moon, vec3 s)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code 
  if(is_moon){
    return smooth_heaviside(improved_perlin_noise(2 * s), 0.1);
  }else{
    float temp = 0.05 * smooth_heaviside(3 * improved_perlin_noise(2 * s), 30);
    if(temp > 0.03){
      temp += 0.1 * improved_perlin_noise(5 * s);
      temp += 0.007 * improved_perlin_noise(20 * s);
    }else{
      temp += 0.02 * improved_perlin_noise(15 * s);
    }
    return temp;
  }
  /////////////////////////////////////////////////////////////////////////////
}
