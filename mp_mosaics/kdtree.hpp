/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <stack>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    if (first[curDim] < second[curDim]) {
      return true;
    }
    if (first[curDim] == second[curDim]) {
      return (first<second);
    }

    return false;
}

template <int Dim>
double KDTree<Dim>::getDistance(const Point<Dim>& point1, const Point<Dim>& point2) const {
  double distance = 0;
  for (int i = 0; i<Dim; i++){
    distance += pow(point1[i] - point2[i], 2);
  }
  return distance;
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
     double potDis = getDistance(potential, target);
     double curBestDis = getDistance(currentBest, target);
     if (potDis < curBestDis) {
       return true;
     }
     if (potDis == curBestDis) {
       return potential<currentBest;
     }

     return false;
}

template <int Dim>
void KDTree<Dim>::swap(Point<Dim>& point1, Point<Dim>& point2)
{
    Point<Dim> tmp = point1;
    point1 = point2;
    point2 = tmp;
}

template <int Dim>
int KDTree<Dim>::partition(vector<Point<Dim>>& newPoints, int left, int right, int pivotIndex, int dim)
{
    Point<Dim> pivotValue = newPoints[pivotIndex];
    swap(newPoints[pivotIndex], newPoints[right]);
    int storeIndex = left;
    for (int i = left; i <right; i++) {
      if (smallerDimVal(newPoints[i], pivotValue, dim)) {
        swap(newPoints[storeIndex], newPoints[i]);
        storeIndex++;
      }
    }
    swap(newPoints[right], newPoints[storeIndex]);
    return storeIndex;
}

