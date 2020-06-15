#include "insert_triangle_into_box.h"

void insert_triangle_into_box(
  const Eigen::RowVector3d & a,
  const Eigen::RowVector3d & b,
  const Eigen::RowVector3d & c,
  BoundingBox & B)
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  B.min_corner[0] = fmin(fmin(a[0], b[0]), fmin(c[0], B.min_corner[0]));
  B.max_corner[0] = fmax(fmax(a[0], b[0]), fmax(c[0], B.max_corner[0]));
  B.min_corner[1] = fmin(fmin(a[1], b[1]), fmin(c[1], B.min_corner[1]));
  B.max_corner[1] = fmax(fmax(a[1], b[1]), fmax(c[1], B.max_corner[1]));
  B.min_corner[2] = fmin(fmin(a[2], b[2]), fmin(c[2], B.min_corner[2]));
  B.max_corner[2] = fmax(fmax(a[2], b[2]), fmax(c[2], B.max_corner[2]));
  
  ////////////////////////////////////////////////////////////////////////////
}


