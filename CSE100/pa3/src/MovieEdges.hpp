#ifndef MOVIEEDGE_HPP
#define MOVIEEDGE_HPP


//#include "ActorNode.hpp"
class ActorNode;
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <queue>

using namespace std;

 class MovieEdges{

public:

//unordered_map< string, vector<*ActorNode> > main_list; 

string movie_name;
vector< ActorNode * > link;
int movie_weight;
int movie_year;

MovieEdges(string movieName, int movieYear, vector< ActorNode *> neighbors, bool weight);

  
      ~MovieEdges();

};

#endif



