#include "first_hit.h"

bool first_hit(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  int & hit_id, 
  double & t,
  Eigen::Vector3d & n)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  Eigen::Vector3d normal;
  double min = std::numeric_limits<double>::infinity();
  bool flag = false;

  for(int i = 0; i < objects.size(); i++){
    if(objects[i]->intersect(ray, min_t, t, normal)){
      if(t < min){
        min = t;
        hit_id = i;
        n = normal;
        flag = true;
      }
    }
  }
  t = min;
  return flag;
  ////////////////////////////////////////////////////////////////////////////
}

