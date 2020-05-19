#include "Plane.h"
#include "Ray.h"

bool Plane::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  Eigen::Vector3d e = ray.origin;
  Eigen::Vector3d d = ray.direction;
  if(normal.dot(d) == 0){
    return false;
  }
  double temp = (point - e).dot(normal) / normal.dot(d);

  if(temp <= min_t){
    return false;
  }else{
    t = temp;
    n = normal;
    return true;
  }
  ////////////////////////////////////////////////////////////////////////////
}

