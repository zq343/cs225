#pragma once
#include <vector>
#include <utility>
#include "dsets.h"
#include "cs225/PNG.h"
#include <stdlib.h>
using namespace cs225;
class SquareMaze{
public:
	SquareMaze();
	void makeMaze (int width, int height);
	bool canTravel (int x, int y, int dir) const;
	void setWall (int x, int y, int dir, bool exists);
	std::vector< int > solveMaze ();
	PNG * drawMaze () const;
	PNG * drawMazeWithSolution ();
	PNG * custom();
private:
	void dfs(int x, int y, int dst);
	std::vector<int> solve(int x, int y);
	std::vector< int > solveMaze_helper ();
	std::vector< std::vector< std::pair< bool,bool> > > arr;	//first is right, second is down
	std::vector< std::vector< bool > > visited;
	std::vector <int> last_row;
	int dimx;
	int dimy;
	int start_x;
	int start_y;
	int exit_x;
	int exit_y;

};
