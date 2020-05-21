#include "Triangle.h"
#include "Ray.h"

bool Triangle::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  Eigen::Vector3d p1 = std::get<0>(corners);
  Eigen::Vector3d p2 = std::get<1>(corners);
  Eigen::Vector3d p3 = std::get<2>(corners);
  Eigen::Vector3d v1 = p1 - p2;
  Eigen::Vector3d v2 = p1 - p3;
  
  double a = p1[0] - p2[0];
  double b = p1[1] - p2[1];
  double c = p1[2] - p2[2];
  double d = p1[0] - p3[0];
  double e = p1[1] - p3[1];
  double f = p1[2] - p3[2];
  double g = ray.direction[0];
  double h = ray.direction[1];
  double i = ray.direction[2];
  double j = p1[0] - ray.origin[0];
  double k = p1[1] - ray.origin[1];
  double l = p1[2] - ray.origin[2];

  double M = a * (e * i - h * f) + b * (g * f - d * i) + c * (d * h - e * g);
  double temp = - (f * (a * k - j * b) + e * (j * c - a * l) + d * (b * l - k * c)) / M;
  double beta = (j * (e * i - h * f) + k * (g * f - d * i) + l * (d * h - e * g)) / M;
  double gamma = (i * (a * k - j * b) + h * (j * c - a * l) + g * (b * l - k * c)) / M;

  if(temp < min_t){
    return false;
  }

  if(beta < 0 || beta > 1 - gamma){
    return false;
  }

  if(gamma < 0 || gamma > 1){
    return false;
  }
  t = temp;
  n = v1.cross(v2)/(v1.cross(v2).norm());
  return true;


  ////////////////////////////////////////////////////////////////////////////
}


