#include "rgb_to_hsv.h"
#include <cmath>
#include <algorithm>

void rgb_to_hsv(
  const double r,
  const double g,
  const double b,
  double & h,
  double & s,
  double & v)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
    double r1 = r / 255.0;
    double g1 = g / 255.0;
    double b1 = b / 255.0;
    double max = std::max(std::max(r1, g1), b1);
    double min = std::min(std::min(r1, g1), b1);
    double dif = max - min;
    if (min == max) {
        h = 0.0;
    }
    else if (max == r1) {
        h = 60 * (g1 - b1) / dif;
    }
    else if (max == g1) {
        h = (((b1 - r1) / dif) + 2) * 60.0;
    }
    else if (max = b1) {
        h = (((r1 - g1) / dif) + 4) * 60.0;
    }
    v = max;
    if (max == 0) {
        s = 0;
    }
    else {
        s = dif / max;
    }
    if (h < 0) {
        h += 360;
    }
  ////////////////////////////////////////////////////////////////////////////
}
