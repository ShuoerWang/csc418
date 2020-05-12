#include "rotate.h"

void rotate(
  const std::vector<unsigned char> & input,
  const int width,
  const int height,
  const int num_channels,
  std::vector<unsigned char> & rotated)
{
  rotated.resize(height*width*num_channels);
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  int count = 0;
  for (int i = 0; i < width; i++) {
      for (int j = 0; j < height; j++) {
          if (num_channels == 3) {
              rotated[count] = input[(j * width + width - i - 1) * num_channels];
              rotated[count + 1] = input[(j * width + width - i - 1) * num_channels + 1];
              rotated[count + 2] = input[(j * width + width - i - 1) * num_channels + 2];
              count += 3;
          }
          else {
              rotated[count] = input[(j * width + width - i - 1) * num_channels];
              count++;
          }
      }
  }
  ////////////////////////////////////////////////////////////////////////////
}
