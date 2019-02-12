#include "StickerSheet.h"
#include <cmath>
using namespace cs225;

StickerSheet::StickerSheet (const Image &picture, unsigned max){
  picture_=new Image (picture);
  stickers_=new Image* [max];
  max_=max;
  x_=new int[max];
  y_=new int[max];
  for (int i = 0; i < max_; i++){
		stickers_[i] = NULL;
  //  stickers_[i]=NULL;
    x_[i]=0;
    y_[i]=0;
	}

//  count =0;
}

StickerSheet::~StickerSheet (){
  _destroy();
}

StickerSheet::StickerSheet (const StickerSheet &other){
  _copy(other);
}

const StickerSheet & 	StickerSheet::operator= (const StickerSheet &other){
  if(this != &other){
    _destroy();
    _copy(other);
  }
  return *this;
}

void 	StickerSheet::changeMaxStickers (unsigned max){
  Image** stickers= new Image*[max];
  int * x = new int[max];
  int* y = new int[max];
  if ((int)max < (int)max_) {
    for (int i = 0; i < (int)max; i++) {
      if(stickers[i]!=NULL){
        stickers[i]= stickers_[i];
      }
      x[i] = x_[i];
      y[i] = y_[i];
    }
  }

  if((int)max > (int)max_){
    for (int i = 0; i < (int)max_; i++) {
      if(stickers[i]!=NULL){
        stickers[i]= stickers_[i];
      }
      x[i] = x_[i];
      y[i] = y_[i];
    }
    for (int i = max_; i < (int)max; i++) {
      stickers[i]=NULL;
      x[i] = 0;
      y[i] = 0;
    }
  }
  delete[] stickers_;
  delete[] x_;
  delete[] y_;
  stickers_ = stickers;
  x_ = x;
  y_ = y;
  max_ = max;
//  if(max_ ==(int) max){
//    return;
//  }
/*  StickerSheet *newStickers=new StickerSheet((*picture_),max);
//  newStickers->count=count;
  //newStickers->stickers_=stickers_;
  for(int i=0; i<(int) fmin(max_,max); i++){
    newStickers->x_[i]=x_[i];
    newStickers->y_[i]=y_[i];
    newStickers->stickers_[i]=stickers_[i];
  }
  for(int i=0;i<fmax(max_,max);i++){
    delete stickers_[i];
    stickers_[i]=NULL;

  }
  delete[] stickers_;
  delete[] x_;
  delete[] y_;
  //this=newStickers;
  //picture_=newStickers->picture_;
  x_=newStickers->x_;
  y_=newStickers->y_;
  max_=newStickers->max_;
  stickers_=newStickers->stickers_;
  for(int i=0; i<max_; i++){
    stickers_[i]=newStickers->stickers_[i];
  }*/
//  count=newStickers->count;
}

int StickerSheet::addSticker (Image &sticker, unsigned x, unsigned y){
  for(int i=0; i<max_ ;i++){
    if(stickers_[i]==NULL){
      y_[i]=(int)y;
      x_[i]=(int)x;
      stickers_[i]=new Image(sticker);
      break;
    }
  }
  return -1;
}

bool 	StickerSheet::translate (unsigned index, unsigned x, unsigned y){
  if((int)index<=max_&&stickers_[(int)index]!=NULL){
    x_[index]=x;
    y_[index]=y;
    return true;
  }
  return false;
}

void 	StickerSheet::removeSticker (unsigned index){
  if((int)index>=max_||stickers_[(int)index]==NULL){
    return ;
  }
  delete stickers_[(int)index];
  stickers_[(int)index]=NULL;
  x_[index]=0;
  y_[index]=0;
/*  StickerSheet *removed=new StickerSheet((*picture_),max_);
  for(int i=0; i<(int)index; i++){
    removed->x_[i]=x_[i];
    removed->y_[i]=y_[i];
    removed->stickers_[i]=stickers_[i];
  }
  for(int i=index;i<count-1;i++){
    removed->x_[i]=x_[i+1];
    removed->y_[i]=y_[i+1];
    removed->stickers_[i]=stickers_[i+1];
  }
  int todo = 0;
  for(int i=0; i<max_; i++){
    if(i==(int)index) {
      todo = 1;
    }
    else{
        removed->x_[i]=x_[i+todo];
        removed->y_[i]=y_[i+todo];
        removed->stickers_[i]=stickers_[i+todo];
    }
  }
  _destroy();
//  this=removed;
  picture_=removed->picture_;
  x_=removed->x_;
  y_=removed->y_;
  max_=removed->max_;
  stickers_=removed->stickers_;
  for(int i=0; i<max_; i++){
    stickers_[i]=removed->stickers_[i];
  }*/

//  count=removed->count;
//  count--;
}

