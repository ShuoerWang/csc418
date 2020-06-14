#include "ray_intersect_box.h"
#include <iostream>

bool ray_intersect_box(
  const Ray & ray,
  const BoundingBox& box,
  const double min_t,
  const double max_t)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  double xd = ray.direction[0];
  double yd = ray.direction[1];
  double zd = ray.direction[2];
  double txmin, txmax, tymin, tymax, tzmin, tzmax = 0;

  double xmin = box.min_corner[0];
  double xmax = box.max_corner[0];
  double ymin = box.min_corner[1];
  double ymax = box.max_corner[1];
  double zmin = box.min_corner[2];
  double zmax = box.max_corner[2];

  double xe = ray.origin[0];
  double ye = ray.origin[1];
  double ze = ray.origin[2];
  if(xd >= 0){
  	txmin = (xmin - xe)/xd;
  	txmax = (xmax - xe)/xd;
  }else{
  	txmin = (xmax - xe)/xd;
  	txmax = (xmin - xe)/xd;
  }

  if(yd >= 0){
  	tymin = (ymin - ye)/yd;
  	tymax = (ymax - ye)/yd;
  }else{
  	tymin = (ymax - ye)/yd;
  	tymax = (ymin - ye)/yd;
  }

  if(zd >= 0){
  	tzmin = (zmin - ze)/zd;
  	tzmax = (zmax - ze)/zd;
  }else{
  	tzmin = (zmax - ze)/zd;
  	tzmax = (zmin - ze)/zd;
  }

  double min_max = std::max(std::max(std::max(txmin, tymin), tzmin), min_t);
  double max_min = std::min(std::min(std::min(txmax, tymax), tzmax), max_t);
  if(min_max > max_min){
  	return false;
  }
  return true;

  ////////////////////////////////////////////////////////////////////////////
}
