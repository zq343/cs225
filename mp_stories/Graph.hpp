#include "Graph.h"
#include "Edge.h"
#include "Vertex.h"

#include <string>
#include <iostream>

/**
* @return The number of vertices in the Graph
*/
template <class V, class E>
unsigned int Graph<V,E>::numVertices() const {
  // TODO: Part 2
  return vertexMap.size();
}


/**
* The degree of the vertex. For directed: Sum of in-degree and out-degree
* @return Returns the degree of a given vertex.
* @param v Given vertex to return degree.
*/
template <class V, class E>
unsigned int Graph<V,E>::degree(const V & v) const {
  // TODO: Part 2
  string a=v.key();
  return (adjList.at(a)).size();
}


/**
* Inserts a Vertex into the Graph.
* @param key The key of the Vertex to insert
* @return The inserted Vertex
*/
template <class V, class E>
V & Graph<V,E>::insertVertex(std::string key) {
  // TODO: Part 2
  V & v = *(new V(key));
//  vertexMap.insert(std::pair<std::string, V_byRef>(key,v));
  vertexMap.emplace(key, v);
  std::list<edgeListIter> a;
  adjList.emplace(key, a);
  return v;
}


/**
* Removes a given Vertex
* @param v The Vertex to remove
*/
template <class V, class E>
void Graph<V,E>::removeVertex(const std::string & key) {
  // TODO: Part 2
  auto it=adjList.find(key);
  std::list<edgeListIter> edgeitr=it->second;
  for(auto itr: edgeitr){
    E edge= *itr;
    V v1=edge.source();
    V v2=edge.dest();
    (adjList.find(v1.key())->second).remove(itr);
    (adjList.find(v2.key())->second).remove(itr);
    edgeList.erase(itr);
  }
  vertexMap.erase(key);
  adjList.erase(key);
}


/**
* Inserts an Edge into the Graph.
* @param v1 The source Vertex
* @param v2 The destination Vertex
* @return The inserted Edge
*/
template <class V, class E>
E & Graph<V,E>::insertEdge(const V & v1, const V & v2) {
  // TODO: Part 2
  E & e = *(new E(v1, v2));
  edgeList.push_front(e);
  (adjList.at(v1.key())).push_front(edgeList.begin());
  (adjList.at(v2.key())).push_front(edgeList.begin());
  return e;
}


/**
* Removes an Edge from the Graph. Consider both the undirected and directed cases.
* min(degree(key1), degree(key2))
* @param key1 The key of the source Vertex
* @param key2 The key of the destination Vertex
*/
template <class V, class E>
void Graph<V,E>::removeEdge(const std::string key1, const std::string key2) {
  // TODO: Part 2
  E & e= *(new E(Vertex(key1),Vertex(key2)));
  for(auto a=edgeList.begin();a !=edgeList.end();++a){
    if((*a).get()==e){
      removeEdge(a);
      break;
    }
  }
  delete &e;

}



/**
* Removes an Edge from the Graph given by the location of the given iterator into the edge list.
* @param it An iterator at the location of the Edge that
* you would like to remove
*/
template <class V, class E>
void Graph<V,E>::removeEdge(const edgeListIter & it) {
  // TODO: Part 2
  string source=(*it).get().source().key();
  string dest=(*it).get().dest().key();
  adjList.at(source).remove(it);
  adjList.at(dest).remove(it);
  edgeList.erase(it);
}


/**
* Return the list of incident edges from a given vertex.
* For the directed case, consider all edges that has the vertex as either a source or destination.
* @param key The key of the given vertex
* @return The list edges (by reference) that are adjacent to the given vertex
*/
template <class V, class E>
const std::list<std::reference_wrapper<E>> Graph<V,E>::incidentEdges(const std::string key) const {
  // TODO: Part 2
  std::list<std::reference_wrapper<E>> edges;
  for(auto& a: adjList.at(key)){
    edges.push_back((*a).get());
  }
  return edges;
}


/**
* Return whether the two vertices are adjacent to one another. Consider both the undirected and directed cases.
* When the graph is directed, v1 and v2 are only adjacent if there is an edge from v1 to v2.
* @param key1 The key of the source Vertex
* @param key2 The key of the destination Vertex
* @return True if v1 is adjacent to v2, False otherwise
*/
template <class V, class E>
bool Graph<V,E>::isAdjacent(const std::string key1, const std::string key2) const {
  // TODO: Part 2
  if((adjList.at(key1)).size() > (adjList.at(key2)).size()){
    for(auto a: adjList.at(key2)){
      if( (((*a).get()).source()).key() == key1) return true;
    }
  }
  else{
    for(auto b: adjList.at(key1)){
      if( (((*b).get()).dest()).key() == key2) return true;
    }
  }
  return false;
}
