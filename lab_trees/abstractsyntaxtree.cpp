#include "abstractsyntaxtree.h"

/**
 * Calculates the value from an AST (Abstract Syntax Tree). To parse numbers from strings, please use std::stod
 * @return A double representing the calculated value from the expression transformed into an AST
 */
double AbstractSyntaxTree::eval() const {

    return math(root);
}
double AbstractSyntaxTree::math(Node* subRoot)const{
  if (subRoot == NULL) return 0;

  if (subRoot->elem == "+") {
    return math(subRoot->left) + math(subRoot->right);
  }

  else if (subRoot->elem == "-") {
    return math (subRoot->left) - math(subRoot->right);
  }

  else if (subRoot->elem == "/") {
    return math (subRoot->left) / math(subRoot->right);
  }

  else if (subRoot->elem == "*") {
    return math (subRoot->left) * math(subRoot->right);
  }
  return std::stod(subRoot->elem);
}
