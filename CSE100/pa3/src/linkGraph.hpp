/*
 * linkGraph.hpp
 *
 * This file is meant to exist as a container for starter code that you can use
 * to read the input file format
 * defined in movie_casts.tsv. Feel free to modify any/all aspects as you wish.
 */
#ifndef LINKGRAPH_HPP
#define LINKRGRAPH_HPP
#include "ActorNode.hpp"
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <iostream>
#include "MovieEdges.hpp"
#include <utility>
#include <tuple>
#include <set>
// Maybe include some data structures here

class linkGraph {
 protected:
  // Maybe add class data structure(s) here
 public:
  //default constructor
  linkGraph(void);

   //default destructor
  ~linkGraph();

   void deleteAll();

  unordered_map<string, ActorNode * > actor_list;
  unordered_map<string, vector< ActorNode *> > movie_database;
  unordered_map<string, vector< pair<string, int>> > actor_database;

  vector<  vector<int>   > matrix;
  unordered_map<string, int> actor_indices;

  //if weighted or unweighted
  bool is_weighted;

  //Create the tuple
  typedef tuple<int, string, bool, string, int> TableNode;


  bool loadFromFile(const char *in_filename, const bool use_weighted_edges);

  static bool sortbyWeight(MovieEdges a, MovieEdges b);

  void sortMovieEdges();  

  void makeNodes(); 

  void fillConnections();

  void zeroFillMatrix(); 

  vector<   vector<int>   > findActorRow(string actorRow);

/*

  ~ActorGraph();

*/

};

#endif  // ACTORGRAPH_HPP

