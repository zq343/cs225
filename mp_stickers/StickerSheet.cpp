#include "StickerSheet.h"

StickerSheet::StickerSheet (const Image &picture, unsigned max){
  picture_=picture;
  max_=max;
  x_=new int[max]
  y_=new int[max]
  int count =0;
}

StickerSheet::~StickerSheet (){
  _destroy();
}

StickerSheet::StickerSheet (const StickerSheet:StickerSheet &other){
  _copy();
}

const StickerSheet::StickerSheet & 	operator= (const StickerSheet::StickerSheet &other){
  if(*this != other){
    _destroy();
    _copy(other);
  }
  return *this;
}

void 	StickerSheet::changeMaxStickers (unsigned max){
  StickerSheet *newStickers=new StickerSheet(picture_,max);

}

int addSticker (Image &sticker, unsigned x, unsigned y){

}

void _copy(const StickerSheet:StickerSheet &other);
void _destroy();
