#include "catmull_rom_interpolation.h"
#include <Eigen/Dense>

Eigen::Vector3d catmull_rom_interpolation(
  const std::vector<std::pair<double, Eigen::Vector3d> > & keyframes,
  double t)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  if(keyframes.size() == 0){
    return Eigen::Vector3d(0, 0, 0);
  }
  Eigen::Vector3d p0, p1, p2, p3;
  double t0, t1, t2, t3;

  t = fmod(t, keyframes.back().first);

  int i = 0;
  while (i < keyframes.size()){
    if(keyframes[i].first > t){
      break;
    }
    i++;
  }

  if(i < 2 || i == keyframes.size() - 1){
    p0 = keyframes[i - 1].second;
    p1 = keyframes[i - 1].second;
    p2 = keyframes[i].second;
    p3 = keyframes[i].second;

    t0 = keyframes[i - 1].first;
    t1 = keyframes[i - 1].first;
    t2 = keyframes[i].first;
    t3 = keyframes[i].first;
  }else{
    p0 = keyframes[i - 2].second;
    p1 = keyframes[i - 1].second;
    p2 = keyframes[i].second;
    p3 = keyframes[i + 1].second;

    t0 = keyframes[i - 2].first;
    t1 = keyframes[i - 1].first;
    t2 = keyframes[i].first;
    t3 = keyframes[i + 1].first;
  }
  //http://graphics.cs.cmu.edu/nsp/course/15-462/Fall04/assts/catmullRom.pdf
  double tao = 0.25;
  Eigen::Vector4d mu = Eigen::Vector4d(-tao * t + 2 * tao * pow(t, 2) - tao * pow(t, 3),
                        1 + (tao -3) * pow(t, 2) - (2 - tao) * pow(t, 3),
                        tao * t + (3 - 2 * tao) * pow(t, 2) + (tao - 2) * pow(t, 3),
                        -tao * pow(t, 2) + tao * pow(t, 3));

  Eigen::MatrixXd temp(4, 3);
  temp << p0, p1, p2, p3;

  return temp.transpose() * mu;
  /////////////////////////////////////////////////////////////////////////////
}
