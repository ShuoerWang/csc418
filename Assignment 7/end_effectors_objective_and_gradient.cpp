#include "end_effectors_objective_and_gradient.h"
#include "transformed_tips.h"
#include "kinematics_jacobian.h"
#include "copy_skeleton_at.h"
#include <iostream>

void end_effectors_objective_and_gradient(
  const Skeleton & skeleton,
  const Eigen::VectorXi & b,
  const Eigen::VectorXd & xb0,
  std::function<double(const Eigen::VectorXd &)> & f,
  std::function<Eigen::VectorXd(const Eigen::VectorXd &)> & grad_f,
  std::function<void(Eigen::VectorXd &)> & proj_z)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  f = [&](const Eigen::VectorXd & A)->double
  {
    Skeleton copy = copy_skeleton_at(skeleton, A);
    Eigen::VectorXd tip = transformed_tips(copy, b);
    double result = 0.0;

    for(int i = 0; i < b.size(); i++){
      Eigen::Vector3d xb = Eigen::Vector3d(tip[3 * i], tip[3 * i + 1], tip[3 * i + 2]);
      Eigen::Vector3d q = Eigen::Vector3d(xb0[3 * i], xb0[3 * i + 1], xb0[3 * i + 2]);
      result += (xb - q).squaredNorm();
    }
    return result;
  };
  grad_f = [&](const Eigen::VectorXd & A)->Eigen::VectorXd
  {
    Skeleton copy = copy_skeleton_at(skeleton, A);
    Eigen::VectorXd tip = transformed_tips(copy, b);
    Eigen::MatrixXd jacobian;
    kinematics_jacobian(copy, b, jacobian);

    Eigen::VectorXd result = Eigen::VectorXd::Zero(A.size());

    for(int i = 0; i < b.size(); i++){
      for(int j = 0; j < 3; j++){
        result += 2 * (tip[3 * i + j] - xb0[3 * i + j]) * jacobian.row(3 * i + j).transpose();
      }
    }
    return result;
  };

  proj_z = [&](Eigen::VectorXd & A)
  {
    assert(skeleton.size()*3 == A.size());
    for(int i = 0; i < skeleton.size(); i++){
      for(int j = 0; j < 3; j++){
        A[3 * i + j] = std::max(skeleton[i].xzx_min[j], std::min(skeleton[i].xzx_max[j], A[3 * i + j]));
      }
    }
  };
  /////////////////////////////////////////////////////////////////////////////
}

