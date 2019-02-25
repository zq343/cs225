/**
 * @file binarytree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include "TreeTraversals/InorderTraversal.h"
#include <iostream>
#include <cmath>

/**
 * @return The height of the binary tree. Recall that the height of a binary
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>::height() const
{
    // Call recursive helper function on root
    return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node* subRoot) const
{
    // Base case
    if (subRoot == NULL)
        return -1;

    // Recursive definition
    return 1 + std::max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
    // Call recursive helper function on the root
    printLeftToRight(root);

    // Finish the line
    std::cout << std::endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node* subRoot) const
{
    // Base case - null node
    if (subRoot == NULL)
        return;

    // Print left subtree
    printLeftToRight(subRoot->left);

    // Print this node
    std::cout << subRoot->elem << ' ';

    // Print right subtree
    printLeftToRight(subRoot->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
    template <typename T>
void BinaryTree<T>::mirror()
{
  mirror(root);
}

template <typename T>
void BinaryTree<T>::mirror(Node* root)
{
  if(root == NULL) return;
  mirror(root->left);
  mirror(root->right);
  Node* tmp = root->left;
	root->left = root->right;
	root->right = tmp;

    //your code here
}


/**
 * isOrdered() function iterative version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedIterative() const
{
    // your code here
    return false;
}

/**
 * isOrdered() function recursive version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedRecursive() const
{
  return isOrdered(root);
}

template <typename T>
bool BinaryTree<T>::isOrdered(const Node* subRoot) const
{

  if(subRoot->left == NULL && subRoot->right == NULL) {
    return true;
  }
  bool eval;
  if(subRoot->left != NULL){
    eval= eval && isOrdered(subRoot->left)&& (subRoot->elem >= subRoot->left->elem);
  }
  if(subRoot->right != NULL){
    eval=eval && isOrdered(subRoot->right)&& (subRoot->elem <= subRoot->right->elem);
  }
  return eval;
}
/*
template <typename T>
T BinaryTree<T>::leftMax(const Node* root) const{
    T res;
    if (root == NULL)
        return res;

    if (root->left != NULL)
        res = root->left->elem;
    return max({ leftMax(root->left),
                 res,
                 leftMax(root->right) });
}
template <typename T>
T BinaryTree<T>::rightMin(const Node* root)const {
    T res;
    if (root == NULL)
        return res;

    if (root->right != NULL)
        res = root->right->elem;
    return min({ rightMin(root->left),
                 res,
                 rightMin(root->right) });
}*/


/**
 * creates vectors of all the possible paths from the root of the tree to any leaf
 * node and adds it to another vector.
 * Path is, all sequences starting at the root node and continuing
 * downwards, ending at a leaf node. Paths ending in a left node should be
 * added before paths ending in a node further to the right.
 * @param paths vector of vectors that contains path of nodes
 */
template <typename T>
void BinaryTree<T>::getPaths(std::vector<std::vector<T>>& paths) const
{
    std::vector<T> path;
    _getPaths(paths,path, root);
}

template <typename T>
void BinaryTree<T>::_getPaths(std::vector<std::vector<T>>& paths, std::vector<T> path, Node *subRoot) const{
  if (subRoot== NULL) {
    return;
  }
  path.push_back(subRoot->elem);
  if (subRoot->left == NULL && subRoot->right == NULL) {
    paths.push_back(path);
  }

  _getPaths(paths, path, subRoot->left);
  _getPaths(paths, path, subRoot->right);
}
/**
 * Each node in a tree has a distance from the root node - the depth of that
 * node, or the number of edges along the path from that node to the root. This
 * function returns the sum of the distances of all nodes to the root node (the
 * sum of the depths of all the nodes). Your solution should take O(n) time,
 * where n is the number of nodes in the tree.
 * @return The sum of the distances of all nodes to the root
 */
template <typename T>
int BinaryTree<T>::sumDistances() const
{
    int sum = 0;
    return _sumDistances(-1,root,sum);
}

template <typename T>
int & BinaryTree<T>::_sumDistances(int distance, const Node* subRoot, int &sum) const
{
    distance++;
    sum += distance;
    if(subRoot->left != NULL){
        sum = _sumDistances(distance, subRoot->left, sum);
    }
    if(subRoot->right != NULL){
        sum = _sumDistances(distance, subRoot->right, sum);
    }
    return sum;
}
