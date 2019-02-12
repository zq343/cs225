#include "Image.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <iostream>
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
  this->cs225::PNG::resize(ceil(this->width()*factor),ceil(this->height()*factor));
  if (factor>0 && factor <1){
    for (unsigned x = 0; x < this->width(); x++) {
      for (unsigned y =0; y < this->height(); y++){
        HSLAPixel & pixel = this->getPixel(x,y);
        HSLAPixel & origpixel = original->getPixel(ceil(x/factor),ceil(y/factor));
        pixel=origpixel;
      }
    }
  }
  if(factor>1){
    for (unsigned x = 0; x < this->width()/factor; x++) {
      for (unsigned y =0; y < this->height()/factor; y++){
        HSLAPixel & origpixel = original->getPixel(x,y);
        for (unsigned a = 0; a < ceil(factor); a++) {
          for (unsigned b =0; b < ceil(factor); b++){
            HSLAPixel & pixel = this->getPixel(x*factor+a,y*factor+b);
            pixel=origpixel;
          }
        }
      }
    }
  }
  delete original;
}



//Scales the image to fit within the size (w x h).
void Image::scale (unsigned w, unsigned h){
  double factW=(double)w/(double)this->width();
  double factH=(double)h/(double)this->height();
  if (factW < factH){
    scale(factW);
  }else {
    scale(factH);
  }
}

//  PNG *original= new cs225::PNG(*this);
//  this->cs225::PNG::resize((int)w,(int)h);

//  for (unsigned x = 0; x < w; x++) {

  //     HSLAPixel & pixel = original->getPixel((int)(x/factW),(int)(y/factW));
  //      HSLAPixel & alteredPixel = this->getPixel(x,y);
  //      alteredPixel=pixel;

  //      HSLAPixel & pixel = original->getPixel((int)(x/factH),(int)(y/factH));
  //      HSLAPixel & alteredPixel = this->getPixel(x,y);
  //      alteredPixel=pixel;
