#include "AABBTree.h"
#include "insert_box_into_box.h"

AABBTree::AABBTree(
  const std::vector<std::shared_ptr<Object> > & objects,
  int a_depth): 
  depth(std::move(a_depth)), 
  num_leaves(objects.size())
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  int N = objects.size();
  for(int i = 0; i < N; i++){
  	insert_box_into_box(objects[i]->box, this->box);
  }
  this->left = NULL;
  this->right = NULL;
  if(N == 1){
  	this->left = objects[0];
  }else if(N == 2){
  	this->left = objects[0];
  	this->right = objects[1];
  }else{
  	double longest = -1;
  	double axis = -1;
  	double length = -1;
  	for(int i = 0; i < 3; i++){
  		length = this->box.max_corner[i] - this->box.min_corner[i];
  		if(length > longest){
  			longest = length;
  			axis = i;
  		}
  	}
  	double mid = (this->box.max_corner[axis] + this->box.min_corner[axis]) / 2;

  	std::vector<std::shared_ptr<Object>> left, right;
  	for(int i = 0; i < objects.size(); i++){
  		if (objects[i]->box.center()[axis] <= mid){
  			left.emplace_back(objects[i]);
  		}else{
  			right.emplace_back(objects[i]);
  		}
  	}

  	if(left.empty() && (!right.empty())){
  		left.emplace_back(right.back());
  		right.pop_back();
  	}

  	if(right.empty() && (!left.empty())){
  		right.emplace_back(left.back());
  		left.pop_back();
  	}

  	this->left = std::make_shared<AABBTree>(left, a_depth + 1);
  	this->right = std::make_shared<AABBTree>(right, a_depth + 1);
  }

  ////////////////////////////////////////////////////////////////////////////
}
