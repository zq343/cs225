/* Your code here! */
#include "dsets.h"
DisjointSets::DisjointSets(){
	arr.clear();
}
DisjointSets::DisjointSets(DisjointSets const & other){
	for(unsigned int i = 0 ; i < other.arr.size(); i++){
		arr.push_back((other.arr)[i]);
	}
}
DisjointSets::~DisjointSets(){
	arr.clear();
}
void DisjointSets::addelements (int num){
	for(int i = 0 ; i < num ; i ++){
		arr.push_back(-1);
	}
}
int DisjointSets::find (int elem){
	if(arr[elem]<0) return elem;
	else{
		int t = find(arr[elem]);
		arr[elem]  = t;
		return t;
	}
}
void DisjointSets::setunion (int a, int b){
	int root1 = find(a);
	int root2 = find(b);
	int newSize = arr[root1] + arr[root2];
	if(arr[root1] < arr[root2]){
		arr[root2] = root1;
		arr[root1] = newSize;
	}
	else{
		arr[root1] = root2;
		arr[root2] = newSize;
	}
}
int DisjointSets::size (int elem){
	return -1 * arr[find(elem)];
}
