#include "euler_angles_to_transform.h"

Eigen::Affine3d euler_angles_to_transform(
  const Eigen::Vector3d & xzx)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  double alpha = xzx[0] * M_PI / 180.0;
  double beta = xzx[1] * M_PI / 180.0;
  double gamma = xzx[2] * M_PI / 180.0;

  Eigen::Affine3d A,B,C,D;
  D.matrix() << 
    1,0,0,0,
    0,cos(alpha),-sin(alpha),0,
    0,sin(alpha),cos(alpha),0,
    0,0,0,1;

  C.matrix() << 
    cos(beta),-sin(beta),0,0,
    sin(beta),cos(beta),0,0,
    0,0,1,0,
    0,0,0,1;

  B.matrix() << 
    1,0,0,0,
    0,cos(gamma),-sin(gamma),0,
    0,sin(gamma),cos(gamma),0,
    0,0,0,1;

  A = B * C * D;
  return A;
  /////////////////////////////////////////////////////////////////////////////
}
