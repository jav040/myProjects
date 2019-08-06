#include "ActorNode.hpp"
#include "MovieEdges.hpp"
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>


using namespace std;




string actor_name;
vector<MovieEdges> movie_edges;



ActorNode::ActorNode(string actorName)
{

  
  this->actor_name = actorName;
  

}


ActorNode::~ActorNode(){}