Image * StickerSheet::getSticker (unsigned index){
  if((int)index<max_){
    return stickers_[(int)index];
  }
  return NULL;
}

Image StickerSheet::render () const{
  unsigned int max_x= picture_->width();
  unsigned int max_y= picture_->height();
  for(int i=0; i < max_; i++){
    if(stickers_[i]==NULL){
      continue;
    }
    max_x = (x_[i]+stickers_[i]->width() > max_x)?(x_[i]+stickers_[i]->width()):max_x;
    max_y = (y_[i]+stickers_[i]->height() > max_y)?(y_[i]+stickers_[i]->height()):max_y;
  }

  Image *output=new Image();
  output->resize(max_x, max_y);
  for(unsigned w=0; w<picture_->width(); w++){
    for(unsigned h=0; h<picture_->height(); h++){
  //    HSLAPixel& stickerpixel=stickers_[i].getPixel(w,stickers_[i].height()-1-h);
      HSLAPixel& picpixel=picture_->getPixel(w,h);
      HSLAPixel& pixel=output->getPixel(w,h);
      pixel=picpixel;
    }
  }
//  for(int i=count-1; i>-1; i--){
  for(int i=0; i<max_; i++){
    if(stickers_[i]!=NULL){
      for(unsigned w=0; w<stickers_[i]->width(); w++){
        for(unsigned h=0; h<stickers_[i]->height(); h++){
      //    HSLAPixel& stickerpixel=stickers_[i].getPixel(w,stickers_[i].height()-1-h);
          HSLAPixel& stickerpixel=stickers_[i]->getPixel(w,h);
          HSLAPixel& pixel=output->getPixel(x_[i]+w,y_[i]+h);
          if(stickerpixel.a !=0){
            pixel=stickerpixel;
          }
        }
      }
    }
  }
  return *output;
}
/*
Image StickerSheet::render()const{


  for (int i = 0; i < max_; i++) {
    if(stickers_[i]!= NULL){
      for (int j = 0; j < (int)stickers_[i]->width(); j++) {
        for (int k = 0; k <(int) stickers_[i]->height(); k++) {
          HSLAPixel &pixel = stickers_[i]->getPixel(j,k);
          if (pixel.a !=0)
            picture_->getPixel(j + x_[i], k + y_[i]) = pixel;
        }
      }
    }

  }
  return *picture_;

}*/
/*
Image StickerSheet::render()const{
//  Image *output=new Image(*picture_);
  for (int i = 0; i < max_; i++) {
    if(stickers_[i]!=NULL){
      for(int w=0; w< (int)stickers_[i]->width(); w++){
        for(int h=0; h<(int)stickers_[i]->height(); h++){
          HSLAPixel & pixel = stickers_[i]->getPixel(w,h);
          HSLAPixel & basepixel =picture_ ->getPixel(w + x_[i], h + y_[i]);
          if (pixel.a !=0){
                basepixel=pixel;
          }
        }
      }
    }
  }
  return *picture_;
}
*/


void StickerSheet::_copy(const StickerSheet &other){
  max_=other.max_;
  x_=new int[max_];
  y_=new int[max_];
//  count=other.count;
  stickers_=new Image *[max_];
  picture_=new Image(*other.picture_);
  for(int i=0; i<max_; i++){
    x_[i]=other.x_[i];
    y_[i]=other.y_[i];
    if(other.stickers_[i]!=NULL){
      stickers_[i]=new Image(*(other.stickers_[i]));
    } else{
      stickers_[i]=NULL;
    }

  }
}

void StickerSheet::_destroy(){
  delete[] x_;
  delete[] y_;
  for(int i=0;i<max_;i++){
    if(stickers_[i]!=NULL){
      delete stickers_[i];
      stickers_[i]=NULL;
    }
  }
  delete[] stickers_;
//  delete[] stickers_;
  delete picture_;
}
