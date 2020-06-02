#include "Sphere.h"
#include "Ray.h"
bool Sphere::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  Eigen::Vector3d d = ray.direction;
  Eigen::Vector3d e = ray.origin;
  Eigen::Vector3d c = center;
  double first = d.dot(d);
  double second = 2 * d.dot(e - c);
  double third = (e - c).dot(e - c) - radius * radius;
  double discriminant = second * second - 4 * first * third;

  if(discriminant < 0){
    return false;
  }else if(discriminant == 0){
    t = ((-1) * second) / (2 * first); 
  }else{
    double r1 = ((-1) * second + sqrt(discriminant)) / (2 * first);
    double r2 = ((-1) * second - sqrt(discriminant)) / (2 * first);
    double min = std::min(r1, r2);
    double max = std::max(r1, r2);
    if(max < min_t){
      return false;
    }
    if(min < min_t){
      t = max;
    }else if(min > min_t){
      t = min;
    }else{
      return false;
    }
  }
  n = (d * t + e - c) / radius;
  return true;
  ////////////////////////////////////////////////////////////////////////////
}