template <int Dim>
Point<Dim> KDTree<Dim>::select(vector<Point<Dim>>& newPoints, int left, int right,int k, int dim)
{
    if (left == right) return newPoints[left];
    int pivotIndex = left;
    pivotIndex = partition(newPoints, left, right, pivotIndex, dim);
    if (k == pivotIndex) return newPoints[k];
    else if (k<pivotIndex) {
      return select(newPoints, left, pivotIndex-1, k, dim);
    }
    else return select(newPoints, pivotIndex+1, right, k, dim);
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::construct(vector<Point<Dim>>& newPoints,int left, int right, int dim) {
  if (right<left) return NULL;
  int medIndex = floor((left+right)/2);
  Point<Dim> med = select(newPoints, left, right, medIndex, dim%Dim);
  KDTreeNode * newNode = new KDTreeNode(med);
  newNode->left = construct(newPoints, left, medIndex-1, (dim+1)%Dim);
  newNode->right = construct(newPoints, medIndex+1, right, (dim+1)%Dim);
  return newNode;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    vector<Point<Dim>> points(newPoints);
    root = construct(points, 0, points.size()-1, 0);
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::copy(const KDTreeNode * subroot) {
  if (subroot == NULL) return NULL;
  // Copy this node and it's children
  KDTreeNode* newNode = new KDTreeNode(subroot->point);
  newNode->left = copy(subroot->left);
  newNode->right = copy(subroot->right);
  return newNode;
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
  root = copy(other.root);
  size = other.size();
}

template <int Dim>
void KDTree<Dim>::clear(KDTreeNode * subroot) {
  if (subroot == NULL) return;
  clear(subroot->left);
  clear(subroot->right);
  delete subroot;
}

template <int Dim>
void KDTree<Dim>::clear() {
  clear(root);
  root = NULL;
}


template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
   if (this != &rhs) {
     clear(root);
     root = copy(rhs.root);
   }

  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
  clear();
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::search(const Point<Dim>& query, KDTreeNode * subroot, int dim, std::stack<KDTreeNode *> &parents, std::stack<int> &dimRecord,
  std::stack<int> &dirRecord) const {
  if (subroot->point == query) {
    return subroot;
  }
  //Search the left subtree
  if (smallerDimVal(query, subroot->point, dim)) {
    parents.push(subroot);
    // std::cout<<subroot->point<<std::endl;
    dimRecord.push(dim);
    dirRecord.push(0);
    if (subroot->left!=NULL) {
      return search(query, subroot->left, (dim+1)%Dim, parents, dimRecord, dirRecord);
    }
    else return subroot;
  }
  //Search the right subtree
  if (!smallerDimVal(query, subroot->point, dim)){
    parents.push(subroot);
    // std::cout<<subroot->point<<std::endl;
    dimRecord.push(dim);
    dirRecord.push(1);
    if (subroot->right!=NULL) {
      return search(query, subroot->right, (dim+1)%Dim, parents, dimRecord, dirRecord);
    }
    else return subroot;
  }
  return subroot;
}

template <int Dim>
bool KDTree<Dim>::splitPlaneCheck(const Point<Dim>& query, const Point<Dim>& searchNode, int dim, double &currBestDist) const {
  // if (abs(query[dim] - searchNode[dim])<=currBestDist) return true;
  Point<Dim> tmp = query;
	tmp.set(dim, searchNode[dim]);
	if (getDistance(query,tmp)<=currBestDist) return true;
  else return false;
}

template <int Dim>
void KDTree<Dim>::back(const Point<Dim>& query, std::stack<KDTreeNode *> &parents, std::stack<int> &dimRecord, std::stack<int> &dirRecord,
  KDTreeNode *& currBestNode, double  &currBestDist) const{

  // std::cout << "back traversal" <<std::endl;
  //check if parent has a closer distance
  KDTreeNode * curr = parents.top();
  if (shouldReplace(query, currBestNode->point, curr->point)) {
    // std::cout << "replace with parent node" <<std::endl;
    currBestNode = curr;
    currBestDist = getDistance(currBestNode->point, query);
  }

  int dim = dimRecord.top();
  int dir = dirRecord.top();
  parents.pop();
  dimRecord.pop();
  dirRecord.pop();

  //check the distance to the split plane and if the other child of the parent contain a closer point
  if ( splitPlaneCheck(query, curr->point, dim, currBestDist)) {
    // std::cout << "go to other side" <<std::endl;
    // std::cout<<"current search node" <<curr->point<<std::endl;

    if (dir == 0 && curr->right!=NULL) {
      KDTreeNode * subBestNode = curr;
      // std::cout << "subfindnearestneighbor before" <<std::endl;
      subBestNode = search(query, curr->right, (dim+1)%Dim, parents, dimRecord, dirRecord );
      // std::cout << "subfindnearestneighbor after" <<std::endl;
      if (shouldReplace(query, currBestNode->point, subBestNode->point)) {
        currBestNode = subBestNode;
        currBestDist = getDistance(currBestNode->point, query);
      }
    }
    if (dir == 1 && curr->left!=NULL) {
      KDTreeNode * subBestNode = curr;
      subBestNode = search(query, curr->left, (dim+1)%Dim, parents, dimRecord, dirRecord );
      if (shouldReplace(query, currBestNode->point, subBestNode->point)) {
        currBestNode = subBestNode;
        currBestDist = getDistance(currBestNode->point, query);
      }
    }
  }

  if (!parents.empty()) {
    back(query, parents, dimRecord, dirRecord, currBestNode, currBestDist);
    currBestDist = getDistance(currBestNode->point, query);
  }

  return;

}

template <int Dim>
typename KDTree<Dim>::KDTreeNode * KDTree<Dim>::_findNearestNeighbor(const Point<Dim>& query, KDTreeNode* subroot, int dim) const
{
    /**
     * @todo Implement this function!
     */
    std::stack<KDTreeNode *> parents;
    std::stack<int> dimRecord;
    std::stack<int> dirRecord; //record the direction of the path, 0=left, 1=right;

    //search
    KDTreeNode * currBestNode = search(query, root, dim, parents, dimRecord, dirRecord);

    if (currBestNode->point == query) return currBestNode;
    double currBestDist = getDistance(currBestNode->point, query);
    //traverse back
    back(query, parents, dimRecord, dirRecord, currBestNode, currBestDist);
    return currBestNode;
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
     return _findNearestNeighbor(query, root, 0)->point;
}
