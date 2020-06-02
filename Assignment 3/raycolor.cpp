#include "raycolor.h"
#include "first_hit.h"
#include "blinn_phong_shading.h"
#include "reflect.h"

bool raycolor(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector< std::shared_ptr<Light> > & lights,
  const int num_recursive_calls,
  Eigen::Vector3d & rgb)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  rgb = Eigen::Vector3d(0,0,0);
  Eigen::Vector3d n = Eigen::Vector3d(0,0,0);
  int hit_id;
  double t = 0;

  if(first_hit(ray, min_t, objects, hit_id, t, n)){
    rgb += blinn_phong_shading(ray, hit_id, t, n, objects, lights);

    Ray ray2;
    ray2.origin = ray.origin + t * ray.direction;
    ray2.direction = reflect(ray.direction, n);
    Eigen::Vector3d color = Eigen::Vector3d(0,0,0);

    if(raycolor(ray2, 0.000001, objects, lights, num_recursive_calls + 1, color)){
      rgb += (objects[hit_id]->material->km.array() * color.array()).matrix();
    }  
  }
  return true;
  ////////////////////////////////////////////////////////////////////////////
}
