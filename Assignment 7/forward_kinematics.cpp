#include "forward_kinematics.h"
#include "euler_angles_to_transform.h"
#include <functional> // std::function

Eigen::Affine3d helper(
  int index,
  const Skeleton & skeleton
){
  if(skeleton[index].parent_index < 0){
      return Eigen::Affine3d::Identity();
  }
  Bone bone = skeleton[index];
  int parent = bone.parent_index;
  Eigen::Affine3d Tp = helper(parent, skeleton);
  Eigen::Affine3d R = euler_angles_to_transform(bone.xzx);
  return Tp * bone.rest_T * R * bone.rest_T.inverse();

}

void forward_kinematics(
  const Skeleton & skeleton,
  std::vector<Eigen::Affine3d,Eigen::aligned_allocator<Eigen::Affine3d> > & T)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  T.resize(skeleton.size(),Eigen::Affine3d::Identity());
  for(int i = 0; i < skeleton.size(); i++){
    T[i] = helper(i, skeleton);
  }
  /////////////////////////////////////////////////////////////////////////////
}
