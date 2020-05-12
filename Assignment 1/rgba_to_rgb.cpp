#include "rgba_to_rgb.h"

void rgba_to_rgb(
  const std::vector<unsigned char> & rgba,
  const int & width,
  const int & height,
  std::vector<unsigned char> & rgb)
{
  rgb.resize(height*width*3);
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here

  int count = 0;
  for (int i = 0; i < height * width * 4; i++) {
      if (i % 4 != 3) {
          rgb[count] = rgba[i];
          count++;
      } 
  }
  ////////////////////////////////////////////////////////////////////////////
}
