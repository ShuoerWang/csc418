#include "transformed_tips.h"
#include "forward_kinematics.h"

Eigen::VectorXd transformed_tips(
  const Skeleton & skeleton, 
  const Eigen::VectorXi & b)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  Eigen::VectorXd result(3*b.size());
  std::vector<Eigen::Affine3d,Eigen::aligned_allocator<Eigen::Affine3d> > T;
  forward_kinematics(skeleton, T);

  for(int i = 0; i < b.size(); i++){
    Bone bone = skeleton[b[i]];
    Eigen::Vector4d tip = T[b[i]] * bone.rest_T * Eigen::Vector4d(bone.length, 0, 0, 1);
    for(int j = 0; j < 3; j++){
      result[3 * i + j] = tip[j] / tip[3];
    }
  }
  return result;
  /////////////////////////////////////////////////////////////////////////////
}
