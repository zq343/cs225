#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "intro.h"

#include <cmath>
#include <string>

using cs225::HSLAPixel;
using cs225::PNG;

void rotate(std:: string inputFile, std:: string outputFile) {
  PNG input;
  input.readFromFile(inputFile);
  PNG output(input.width(),input.height());
  for (unsigned x = 0; x < input.width(); x++) {
    for (unsigned y = 0; y < input.height(); y++) {
      HSLAPixel & inputPixel = input.getPixel(x, y);
      HSLAPixel & outputPixel = output.getPixel(input.width()-x-1,input.height()-y-1);
      outputPixel=inputPixel;
    }
  }
  output.writeToFile(outputFile);
}

cs225::PNG myArt(unsigned int width, unsigned int height) {
  cs225::PNG png(width, height);
  for (unsigned x = 0; x < png.width(); x++) {
    for (unsigned y = 0; y < png.height(); y++) {
      HSLAPixel & pixel = png.getPixel(x,y);
      pixel.h=180/cos((y-x)/360*3.141)*cos(60*x/width)+20;
      pixel.a=1;
      pixel.l=fmin(0.5+x/width,0.9);
      double distance=x*x+y*y;
      double diameter=width*width;
      if((distance<diameter && distance> diameter/1.5)
      || (distance<diameter/10 && distance> diameter/15)
      || (distance<diameter/49 && distance> diameter/70 )){
        pixel.s=1;
      } else {
        pixel.s=0.6;
      }
    }
  }
  return png;
}
