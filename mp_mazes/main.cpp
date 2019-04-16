#include <iostream>
#include "dsets.h"
#include "maze.h"
#include "cs225/PNG.h"

using namespace std;

int main()
{
  PNG* ret;
  SquareMaze m;
  m.makeMaze(5,5);
  m.custom()->writeToFile("custom"+ string(".png"));
  m.drawMaze()->writeToFile("d"+ string(".png"));
  return 0;
}
