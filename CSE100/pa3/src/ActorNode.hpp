#ifndef ACTORNODE_HPP
#define ACTORNODE_HPP

#include "MovieEdges.hpp"
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>



using namespace std;




class ActorNode
{
public:

        string actor_name;
        vector<MovieEdges> movie_edges;        


       ActorNode(string actorName);
     
      ~ActorNode();
       

/*
       // Destructor 
       ~ActorNode();
*/
};

#endif

