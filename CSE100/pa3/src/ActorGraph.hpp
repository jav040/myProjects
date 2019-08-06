/*

 * ActorGraph.hpp

 *

 * This file is meant to exist as a container for starter code that you can use

 * to read the input file format

 * defined in movie_casts.tsv. Feel free to modify any/all aspects as you wish.

 */

#ifndef ACTORGRAPH_HPP

#define ACTORGRAPH_HPP

#include "ActorNode.hpp"

#include <algorithm>

#include <vector>

#include <unordered_map>

#include <iostream>

#include "MovieEdges.hpp"

#include <utility>

#include <tuple>

// Maybe include some data structures here

class ActorGraph {

 protected:

  // Maybe add class data structure(s) here

 public:

  //default constructor
  ActorGraph(void);

   //default destructor
  ~ActorGraph();

   void deleteAll();

  unordered_map<string, ActorNode * > actor_list;

  unordered_map<string, vector< ActorNode *> > movie_database;

  unordered_map<string, vector< pair<string, int> > > actor_database;

  //if weighted or unweighted

  bool is_weighted;

  //Create the tuple

  typedef tuple<int, string, bool, string, int> TableNode;

  unordered_map<string, TableNode> Table;

  bool loadFromFile(const char *in_filename, const bool use_weighted_edges);

  static bool sortbyWeight(MovieEdges a, MovieEdges b);

  

  void sortMovieEdges();  

  void makeNodes(); 

  void resetTable();

  void dijkstraSearch(string startActor, string endActor);

/*

  ~ActorGraph();

*/

};

#endif  // ACTORGRAPH_HPP

