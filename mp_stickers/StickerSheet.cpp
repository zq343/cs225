#include "StickerSheet.h"
#include <cmath>
using namespace cs225;

StickerSheet::StickerSheet (const Image &picture, unsigned max){
  picture_=new Image (picture);
  stickers_=new Image [max];
  max_=max;
  x_=new int[max];
  y_=new int[max];
  count =0;
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
  StickerSheet *newStickers=new StickerSheet((*picture_),max);
  newStickers->count=count;

  for(int i=0; i<(int) fmin(max_,max); i++){
    newStickers->x_[i]=x_[i];
    newStickers->y_[i]=y_[i];
    newStickers->stickers_[i]=stickers_[i];
  }
  _destroy();
  //this=newStickers;
  picture_=newStickers->picture_;
  x_=newStickers->x_;
  y_=newStickers->y_;
  stickers_=newStickers->stickers_;
  max_=newStickers->max_;
  count=newStickers->count;
}

int StickerSheet::addSticker (Image &sticker, unsigned x, unsigned y){
  if(count<max_){
    y_[count]=y;
    x_[count]=x;
    stickers_[count]=sticker;
    count ++;
  }
  return -1;
}

bool 	StickerSheet::translate (unsigned index, unsigned x, unsigned y){
  if((int)index<=count){
    x_[index]=x;
    y_[index]=y;
    return true;
  }
  return false;
}

void 	StickerSheet::removeSticker (unsigned index){
if((int)index>count){
    return ;
  }
  StickerSheet *removed=new StickerSheet((*picture_),max_);
/*  for(int i=0; i<(int)index; i++){
    removed->x_[i]=x_[i];
    removed->y_[i]=y_[i];
    removed->stickers_[i]=stickers_[i];
  }
  for(int i=index;i<count-1;i++){
    removed->x_[i]=x_[i+1];
    removed->y_[i]=y_[i+1];
    removed->stickers_[i]=stickers_[i+1];
  }*/
  int todo = 0;
  for(int i=0; i<count; i++){
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
  stickers_=removed->stickers_;
  max_=removed->max_;
  count=removed->count;
  count--;
}

Image * StickerSheet::getSticker (unsigned index){
  if((int)index<count){
    return &stickers_[(int)index];
  }
  return NULL;
}

Image StickerSheet::render () const{
  unsigned int max_x= picture_->width();
  for(int i=0; i < count; i++){
    max_x = (x_[i]+stickers_[i].width() > max_x)?(x_[i]+stickers_[i].width()):max_x;
  }
  unsigned int max_y= picture_->height();
  for(int i=0; i < count; i++){
    max_y = (y_[i]+stickers_[i].height() > max_y)?(y_[i]+stickers_[i].height()):max_y;
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
  for(int i=0; i<count; i++){
    for(unsigned w=0; w<stickers_[i].width(); w++){
      for(unsigned h=0; h<stickers_[i].height(); h++){
    //    HSLAPixel& stickerpixel=stickers_[i].getPixel(w,stickers_[i].height()-1-h);
        HSLAPixel& stickerpixel=stickers_[i].getPixel(w,h);
        HSLAPixel& pixel=output->getPixel(x_[i]+w,y_[i]+h);
        if(stickerpixel.a !=0){
          pixel=stickerpixel;
        }
      }
    }
  }
  return *output;
}

void StickerSheet::_copy(const StickerSheet &other){

  max_=other.max_;
  x_=new int[max_];
  y_=new int[max_];
  count=other.count;
  stickers_=new Image [max_];
  picture_=new Image(*other.picture_);
  for(int i=0; i<max_; i++){
    x_[i]=other.x_[i];
    y_[i]=other.y_[i];
    stickers_[i]=other.stickers_[i];
  }
}

void StickerSheet::_destroy(){
  delete[] x_;
  delete[] y_;
  delete[] stickers_;
  delete picture_;
}
