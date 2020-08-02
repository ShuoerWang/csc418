#include "line_search.h"
#include <iostream>

double line_search(
  const std::function<double(const Eigen::VectorXd &)> & f,
  const std::function<void(Eigen::VectorXd &)> & proj_z,
  const Eigen::VectorXd & z,
  const Eigen::VectorXd & dz,
  const double max_step)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  double step = max_step;
  Eigen::VectorXd curr = z - step * dz;
  proj_z(curr);
  while(f(curr) > f(z)){
    step /= 2;
    curr = z - step * dz;
    proj_z(curr);
  }
  return step;
  /////////////////////////////////////////////////////////////////////////////
}
