#include "maze.h"
#include <ctime>
#include <queue>
#include <map>
#include <iostream>
using cs225::HSLAPixel;
/* Your code here! */
SquareMaze::SquareMaze(){
}

void SquareMaze::makeMaze (int width, int height){
//clean up
	for(unsigned int i = 0 ;i < arr.size(); i++){
		arr[i].clear();
	}
	arr.clear();

//full maze, all wall present
	for(int i = 0 ; i < height; i ++){
		std::vector< std::pair<bool,bool> > t;
		std::pair<bool, bool> use;
		t.clear();
		for(int j = 0 ; j < width; j ++){
			use.first = true;
			use.second = true;
			t.push_back(use);
		}
		arr.push_back(t);
	}
//initialize dimension
	dimx = width;
	dimy = height;
	start_x = 0;
	start_y = 0;
//random remove wall
	DisjointSets ds;
	ds.addelements(dimx * dimy);
	int x = 0;
	int y = 0;
	int right = 0;
	int count = 0;
	// srand(time(0));//seed for rand
//check visted
	vector< vector< std::pair<bool,bool>>> v;
	pair<bool,bool> p;
	for(unsigned int i = 0 ;i < v.size(); i++){
		v[i].clear();
	}
	v.clear();
	for(int i = 0 ; i < dimy; i ++){
		std::vector< std::pair<bool,bool> > t;
		t.clear();
		p.first = false;
		p.second = false;
		for(int j = 0 ; j < dimx; j ++){
			t.push_back(p);
		}
		v.push_back(t);
	}
	while(1){
		//end condition
		if(count>=(dimx*dimy*2)) break;
		//select random wall
		x = rand() % dimx;
		y = rand() % dimy;
		right = rand() % 2;

		//remove right wall
		if(right==1){
			if(v[y][x].first==false){
				count++;
				v[y][x].first = true;
			}
			if(arr[y][x].first==true) {
				//if block at right most/ bottom, then dont remove wall
				if(x+1>=dimx) continue;
				int a = ds.find(y*dimx+x);
				int b = ds.find(y*dimx+x+1);
				if(a==b) continue;
				ds.setunion(a,b);
				arr[y][x].first=false;
			}
		}
		//remove down wall
		else{
			if(v[y][x].second==false){
				count++;
				v[y][x].second = true;
			}
			if(arr[y][x].second==true) {
				if(y+1>=dimy) continue;
				int a = ds.find(y*dimx+x);
				int b = ds.find((y+1)*dimx+x);
				if(a==b) continue;
				ds.setunion(a,b);
				arr[y][x].second=false;
			}
		}
	}
}
bool SquareMaze::canTravel (int x, int y, int dir) const{
	int destx = x;
	int desty = y;
	bool right = false;
	//locate the block
	switch(dir){
		case 0:	destx = x+1; break;
		case 1:	desty = y+1; break;
		case 2:	destx = x-1; break;
		case 3:	desty = y-1; break;
	}
	//if neighbor out of grid, then do nothing
	if(desty<0 || destx<0 || desty >=dimy || destx>=dimy) return false;

	if(dir==0||dir==2) right = true;
	if(dir<2){
		destx = x;
		desty = y;
	}
	//destx,desty,right locates the wall
	if(right) return !(arr[desty][destx].first);
	else	  return !(arr[desty][destx].second);
}

void SquareMaze::setWall(int x, int y, int dir, bool exists) {
  if (x>=0&& y>=0 && y<dimy && x<dimx) {
    if (dir == 0) {
      arr[y][x].first = exists;
    }
    if (dir == 1) {
      arr[y][x].second = exists;
    }
  }
}
/*
void SquareMaze::setWall (int x, int y, int dir, bool exists){
	int destx = x;
	int desty = y;
	bool right = false;
	if((dir%2)==0) right = true;
	if(dir==2){
		destx--;
	}
	else if(dir==3){
		desty--;
	}
	if(destx>=0 && desty >=0 && destx<dimx && desty<dimy){
		if(right)
			arr[desty][destx].first = exists;
		else
			arr[desty][destx].second = exists;
	}
}
*/

