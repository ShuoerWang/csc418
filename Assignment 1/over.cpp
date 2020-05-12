#include "over.h"
#include <cmath>
#include <algorithm>

void over(
  const std::vector<unsigned char> & A,
  const std::vector<unsigned char> & B,
  const int & width,
  const int & height,
  std::vector<unsigned char> & C)
{
  C.resize(A.size());
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  int count = 0;
  while (count < A.size()) {
      double a = A[count + 3] / 255.0;
      C[count] = a * A[count] + (1 - a) * B[count];
      C[count + 1] = a * A[count + 1] + (1 - a) * B[count + 1];
      C[count + 2] = a * A[count + 2] + (1 - a) * B[count + 2];
      C[count + 3] = std::min(A[count + 3], B[count + 3]);
      count += 4;
  }
  ////////////////////////////////////////////////////////////////////////////
}
