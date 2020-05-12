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
      double srca = A[count + 3] / 255.0;
      double dsta = B[count + 3] / 255.0;
      double resulta = srca + dsta * (1 - srca);
      C[count] = (srca * A[count] + (1 - srca) * B[count] * dsta) / resulta;
      C[count + 1] = (srca * A[count + 1] + (1 - srca) * B[count + 1] * dsta) / resulta;
      C[count + 2] = (srca * A[count + 2] + (1 - srca) * B[count + 2] * dsta) / resulta;
      C[count + 3] = resulta * 255.0;
      if (resulta == 0) {
          C[count] = 0;
          C[count + 1] = 0;
          C[count + 2] = 0;
      }
      count += 4;
  }
  ////////////////////////////////////////////////////////////////////////////
}
