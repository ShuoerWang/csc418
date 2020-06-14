#include "point_AABBTree_squared_distance.h"
#include <queue> // std::priority_queue
#include <iostream>

bool point_AABBTree_squared_distance(
    const Eigen::RowVector3d & query,
    const std::shared_ptr<AABBTree> & root,
    const double min_sqrd,
    const double max_sqrd,
    double & sqrd,
    std::shared_ptr<Object> & descendant)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here
  auto cmp = [](std::pair<double, std::shared_ptr<Object>> left, std::pair<double, std::shared_ptr<Object>> right){return left > right;};
  std::priority_queue<std::pair<double, std::shared_ptr<Object>>, std::vector<std::pair<double, std::shared_ptr<Object>>>, decltype(cmp)> q(cmp);
  sqrd = max_sqrd;

  q.push(std::make_pair(point_box_squared_distance(query, root->box), root));
  double curr_sqrd;
  std::shared_ptr<Object> curr_d;

  while(!q.empty()){
    double distance = q.top().first;
    std::shared_ptr<Object> subtree = q.top().second;
    q.pop();
    std::shared_ptr<AABBTree> temp = std::dynamic_pointer_cast<AABBTree>(subtree);

    if(distance < sqrd){ 
      if(temp == nullptr){
        if(subtree->point_squared_distance(query, min_sqrd, max_sqrd, curr_sqrd, curr_d)){
          if(curr_sqrd < sqrd){
            sqrd = curr_sqrd;
            descendant = subtree;
          }
        }
      }else{
        if(temp->left != nullptr)
          q.push(std::make_pair(point_box_squared_distance(query, temp->left->box), (temp->left)));
        if(temp->right != nullptr)
          q.push(std::make_pair(point_box_squared_distance(query, temp->right->box), (temp->right)));
      }
    }
  }
  return descendant != NULL;
  ////////////////////////////////////////////////////////////////////////////
}
