#include "viewing_ray.h"

void viewing_ray(
  const Camera & camera,
  const int i,
  const int j,
  const int width,
  const int height,
  Ray & ray)
{
  ////////////////////////////////////////////////////////////////////////////
  //Add your code here
  double u = camera.width * (j + 0.5) / width - camera.width / 2;
  double v = camera.height / 2 - camera.height * (i + 0.5) / height;
  ray.direction = u * camera.u + v * camera.v - camera.d * camera.w;
  ray.origin = camera.e;
  ////////////////////////////////////////////////////////////////////////////
}

