#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() : traversal_(NULL)
{
  /** @todo [Part 1] */
}


ImageTraversal::Iterator::Iterator(const PNG & png, const Point & start, double tolerance, ImageTraversal* traversal){
  png_=png;
  start_=start;
  tolerance_=tolerance;
  traversal_=traversal;
  current_=start;
  for (unsigned i = 0; i < png_.width() * png_.height(); i++) {
   visited_.push_back(false);
  }
}
/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  Point right = Point(current_.x + 1, current_.y);
//  if(visited_[(current_.x+2)*(current_.y+1)]==false && inTolerance(right)==true) traversal_->add(right);
  Point up = Point(current_.x, current_.y + 1);
//  if(visited_[(current_.x+2)*(current_.y+1)]==false && inTolerance(right)==true) traversal_->add(right);
  Point left= Point(current_.x-1, current_.y);
  Point down = Point(current_.x, current_.y - 1);

  if (inTolerance(right)&&visited_[(current_.x+1)+(current_.y)*png_.width()]==false) traversal_->add(right);
  if (inTolerance(up)&&visited_[(current_.x)+(current_.y+1)*png_.width()]==false) traversal_->add(up);
  if (inTolerance(left)&&visited_[(current_.x-1)+(current_.y)*png_.width()]==false) traversal_->add(left);
  if (inTolerance(down)&&visited_[(current_.x)+(current_.y-1)*png_.width()]==false) traversal_->add(down);


  if (traversal_->empty()) {
    return *this;
  }
  if (!traversal_->empty()) {
      current_ = traversal_->pop();
      traversal_->add(current_);
      current_ = traversal_->peek();
      visited_[(current_.x)+(current_.y)*png_.width()]=true;

  }
  return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return current_;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  bool thisEmpty = false;
  bool otherEmpty = false;
  if (traversal_ == NULL) { thisEmpty = true; }
  if (other.traversal_ == NULL) { otherEmpty = true; }

  if (!thisEmpty)  { thisEmpty = traversal_->empty(); }
  if (!otherEmpty) { otherEmpty = other.traversal_->empty(); }

  if (thisEmpty && otherEmpty) return false; // both empty then the traversals are equal
  else if ((!thisEmpty)&&(!otherEmpty)) return (traversal_ != other.traversal_); //both not empty then compare the traversals
  else return true;
}

bool ImageTraversal::Iterator::inTolerance(Point point){
  if (point.x >= png_.width() || point.y >= png_.height()) return false;
  HSLAPixel &orig = png_.getPixel(start_.x, start_.y);
  HSLAPixel &curr= png_.getPixel(point.x, point.y);
  if (calculateDelta(orig, curr) >= tolerance_) return false;
  return true;
}
