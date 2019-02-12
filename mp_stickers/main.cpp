#include "Image.h"
#include "StickerSheet.h"

int main() {

  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image picture;
  picture.readFromFile("alma.png");
  picture.scale(2);
  Image sticker1;
  sticker1.readFromFile("penguins.png");
  Image sticker2;
  sticker2.readFromFile("duck.png");
  Image sticker3;
  sticker3.readFromFile("i.png");
  sticker2.scale(0.7);
  StickerSheet result(picture,10);
  result.addSticker(sticker1,0,0);
  result.addSticker(sticker2,100,1200);
  result.addSticker(sticker3,picture.width()-sticker3.width(),0);
//  for(int i=0; i<7; i++){
  //  result.addSticker(sticker2,sticker2.width()*i,picture.height()-sticker2.height());
  //}

  Image output=result.render();
  output.writeToFile("myImage.png");
  return 0;
}
