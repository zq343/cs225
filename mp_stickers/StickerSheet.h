/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once

#include "Image.h"


class StickerSheet{
public:
  //Initializes this StickerSheet with a base picture
  //And the ability to hold a max number of stickers (Images) with indices 0 through max - 1.
  StickerSheet (const Image &picture, unsigned max);
  //Frees all space that was dynamically allocated by this StickerSheet.
  ~StickerSheet ();
  //The copy constructor makes this StickerSheet an independent copy of the source.
  StickerSheet (const StickerSheet &other);
  //The assignment operator for the StickerSheet class.
  const StickerSheet & 	operator= (const StickerSheet &other);
  //Modifies the maximum number of stickers that can be stored on this StickerSheet
  //without changing existing stickers' indices.
  void 	changeMaxStickers (unsigned max);
  //Adds a sticker to the StickerSheet,
  //the top-left of the sticker's Image is at (x, y) on the StickerSheet.
  int addSticker (Image &sticker, unsigned x, unsigned y);
  //Changes the x and y coordinates of the Image in the specified layer.
  bool 	translate (unsigned index, unsigned x, unsigned y);
  //Removes the sticker at the given zero-based layer index.
  void 	removeSticker (unsigned index);
  //Returns a pointer to the sticker at the specified index, not a copy of it.
  Image * getSticker (unsigned index);
  //Renders the whole StickerSheet on one Image and returns that Image.
  Image 	render () const;
private:
  Image *picture_;
  Image **stickers_;
  int max_;
  int* x_;
  int* y_;
  //int count;
  void _copy(const StickerSheet &other);
  void _destroy();
};
