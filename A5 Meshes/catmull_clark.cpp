#include "catmull_clark.h"
#include <unordered_map>
#include <utility>
#include <functional>
#include <vector>

void catmull_clark(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const int num_iters,
  Eigen::MatrixXd & SV,
  Eigen::MatrixXi & SF)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  Eigen::RowVector3d get_edge_point(
    const Eigen::MatrixXd & V,
    std::unordered_map<int, Eigen::RowVector3d> & face_points,
    std::unordered_map<std::string, std::vector<int>> & edges,
    int v1,
    int v2);
  Eigen::RowVector3d get_new_point(
    const Eigen::MatrixXd & V,
    std::unordered_map<int, Eigen::RowVector3d> & face_points,
    std::unordered_map<int, std::vector<int>> & adj_faces,
    std::unordered_map<int, std::vector<int>> & adj_vertices,
    int p); 
  void build_faces(
    Eigen::MatrixXd & SV,
    Eigen::MatrixXi & SF,
    std:: vector<Eigen::RowVector3d> vertices);
  
  std::unordered_map<int, Eigen::RowVector3d> face_points;
  std::unordered_map<std::string, std::vector<int>> edges;
  std::unordered_map<int, std::vector<int>> adj_faces;
  std::unordered_map<int, std::vector<int>> adj_vertices;
  
  if(num_iters == 0)
    return;
//step 1
  for(int i = 0; i < F.rows(); i++){
    face_points[i] = (V.row(F(i, 0)) + V.row(F(i, 1)) + V.row(F(i, 2)) + V.row(F(i, 3))) / 4.0;
  }
  for(int i = 0; i < F.rows(); i++){
    for(int j = 0; j < F.cols(); j++){
      std::string key1 = std::to_string(F(i, j)) + " " + std::to_string(F(i, (j + 1) % F.cols()));
      std::string key2 = std::to_string(F(i, (j + 1) % F.cols())) + " " +  std::to_string(F(i, j));
      //check wether already in
      if(std::find(edges[key1].begin(), edges[key1].end(), i) == edges[key1].end())
        edges[key1].push_back(i);
      if(std::find(edges[key2].begin(), edges[key2].end(), i) == edges[key2].end())
        edges[key2].push_back(i);
    }
  }
  for(int i = 0; i < F.rows(); i++){
    for(int j = 0; j < F.cols(); j++){
      adj_faces[F(i, j)].push_back(i);
    }
  }

  for(int i = 0; i < F.rows(); i++){
    for(int j = 0; j < F.cols(); j++){
      int temp1 = F(i, (j + 1) % F.cols());
      int temp2 = F(i, (j - 1 + F.cols()) % F.cols());
      int key = F(i , j);
      if(std::find(adj_vertices[key].begin(), adj_vertices[key].end(), temp1) == adj_vertices[key].end())
        adj_vertices[key].push_back(temp1);
      if(std::find(adj_vertices[key].begin(), adj_vertices[key].end(), temp2) == adj_vertices[key].end())
        adj_vertices[key].push_back(temp2);
    }
  }
  SV.resize(0, 3);
  SF.resize(0, 4);
  for(int i = 0; i < F.rows(); i++){
    for(int j = 0; j < F.cols(); j++){
      int curr = F(i, j);
      int next = F(i, (j + 1) % F.cols());
      int previous = F(i, ((j - 1) + F.cols()) % F.cols());
      std::vector<Eigen::RowVector3d> vertices;
      vertices.push_back(get_new_point(V, face_points, adj_faces, adj_vertices, curr));
      vertices.push_back(get_edge_point(V, face_points, edges, curr, next));
      vertices.push_back(face_points[i]);
      vertices.push_back(get_edge_point(V, face_points, edges, curr, previous));
      build_faces(SV, SF, vertices);
    }
  }
  catmull_clark(Eigen::MatrixXd(SV), Eigen::MatrixXi(SF), num_iters - 1, SV, SF);
  ////////////////////////////////////////////////////////////////////////////
}


  Eigen::RowVector3d get_edge_point(
    const Eigen::MatrixXd & V,
    std::unordered_map<int, Eigen::RowVector3d> & face_points,
    std::unordered_map<std::string, std::vector<int>> & edges,
    int v1,
    int v2){
      Eigen::RowVector3d result(0, 0, 0);
      std::string key = std::to_string(v1) + " " + std::to_string(v2);
      for(int i: edges[key]){
        result += face_points[i];
      }
      result = (result + V.row(v1) + V.row(v2)) / 4.0;
      return result;
  }

  Eigen::RowVector3d get_new_point(
    const Eigen::MatrixXd & V,
    std::unordered_map<int, Eigen::RowVector3d> & face_points,
    std::unordered_map<int, std::vector<int>> & adj_faces,
    std::unordered_map<int, std::vector<int>> & adj_vertices,
    int p){
      Eigen::RowVector3d sum(0, 0, 0);
      for(int i: adj_faces[p]){
        sum += face_points[i];
      }
      Eigen::RowVector3d F = sum / (double)adj_faces[p].size();

      Eigen::RowVector3d P = V.row(p);
      Eigen::RowVector3d sum2(0, 0, 0);
      for(int i: adj_vertices[p]){
        sum2 += (P + V.row(i)) / 2.0;
      }
      Eigen::RowVector3d R = sum2 / (double)adj_vertices[p].size();
      double n = adj_faces[p].size();
      return (F + 2.0 * R + (n - 3) * P) / n;
  }

  void build_faces(
    Eigen::MatrixXd & SV,
    Eigen::MatrixXi & SF,
    std:: vector<Eigen::RowVector3d> vertices){
      Eigen::RowVector4i face(-1,-1,-1,-1);
      int count = 0;
      for(Eigen::RowVector3d vertex: vertices){
        for(int i = 0; i < SV.rows(); i++){
          if(vertex.isApprox(SV.row(i))){
            face(count) = i;
          }
        }
        if(face(count) == -1){
          Eigen::MatrixXd temp = Eigen::MatrixXd::Zero(SV.rows() + 1, 3);
          temp.topRows(SV.rows()) = SV;
          temp.bottomRows(1) = vertex;
          SV = temp;
          face(count) = SV.rows() - 1;
        }
        count++;
      }
      Eigen::MatrixXi temp = Eigen::MatrixXi::Zero(SF.rows() + 1, 4);
      temp.topRows(SF.rows()) = SF;
      temp.bottomRows(1) = face;
      SF = temp;
  }

