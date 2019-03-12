#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;

MyColorPicker::MyColorPicker( double increment ): luminance(0.3), increment(increment) { };

/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */
HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {

  HSLAPixel pixel(100, 0.5,luminance);
  luminance += increment;
  if (luminance >= 0.9) { luminance=0.3 ;}
  return pixel;
}
