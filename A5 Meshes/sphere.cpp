#include "sphere.h"
#include <iostream>

void sphere(
  const int num_faces_u,
  const int num_faces_v,
  Eigen::MatrixXd & V,
  Eigen::MatrixXi & F,
  Eigen::MatrixXd & UV,
  Eigen::MatrixXi & UF,
  Eigen::MatrixXd & NV,
  Eigen::MatrixXi & NF)
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here:
  int num_faces = num_faces_v * num_faces_u;
  int num_vertices = (num_faces_u + 1) * (num_faces_v + 1);
  V.resize(num_vertices, 3);
  F.resize(num_faces, 4);
  UV.resize(num_vertices, 2);
  UF.resize(num_faces, 4);
  NV.resize(num_vertices, 3);
  NF.resize(num_faces, 4);

  int index = 0;
  for(int i = 0; i < num_faces_u + 1; i++){
    double theta = static_cast<double>(i) * 2 * M_PI / num_faces_u;

    for(int j = 0; j < num_faces_v + 1; j++){
      double phi = static_cast<double>(j) * M_PI / num_faces_v;

      double x = -sin(phi) * cos(theta);
      double y = -sin(phi) * sin(theta);
      double z = -cos(phi);

      V.row(index) = Eigen::RowVector3d(x, y, z);
      UV.row(index) = Eigen::RowVector2d(
        static_cast<double>(i)/num_faces_u, static_cast<double>(j)/num_faces_v);
      NV.row(index) = Eigen::RowVector3d(x, y, z);
      index++;
    }
  }

  index = 0;
  for(int i = 0; i < num_faces_u; i++){
    for(int j = 0; j < num_faces_v; j++){
      int temp1 = i * (num_faces_v + 1) + j;
      int temp2 = (i + 1) *  (num_faces_v + 1) + j;
      F.row(index) = Eigen::RowVector4i(temp1, temp2, temp2 + 1, temp1 + 1);
      UF.row(index) = Eigen::RowVector4i(temp1, temp2, temp2 + 1, temp1 + 1);
      NF.row(index) = Eigen::RowVector4i(temp1, temp2, temp2 + 1, temp1 + 1);
      index++;
    }
  }
  
  ////////////////////////////////////////////////////////////////////////////
}
