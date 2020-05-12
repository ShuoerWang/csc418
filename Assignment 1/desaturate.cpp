#include "desaturate.h"
#include "hsv_to_rgb.h"
#include "rgb_to_hsv.h"

void desaturate(
  const std::vector<unsigned char> & rgb,
  const int width,
  const int height,
  const double factor,
  std::vector<unsigned char> & desaturated)
{
  desaturated.resize(rgb.size());
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  int count = 0;
  while (count < rgb.size()) {
      double h, s, v;
      double r = rgb[count];
      double g = rgb[count + 1];
      double b = rgb[count + 2];
      rgb_to_hsv(r, g, b, h, s, v);
      s *= (1 - factor);
      hsv_to_rgb(h, s, v, r, g, b);
      desaturated[count] = r;
      desaturated[count + 1] = g;
      desaturated[count + 2] = b;
      count += 3;
  }
  ////////////////////////////////////////////////////////////////////////////
}