std::vector<int> SquareMaze::solveMaze() {

  std::vector<int> lastRow;
  std::map<int, int> pathTrack; //next, prev
  std::vector<bool> visited;
  for(int i = 0; i < dimx*dimy; i++) {
    visited.push_back(false);
  }
  std::queue<int> queue;
  queue.push(0);
  visited[0] = true;

  //Traversal
  while(!queue.empty()) {
    int front = queue.front();
    queue.pop();

    int x = front % dimx;
    int y = front / dimx;

    if (canTravel(x, y, 0) && !visited[front + 1]) {
      pathTrack.insert(std::pair<int, int> (front + 1, front));
      visited[front + 1] = true;
      queue.push(front + 1);
    }
    if (canTravel(x, y, 1) && !visited[front+ dimx]) {
      pathTrack.insert(std::pair<int, int> (front + dimx, front));
      visited[front + dimx] = true;
      queue.push(front + dimx);
    }
    if (canTravel(x, y, 2) && !visited[front - 1]) {
      pathTrack.insert(std::pair<int, int> (front - 1, front));
      visited[front - 1] = true;
      queue.push(front - 1);
    }
    if (canTravel(x, y, 3) && !visited[front - dimx]) {
      pathTrack.insert(std::pair<int, int> (front - dimx, front));
      visited[front - dimx] = true;
      queue.push(front - dimx);
    }

    if (y == dimy - 1) {
      lastRow.push_back(front);
    }

  }


  std::vector<int> ret;
  int curr = lastRow.back();
	exit_x= curr%dimx;
  exit_y = dimy-1;

  while (curr != 0) {
    int prevIndex = pathTrack[curr];
    if (curr == prevIndex + 1) ret.push_back(0);
    if (curr == prevIndex + dimx) ret.push_back(1);
    if (curr == prevIndex - 1) ret.push_back(2);
    if (curr == prevIndex - dimx) ret.push_back(3);
    curr = prevIndex;
  }

  reverse(ret.begin(),ret.end());
  return ret;
}

