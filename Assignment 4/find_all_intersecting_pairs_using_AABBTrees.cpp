#include "find_all_intersecting_pairs_using_AABBTrees.h"
#include "box_box_intersect.h"
// Hint: use a list as a queue
#include <list> 

void find_all_intersecting_pairs_using_AABBTrees(
  const std::shared_ptr<AABBTree> & rootA,
  const std::shared_ptr<AABBTree> & rootB,
  std::vector<std::pair<std::shared_ptr<Object>,std::shared_ptr<Object> > > & 
	leaf_pairs)
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  std::list<std::pair<std::shared_ptr<Object>, std::shared_ptr<Object>>> q;
  if(box_box_intersect(rootA->box, rootB->box)){
	  q.push_back(std::make_pair(rootA, rootB));
  }

  while(!q.empty()){
	 std::shared_ptr<Object> nodeA = q.front().first;
	 std::shared_ptr<Object> nodeB = q.front().second;
	 std::shared_ptr<AABBTree> a = std::dynamic_pointer_cast<AABBTree>(nodeA);
	 std::shared_ptr<AABBTree> b = std::dynamic_pointer_cast<AABBTree>(nodeB);
	 q.pop_front();
  
	 if((!a) && (!b)){
	 	leaf_pairs.emplace_back(std::make_pair(nodeA, nodeB));
	 }
	 else if(!a){
	 	if(b->left && box_box_intersect(b->left->box, nodeA->box)){
	 		q.push_back(std::make_pair(nodeA, b->left));
	 	}
	 	if(b->right && box_box_intersect(b->right->box, nodeA->box)){
	 		q.push_back(std::make_pair(nodeA, b->right));
	 	}
	 }
	 else if(!b){
	 	if(a->left && box_box_intersect(a->left->box, nodeB->box)){
	 		q.push_back(std::make_pair(a->left, nodeB));
	 	}
	 	if(a->right && box_box_intersect(a->right->box, nodeB->box)){
	 		q.push_back(std::make_pair(a->right, nodeB));
	 	}
   }
	 else {
	 	if (a->left && b->left && box_box_intersect(a->left->box, b->left->box)) {
	 		q.push_back(std::make_pair(a->left, b->left));
	 	}
	 	if (a->left && b->right && box_box_intersect(a->left->box, b->right->box)) {
	 		q.push_back(std::make_pair(a->left, b->right));
	 	}
	 	if (a->right && b->left && box_box_intersect(a->right->box, b->left->box)) {
	 		q.push_back(std::make_pair(a->right, b->left));
	 	}
	 	if (a->right && b->right && box_box_intersect(a->right->box, b->right->box)) {
	 		q.push_back(std::make_pair(a->right, b->right));
	 	}
  
	 }

  }

  ////////////////////////////////////////////////////////////////////////////
}
