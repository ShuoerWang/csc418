#include "kinematics_jacobian.h"
#include "transformed_tips.h"
#include <iostream>

void kinematics_jacobian(
  const Skeleton & skeleton,
  const Eigen::VectorXi & b,
  Eigen::MatrixXd & J)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  J = Eigen::MatrixXd::Zero(b.size()*3,skeleton.size()*3);
  Eigen::VectorXd tip = transformed_tips(skeleton, b);
  double da = 1.0e-10;
  for(int i = 0; i < skeleton.size(); i++){
    for(int j = 0; j < skeleton[0].xzx.size(); j++){
      Skeleton copy = skeleton;
      copy[i].xzx[j] += da;
      Eigen::VectorXd temp = transformed_tips(copy, b);
      for(int m = 0; m < J.rows(); m++){
        J(m, 3 * i + j) = (temp - tip)[m] / da;
      }
    }
  } 
  /////////////////////////////////////////////////////////////////////////////
}