/*
std::vector< int > SquareMaze::solveMaze (){
	vector<int> v = solveMaze_helper();
	v.erase(v.begin());
	return v;
}
std::vector< int > SquareMaze::solveMaze_helper (){
//clean up
	last_row.clear();
	for(int i = 0; i < dimx; i++){
		last_row.push_back(-1);
	}
	for(unsigned int i = 0 ;i < visited.size(); i++){
		visited[i].clear();
	}
	visited.clear();
	for(int i = 0 ; i < dimy; i ++){
		std::vector< bool > t;
		t.clear();
		for(int j = 0 ; j < dimx; j ++){
			t.push_back(false);
		}
		visited.push_back(t);
	}
//run dfs to update the distance of last row
	dfs(start_x,start_y,0);
	int max = 0;
	exit_y = dimy-1;
//select the longest path
	for(int i = 0; i < dimx; i++){
		if(last_row[i]>max){
			max = last_row[i];
			exit_x = i;
		}
	}
//clean up for solve
	for(int i = 0 ; i < dimy; i ++){
		for(int j = 0 ; j < dimx; j ++){
			visited[i][j] = false;
		}
	}
	return solve(exit_x,exit_y);
}
*/
/*
 *solve
 *	DESCRIPTION: dfs from exit to start point, and backtrack for the path
 *	INPUT: starting x, starting y
 *	OUTPUT: none
 *	RETURN VALUE:	the correct path
*/
std::vector<int> SquareMaze::solve(int x, int y){
	std::vector<int> ret;
	ret.clear();
	if(visited[y][x]==false){
		visited[y][x] = true;
		if(y==start_y&&x==start_x){
			ret.push_back(-1);
			return ret;
		}
		if(arr[y][x].first==false){
			ret = solve(x+1,y);
			if(ret.size()!=0){
				ret.push_back(2);
				return ret;
			}
		}
		if(arr[y][x].second==false){
			ret = solve(x,y+1);
			if(ret.size()!=0){
				ret.push_back(3);
				return ret;
			}
		}
		if(x!=0&&arr[y][x-1].first==false){
			ret = solve(x-1,y);
			if(ret.size()!=0){
				ret.push_back(0);
				return ret;
			}
		}
		if(y!=0&&arr[y-1][x].second==false){
			ret = solve(x,y-1);
			if(ret.size()!=0){
				ret.push_back(1);
				return ret;
			}
		}
	}
	return ret;
}
/*
 *dfs
 *	DESCRIPTION: helper to do dfs tranversal
 *	INPUT: starting x, starting y, distance travelled
 *	OUTPUT: none
 *	RETURN VALUE:none
*/
void SquareMaze::dfs(int x, int y, int dst){
	if(visited[y][x]==false){
		visited[y][x] = true;

		if(y==dimy-1) last_row[x] = last_row[x]>0?last_row[x]:dst;

		if(arr[y][x].first==false) dfs(x+1,y,dst+1);
		if(arr[y][x].second==false) dfs(x,y+1,dst+1);
		if(x!=0&&arr[y][x-1].first==false) dfs(x-1,y,dst+1);
		if(y!=0&&arr[y-1][x].second==false) dfs(x,y-1,dst+1);
	}
}
PNG * SquareMaze::drawMaze () const{
	PNG* ret = new PNG(dimx*10+1,dimy*10+1);
	for(unsigned int i = 0; i < ret->width(); i++){
		if(i==0||i>9)
			ret->getPixel(i,0) = HSLAPixel(0,1,0,1);
		else{
			ret->getPixel(i,0) = HSLAPixel(0,0,1,1);
		}
	}
	for(unsigned int i = 0; i < ret->height(); i++){
		ret->getPixel(0,i) = HSLAPixel(0,0,0,1);
	}
	for(int y = 0; y < dimy; y++){
		for(int x = 0; x < dimx; x++){
			if(arr[y][x].first==true){
				for(int k = 0; k < 11; k++){
					ret->getPixel((x+1)*10,y*10+k) = HSLAPixel(0,1,0,1);
				}
			}
			if(arr[y][x].second==true){
				for(int k = 0; k < 11; k++){
					ret->getPixel(x*10+k,(y+1)*10) = HSLAPixel(0,1,0,1);
				}
			}
		}
	}
	return ret;
}
PNG * SquareMaze::drawMazeWithSolution (){
	int curr_x = 5;
	int curr_y = 5;
	PNG* ret = drawMaze();
	std::vector<int> sol = solveMaze();
	for(unsigned int i = 0 ; i < sol.size() ; i++){
		for(unsigned int k = 0; k < 11; k++){
			switch(sol[i]){
				case 0:
					ret->getPixel(curr_x+k,curr_y) = HSLAPixel(0,1,0.5,1);
					break;
				case 1:
					ret->getPixel(curr_x,curr_y+k) = HSLAPixel(0,1,0.5,1);
					break;
				case 2:
					ret->getPixel(curr_x-k,curr_y) = HSLAPixel(0,1,0.5,1);
					break;
				case 3:
					ret->getPixel(curr_x,curr_y-k) = HSLAPixel(0,1,0.5,1);
					break;
			}
		}
		switch(sol[i]){
			case 0: curr_x+=10;break;
			case 1: curr_y+=10;break;
			case 2: curr_x-=10;break;
			case 3: curr_y-=10;break;
		}
	}
	for(int k = 1; k < 10; k++){
		ret->getPixel(exit_x*10+k,(exit_y+1)*10) = HSLAPixel(0,0,1,1);
	}
	return ret;
}
PNG * SquareMaze::custom (){
	PNG* ret = new PNG(10*dimx+5*dimy,5*dimy+1);
	for( int i = 0; i < dimx; i++){
		if(i!=0)
		for(int k = 0; k < 10; k++){
			ret->getPixel(i*10+k,0) = HSLAPixel(0,0,0,1);
		}
	}
	for( int i = 0; i < dimy; i++){
		for(int k = 0; k < 5 ; k++){
			ret->getPixel(i*5+k,i*5+k) = HSLAPixel(0,0,0,1);
		}
	}
	for(int y = 0; y < dimy; y++){
		for(int x = 0; x < dimx; x++){
			if(arr[y][x].first==true){
				for(int k = 0; k < 5; k++){
					ret->getPixel((x+1)*10+y*5+k,y*5+k) = HSLAPixel(0,1,0,1);
				}
			}
			if(arr[y][x].second==true){
				for(int k = 0; k < 10; k++){
					ret->getPixel(x*10+y*5+k+5,(y+1)*5) = HSLAPixel(0,1,0,1);
				}
			}
		}
	}
	return ret;
}
