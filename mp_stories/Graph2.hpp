#include <queue>
#include <algorithm>
#include <string>
#include <list>
#include <map>
/**
 * Returns an std::list of vertex keys that creates any shortest path between `start` and `end`.
 *
 * This list MUST include the key of the `start` vertex as the first vertex in the list, the key of
 * the `end` vertex as the last element in the list, and an ordered list of all vertices that must
 * be traveled along the shortest path.
 *
 * For example, the path a -> c -> e returns a list with three elements: "a", "c", "e".
 *
 * You should use undirected edges. Hint: There are no edge weights in the Graph.
 *
 * @param start The key for the starting vertex.
 * @param end   The key for the ending vertex.
 */
template <class V, class E>
std::list<std::string> Graph<V,E>::shortestPath(const std::string start, const std::string end) {
  // TODO: Part 3
  std::list<std::string> path;
  std::list<std::string> queue;
  std::map<std::string, bool> visited;
  std::map<std::string, std::string> pred;
  string next;
  string curr;

  for(auto a: vertexMap){
    visited.emplace(a.first, false);
  }

  queue.push_back(start);
  visited.at(start)=true;

  while(!queue.empty()){
    curr = queue.front();
    queue.pop_front();
    std::list<edgeListIter> edgeitr=adjList.at(curr);

    for(auto itr: edgeitr){
      if((((*itr).get()).source()).key()==curr && visited.at((((*itr).get()).dest()).key())==false){
         next = (((*itr).get()).dest()).key();
         queue.push_back(next);
         visited.at(next)=true;
         pred.emplace(next, curr);
         if(next==end) break;
      }
      if((((*itr).get()).dest()).key()==curr &&visited.at((((*itr).get()).source()).key())==false){
        next = (((*itr).get()).source()).key();
        queue.push_back(next);
        visited.at(next)=true;
        pred.emplace(next, curr);
        if(next==end) break;
      }
    }
    if(next==end) break;
  }

  path.push_back(end);
  string tmp=end;
  while(tmp!=start){
    path.push_front(pred.at(tmp));
    tmp=pred.at(tmp);
  }
  return path;
}
