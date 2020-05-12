#include "hue_shift.h"
#include "hsv_to_rgb.h"
#include "rgb_to_hsv.h"
#include <cmath>
#include <algorithm>

void hue_shift(
  const std::vector<unsigned char> & rgb,
  const int width,
  const int height,
  const double shift,
  std::vector<unsigned char> & shifted)
{
  shifted.resize(rgb.size());
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  int count = 0;
  while (count < rgb.size()) {
      double h, s, v;
      double r = rgb[count];
      double g = rgb[count + 1];
      double b = rgb[count + 2];
      rgb_to_hsv(r, g, b, h, s, v);
      h += shift;
      while (h < 0) {
          h += 360;
      }
      h = fmod(h, 360.0);
      hsv_to_rgb(h, s, v, r, g, b);
      shifted[count] = r;
      shifted[count + 1] = g;
      shifted[count + 2] = b;
      count += 3;
  }
  ////////////////////////////////////////////////////////////////////////////
}
