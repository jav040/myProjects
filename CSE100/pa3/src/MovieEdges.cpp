



#include "ActorNode.hpp"
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <queue>

 //class MovieEdges{


//unordered_map<string, vector<*ActorNode> > main_list; 

string movie_name;
vector<  ActorNode * > link;
int movie_weight;
int movie_year;

MovieEdges::MovieEdges(string movieName, int movieYear, vector<  ActorNode *> neighbors, bool weight)
{
  this->movie_year = movieYear;
  this->movie_name = movieName;
  this->link = neighbors; 
  if(weight == true)
  {
    this->movie_weight = 2019 - movieYear;
  }
  else
  {
    this->movie_weight = 1;
  } 

}


MovieEdges::~MovieEdges(){}






