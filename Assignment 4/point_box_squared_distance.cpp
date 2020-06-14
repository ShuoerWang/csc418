#include "point_box_squared_distance.h"

double point_box_squared_distance(
  const Eigen::RowVector3d & query,
  const BoundingBox & box)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here
  double x = fmax(fmax(box.min_corner[0] - query(0), 0), query(0) - box.max_corner[0]);
  double y = fmax(fmax(box.min_corner[1] - query(1), 0), query(1) - box.max_corner[1]);
  double z = fmax(fmax(box.min_corner[2] - query(2), 0), query(2) - box.max_corner[2]);
  return x * x + y * y + z * z;

  ////////////////////////////////////////////////////////////////////////////
}
