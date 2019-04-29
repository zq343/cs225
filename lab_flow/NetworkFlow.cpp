/**
 * @file NetworkFlow.cpp
 * CS 225: Data Structures
 */

#include <vector>
#include <algorithm>
#include <set>

#include "graph.h"
#include "edge.h"

#include "NetworkFlow.h"

int min(int a, int b) {
  if (a<b)
    return a;
  else return b;
}

NetworkFlow::NetworkFlow(Graph & startingGraph, Vertex source, Vertex sink) :
  g_(startingGraph), residual_(Graph(true,true)), flow_(Graph(true,true)), source_(source), sink_(sink) {

  // YOUR CODE HERE
  std::vector<Edge> currEdges = startingGraph.getEdges();
  std::vector<Vertex> currVertices = startingGraph.getVertices();
  //set vertices of flow and residual graph
  for (auto v : currVertices) {
    if (g_.vertexExists(v)) {
      residual_.insertVertex(v);
      flow_.insertVertex(v);
    }
  }
  //
  int weight = 0;
  for (auto e : currEdges) {
    residual_.insertEdge(e.source, e.dest);
    residual_.insertEdge(e.dest, e.source);
    //set return edge weight
    residual_.setEdgeWeight(e.dest, e.source, weight);
    //set edge weight
    residual_.setEdgeWeight(e.source, e.dest, g_.getEdgeWeight(e.source, e.dest));
    //flow edge
    flow_.insertEdge(e.source, e.dest);
    flow_.setEdgeWeight(e.source, e.dest, weight);
  }
}

  /**
   * findAugmentingPath - use DFS to find a path in the residual graph with leftover capacity.
   *  This version is the helper function.
   *
   * @param source  The starting (current) vertex
   * @param sink    The destination vertex
   * @param path    The vertices in the path
   * @param visited A set of vertices we have visited
   */

bool NetworkFlow::findAugmentingPath(Vertex source, Vertex sink,
  std::vector<Vertex> &path, std::set<Vertex> &visited) {

  if (visited.count(source) != 0)
    return false;
  visited.insert(source);

  if (source == sink) {
    return true;
  }

  vector<Vertex> adjs = residual_.getAdjacent(source);
  for(auto it = adjs.begin(); it != adjs.end(); it++) {
    if (visited.count(*it) == 0 && residual_.getEdgeWeight(source,*it) > 0) {
      path.push_back(*it);
      if (findAugmentingPath(*it,sink,path,visited))
        return true;
      else {
        path.pop_back();
      }
    }
  }

  return false;
}

  /**
   * findAugmentingPath - use DFS to find a path in the residual graph with leftover capacity.
   *  This version is the main function.  It initializes a set to keep track of visited vertices.
   *
   * @param source The starting (current) vertex
   * @param sink   The destination vertex
   * @param path   The vertices in the path
   */

bool NetworkFlow::findAugmentingPath(Vertex source, Vertex sink, std::vector<Vertex> &path) {
   std::set<Vertex> visited;
   path.clear();
   path.push_back(source);
   return findAugmentingPath(source,sink,path,visited);
}

  /**
   * pathCapacity - Determine the capacity of a path in the residual graph.
   *
   * @param path   The vertices in the path
   */

int NetworkFlow::pathCapacity(const std::vector<Vertex> & path) const {
  // YOUR CODE HERE
  if (path.begin() == path.end()) return 0;

//   std::vector<Vertex>::const_iterator itr = path.begin();
//   std::vector<Vertex>::const_iterator itr_next = ++itr;
//   Edge curr_edge = residual_.getEdge(*itr, *itr_next);
//   int cap = curr_edge.getWeight();
//   while(itr_next != path.end()) {
//     int temp = residual_.getEdge(*itr, *itr_next).getWeight();
//     if (cap > temp)
//       cap = temp;
//     itr++;
//     itr_next++;
//
//   }
//   return cap;
// }
  int cap = residual_.getEdgeWeight(path[0], path[1]);
  for (size_t i = 1; i < path.size(); i++) {
    int temp = residual_.getEdgeWeight(path[i-1], path[i]);
    if (cap > temp)
      cap = temp;
  }
  return cap;
}

  /**
   * calculuateFlow - Determine the capacity of a path in the residual graph.
   * Sets the member function `maxFlow_` to be the flow, and updates the
   * residual graph and flow graph according to the algorithm.
   *
   * @return The network flow graph.
   */

const Graph & NetworkFlow::calculateFlow() {
  int max=0;
  std::vector<Vertex> path;

  while(findAugmentingPath(source_,sink_,path)){
    int capacity=pathCapacity(path);
    max=max+capacity;
    // std::vector<Vertex>::const_iterator itr = path.begin();
    // std::vector<Vertex>::const_iterator itr_next = itr++;
    size_t i = 1;
    while(i != path.size()) {
      if(flow_.edgeExists(path[i - 1], path[i])){
        // std::cout << "exist" << std::endl;
        flow_.setEdgeWeight(path[i - 1], path[i],flow_.getEdgeWeight(path[i - 1], path[i])+capacity);
        // std::cout << "forward" << std::endl;
        residual_.setEdgeWeight(path[i - 1], path[i],residual_.getEdgeWeight(path[i - 1], path[i])-capacity);
        // std::cout << "reverse" << std::endl;
        residual_.setEdgeWeight(path[i], path[i - 1], flow_.getEdgeWeight(path[i - 1], path[i]));

      }else{
        // std::cout << "notexist" << std::endl;
        flow_.setEdgeWeight( path[i],path[i - 1], flow_.getEdgeWeight( path[i],path[i - 1])-capacity);
        // std::cout << "reverse" << std::endl;
        residual_.setEdgeWeight( path[i - 1],path[i], flow_.getEdgeWeight(path[i], path[i - 1]));
        // std::cout << "forward" << std::endl;
        residual_.setEdgeWeight(path[i],path[i - 1],g_.getEdgeWeight(path[i],path[i - 1])-flow_.getEdgeWeight(path[i],path[i - 1]));
      }
      // itr++;
      // itr_next++;
      i++;
    }

  }
  maxFlow_=max;
  return flow_;
}


int NetworkFlow::getMaxFlow() const {
  return maxFlow_;
}

const Graph & NetworkFlow::getGraph() const {
  return g_;
}

const Graph & NetworkFlow::getFlowGraph() const {
  return flow_;
}

const Graph & NetworkFlow::getResidualGraph() const {
  return residual_;
}
