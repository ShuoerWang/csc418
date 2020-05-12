#include "demosaic.h"

void demosaic(
  const std::vector<unsigned char> & bayer,
  const int & width,
  const int & height,
  std::vector<unsigned char> & rgb)
{
  rgb.resize(width*height*3);
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  int total;
  int count = 0;
  for (int i = 0; i < height; i++) {
      for (int j = 0; j < width; j++) {
          if (i % 2 == 0) {
              if (j % 2 == 0) {
                  //G(B)
                  if (j - 1 >= 0) {
                      total += bayer[i * width + j - 1];
                      count += 1;
                  }
                  if (j + 1 < width) {
                      total += bayer[i * width + j + 1];
                      count += 1;
                  }
                  if(count > 0){
                      rgb[(i * width + j) * 3 + 2] = total / count;
                  }
                  total = 0;
                  count = 0;
                  if (i - 1 >= 0) {
                      total += bayer[(i - 1) * width + j];
                      count += 1;
                  }
                  if (i + 1 < height) {
                      total += bayer[(i + 1) * width + j];
                      count += 1;
                  }
                  if (count > 0) {
                      rgb[(i * width + j) * 3] = total / count;
                  }
                  total = 0;
                  count = 0;
                  rgb[(i * width + j) * 3 + 1] = bayer[i * width + j];
              }
              else {
                  //B
                  if (j - 1 >= 0) {
                      total += bayer[i * width + j - 1];
                      count += 1;
                  }
                  if (j + 1 < width) {
                      total += bayer[i * width + j + 1];
                      count += 1;
                  }
                  if (i - 1 >= 0) {
                      total += bayer[(i - 1) * width + j];
                      count += 1;
                  }
                  if (i + 1 < height) {
                      total += bayer[(i + 1) * width + j];
                      count += 1;
                  }
                  if (count > 0) {
                      rgb[(i * width + j) * 3 + 1] = total / count;
                  }
                  total = 0;
                  count = 0;
                  if (j - 1 >= 0 && i - 1 >= 0) {
                      total += bayer[(i - 1) * width + j - 1];
                      count += 1;
                  }
                  if (j + 1 < width && i - 1 >= 0) {
                      total += bayer[(i - 1) * width + j + 1];
                      count += 1;
                  }
                  if (j - 1 >= 0 && i + 1 < height) {
                      total += bayer[(i + 1) * width + j - 1];
                      count += 1;
                  }
                  if (j + 1 < width && i + 1 < height) {
                      total += bayer[(i + 1) * width + j + 1];
                      count += 1;
                  }
                  if (count > 0) {
                      rgb[(i * width + j) * 3] = total / count;
                  }
                  total = 0;
                  count = 0;
                  rgb[(i * width + j) * 3 + 2] = bayer[i * width + j];
              }
          }
          else {
              if (j % 2 == 0) {
                  //R
                  if (j - 1 >= 0) {
                      total += bayer[i * width + j - 1];
                      count += 1;
                  }
                  if (j + 1 < width) {
                      total += bayer[i * width + j + 1];
                      count += 1;
                  }
                  if (i - 1 >= 0) {
                      total += bayer[(i - 1) * width + j];
                      count += 1;
                  }
                  if (i + 1 < height) {
                      total += bayer[(i + 1) * width + j];
                      count += 1;
                  }
                  if (count > 0) {
                      rgb[(i * width + j) * 3 + 1] = total / count;
                  }
                  total = 0;
                  count = 0;
                  if (j - 1 >= 0 && i - 1 >= 0) {
                      total += bayer[(i - 1) * width + j - 1];
                      count += 1;
                  }
                  if (j + 1 < width && i - 1 >= 0) {
                      total += bayer[(i - 1) * width + j + 1];
                      count += 1;
                  }
                  if (j - 1 >= 0 && i + 1 < height) {
                      total += bayer[(i + 1) * width + j - 1];
                      count += 1;
                  }
                  if (j + 1 < width && i + 1 < height) {
                      total += bayer[(i + 1) * width + j + 1];
                      count += 1;
                  }
                  if (count > 0) {
                      rgb[(i * width + j) * 3 + 2] = total / count;
                  }
                  total = 0;
                  count = 0;
                  rgb[(i * width + j) * 3] = bayer[i * width + j];
              }
              else {
                  if (j - 1 >= 0) {
                      total += bayer[i * width + j - 1];
                      count += 1;
                  }
                  if (j + 1 < width) {
                      total += bayer[i * width + j + 1];
                      count += 1;
                  }
                  if (count > 0) {
                      rgb[(i * width + j) * 3] = total / count;
                  }
                  total = 0;
                  count = 0;
                  if (i - 1 >= 0) {
                      total += bayer[(i - 1) * width + j];
                      count += 1;
                  }
                  if (i + 1 < height) {
                      total += bayer[(i + 1) * width + j];
                      count += 1;
                  }
                  if (count > 0) {
                      rgb[(i * width + j) * 3 + 2] = total / count;
                  }
                  total = 0;
                  count = 0;
                  rgb[(i * width + j) * 3 + 1] = bayer[i * width + j];
              }
          }
      }
  }
  ////////////////////////////////////////////////////////////////////////////
}
