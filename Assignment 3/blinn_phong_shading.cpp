#include "blinn_phong_shading.h"
// Hint:
#include "first_hit.h"
#include <iostream>

Eigen::Vector3d blinn_phong_shading(
    const Ray & ray,
    const int & hit_id, 
    const double & t,
    const Eigen::Vector3d & n,
    const std::vector< std::shared_ptr<Object> > & objects,
    const std::vector<std::shared_ptr<Light> > & lights)
  {
    ////////////////////////////////////////////////////////////////////////////
    // Replace with your code here:
    Eigen::Vector3d p = ray.origin + t * ray.direction;
    Eigen::Vector3d rgb = Eigen::Vector3d(0, 0, 0);
    Eigen::Vector3d Ia = Eigen::Vector3d(1, 1, 1);
    rgb += ((objects[hit_id]->material->ka.array()) * 0.1 * Ia.array()).matrix();
  
    for(int i = 0; i < lights.size(); i++){
      double max_t;
      Eigen::Vector3d l;
  
      lights[i]->direction(p, l, max_t);
      Eigen::Vector3d h = (-ray.direction.normalized() + l.normalized()).normalized();
  
      Ray ray2;
      ray2.origin = p;
      ray2.direction = l;
      
      double max_h = std::max(0.0, n.dot(h));
      double max_l = std::max(0.0, n.dot(l));

      Eigen::Vector3d n2 = Eigen::Vector3d(0, 0, 0);
      double t2;
      int hit_id2;
  
      if(!first_hit(ray2, 0.000001, objects, hit_id2, t2, n2) || t2 > max_t){
        rgb += (objects[hit_id]->material->kd.array()*lights[i]->I.array()).matrix() * max_l;
        rgb += (objects[hit_id]->material->ks.array()*lights[i]->I.array()).matrix() * (std::pow(max_h, objects[hit_id]->material->phong_exponent));
      

      }
  }
  return rgb;
  ////////////////////////////////////////////////////////////////////////////
}
