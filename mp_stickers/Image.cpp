#include "Image.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include <cmath>
#include <string>

using cs225::HSLAPixel;
using cs225::PNG;

//Lighten an Image by increasing the luminance of every pixel by 0.1
void Image::lighten (){
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y =0; y < this->height(); y++){
      HSLAPixel & pixel = this->getPixel(x,y);
      pixel.l=fmin(pixel.l+0.1,1);
    }
  }
}

//Lighten an Image by increasing the luminance of every pixel by amount.
void Image::lighten (double amount){
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y =0; y < this->height(); y++){
      HSLAPixel & pixel = this->getPixel(x,y);
      pixel.l=fmin(pixel.l+amount,1);
    }
  }
}

//Darken an Image by decreasing the luminance of every pixel by 0.1
void Image::darken (){
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y =0; y < this->height(); y++){
      HSLAPixel & pixel = this->getPixel(x,y);
      pixel.l=fmax(pixel.l-0.1,0);
    }
  }
}


//Darkens an Image by decreasing the luminance of every pixel by amount
void Image::darken (double amount){
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y =0; y < this->height(); y++){
      HSLAPixel & pixel = this->getPixel(x,y);
      pixel.l=fmax(pixel.l-amount,0);
    }
  }
}

//Saturates an Image by increasing the saturation of every pixel by 0.1.
void Image::saturate (){
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y =0; y < this->height(); y++){
      HSLAPixel & pixel = this->getPixel(x,y);
      pixel.s=fmin(pixel.s+0.1,1);
    }
  }
}

//Saturates an Image by increasing the saturation of every pixel by amount.
void Image::saturate (double amount){
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y =0; y < this->height(); y++){
      HSLAPixel & pixel = this->getPixel(x,y);
      pixel.s=fmin(pixel.s+amount,1);
    }
  }
}

//Desaturates an Image by decreasing the saturation of every pixel by 0.1.
void Image::desaturate (){
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y =0; y < this->height(); y++){
      HSLAPixel & pixel = this->getPixel(x,y);
      pixel.s=fmax(pixel.s-0.1,0);
    }
  }
}

//Desaturates an Image by decreasing the saturation of every pixel by amount.
void Image::desaturate (double amount){
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y =0; y < this->height(); y++){
      HSLAPixel & pixel = this->getPixel(x,y);
      pixel.s=fmax(pixel.s-amount,0);
    }
  }
}

//Turns the image grayscale.
void Image::greyscale (){
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y =0; y < this->height(); y++){
      HSLAPixel & pixel = this->getPixel(x,y);
      pixel.h=0;
      pixel.s=0;
    }
  }
}

//	Rotates the color wheel by degrees.
void Image::rotateColor (double degrees){
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y =0; y < this->height(); y++){
      HSLAPixel & pixel = this->getPixel(x,y);
      if((pixel.h+degrees)>360){
        pixel.h=pixel.h+degrees-360;
      } else if((pixel.h+degrees)<0){
        pixel.h=pixel.h+degrees+360;
      } else {
        pixel.h=pixel.h+degrees;
      }
    }
  }
}

//Illinify the image
void Image::illinify (){
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y =0; y < this->height(); y++){
      HSLAPixel & pixel = this->getPixel(x,y);
      if (pixel.h <= 293.5 && pixel.h >= 113.5) {
        pixel.h = 216;
      } else {
        pixel.h = 11;
      }
    }
  }
}

//Scale the Image by a given factor.
void Image::scale (double factor){
  PNG *original= new cs225::PNG(*this);
  this->cs225::PNG::resize(this->width()*factor,this->height()*factor);
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y =0; y < this->height(); y++){
      HSLAPixel & pixel = this->getPixel(x,y);
      HSLAPixel & origpixel = original->getPixel(x/factor,y/factor);
      pixel=origpixel;
    }
  }
}



//Scales the image to fit within the size (w x h).
void Image::scale (unsigned w, unsigned h){
  //PNG *original= new cs225::PNG(*this);
  PNG *altered= new cs225::PNG(w,h);
  //this->cs225::PNG::resize(w,h);
//  double factW=w/original->width();
  //double factH=h/original->height();
  double factW=w/(this->width());
  double factH=h/(this->height());
  for (unsigned x = 0; x < altered->width(); x++) {
    for (unsigned y =0; y < altered->height(); y++){
      HSLAPixel & pixel = this->getPixel(round(x/factW),round(y/factH));
      HSLAPixel & alteredpixel = altered->getPixel(x,y);
      alteredpixel=pixel;
    }
  }
}
