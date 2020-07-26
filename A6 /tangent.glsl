// Input:
//   N  3D unit normal vector
// Outputs:
//   T  3D unit tangent vector
//   B  3D unit bitangent vector
void tangent(in vec3 N, out vec3 T, out vec3 B)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code 
  vec3 a = cross(N, vec3(0,0,1));
  vec3 b = cross(N, vec3(0,1,0));

  if(length(a) > length(b)){
    T = normalize(a);
    B = normalize(cross(N, a));
  }else{
    T = normalize(b);
    B = normalize(cross(N, b));
  }
  /////////////////////////////////////////////////////////////////////////////
}
