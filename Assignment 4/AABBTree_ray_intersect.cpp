#include "AABBTree.h"
#include <stdio.h> 

// See AABBTree.h for API
bool AABBTree::ray_intersect(
  const Ray& ray,
  const double min_t,
  const double max_t,
  double & t,
  std::shared_ptr<Object> & descendant) const 
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  t = 0;
  if(ray_intersect_box(ray, this->box, min_t, max_t)){
    std::shared_ptr<Object> left_d, right_d;
    double left_t = std::numeric_limits<double>::infinity();
    double right_t = std::numeric_limits<double>::infinity();
    bool left_hit = (this->left != NULL) && this->left->ray_intersect(ray, min_t, max_t, left_t, left_d);
    bool right_hit = (this->right != NULL) && this->right->ray_intersect(ray, min_t, max_t, right_t, right_d);

    if(left_hit && !left_d) left_d = this->left;
    if(right_hit && !right_d) right_d = this->right;

    if(!left_hit && !right_hit){ 
      return false;
    }

    if(!left_hit && right_hit){
      t = right_t;
      descendant = right_d;
    }

    if(!right_hit && left_hit){
      t = left_t;
      descendant = left_d;
    }

    if(right_hit && left_hit){
      if(left_t < right_t){
        t = left_t;
        descendant = left_d;
      }else{
        t = right_t;
        descendant = right_d;
      }
    }
    return true;
  }
  return false;
  
  ////////////////////////////////////////////////////////////////////////////
}

