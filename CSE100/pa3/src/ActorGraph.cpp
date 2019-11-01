/*
*ctorGraph.cpp

 *

 * This file is meant to exist as a container for starter code that you can use

 * to read the input file format defined in movie_casts.tsv.

 *

 * Feel free to modify any/all aspects as you wish.

 */

#include "ActorGraph.hpp"

#include <fstream>

#include <iostream>

#include <sstream>

#include <string>

#include <vector>

#include <queue>

#include <utility>

#include "MovieEdges.hpp"

#include <tuple>

#include <climits>

#include <algorithm>

#include <functional>

using namespace std;

  /* Declare actor_list and database maps */

  unordered_map<string, ActorNode*> actor_list;

  unordered_map<string, vector< ActorNode*  >> movie_database;

  unordered_map<string, vector< pair<string, int>> > actor_database;

  //if weighted or unweighted

  bool is_weighted;

  //Create the tuple

  typedef tuple<int, string, bool, string, int> TableNode;

  unordered_map<string, TableNode> Table;

  

 

       

ActorGraph::ActorGraph(void) {}

ActorGraph::~ActorGraph()
{
  deleteAll();
}


void ActorGraph::deleteAll()
{

 
  auto it = this->actor_list.begin();
  while(it!= this->actor_list.end())
  {
    delete(it->second);
    it++;
  }

 // actor_list.clear();
}


bool ActorGraph::loadFromFile(const char *in_filename,

                              const bool use_weighted_edges) {

  // Initialize the file stream

  ifstream infile(in_filename);

  bool have_header = false;

  // keep reading lines until the end of file is reached

  while (infile) {

    string s;

    // get the next line

    if (!getline(infile, s)) break;

    if (!have_header) {

      // skip the header

      have_header = true;

      continue;

    }

    istringstream ss(s);

    vector<string> record;

    while (ss) {

      string next;

      // get the next string before hitting a tab character and put it in 'next'

      if (!getline(ss, next, '\t')) break;

      record.push_back(next);

    }

    if (record.size() != 3) {

      // we should have exactly 3 columns

      continue;

    }

    string actor_name(record[0]);

    string movie_title(record[1]);

    int movie_year = stoi(record[2]);

    string combined_string = movie_title + to_string(movie_year);

    // TODO: we have an actor/movie relationship, now what?

  /* Create new actor_name->actorNode mapping if not already there */

  actor_list.insert(std::make_pair(actor_name, new ActorNode(actor_name)));

  /* Create actorNode with actor name and put in Table */

  /* If not already there */

  if(Table.find(actor_name) == Table.end())

  {

    Table[actor_name];

    get<0>(Table.at(actor_name)) = INT_MAX;

    get<1>(Table.at(actor_name)) = "x";

    get<2>(Table.at(actor_name)) = false; 

    get<3>(Table.at(actor_name)) = "y";

    get<4>(Table.at(actor_name)) = 0;

  }

  

  /* Add actor_name to movie they're in */

  if(movie_database.find(combined_string)!=movie_database.end())

  {

    movie_database.at(combined_string).push_back(actor_list.at(actor_name));

  }

  else//It's not there

  {

    movie_database[combined_string];

    movie_database.at(combined_string).push_back(actor_list.at(actor_name));

  }

  /* Add movie_title to actor if they're in */

  if(actor_database.find(actor_name)!=actor_database.end())

  {

    actor_database.at(actor_name).push_back(std::make_pair(movie_title, movie_year));

  }

  else//Actor not there

  {

    actor_database[actor_name];

    actor_database.at(actor_name).push_back(std::make_pair(movie_title, movie_year));

  }

}

  if (!infile.eof()) {

    cerr << "Failed to read " << in_filename << "!\n";

    return false;

  }

  infile.close();

  return true;

}

void ActorGraph::resetTable()
{

    for(auto it = Table.begin(); it != Table.end(); it++)

    {

      get<0>(it->second) = INT_MAX;

      get<1>(it->second) = "x";

      get<2>(it->second) = false; 

      get<3>(it->second) = "y";

      get<4>(it->second) = 0;

   }

}

void ActorGraph::makeNodes()

{

  auto it = this->actor_list.begin();

  /* Iterate through actor list, access their nodes */

  while(it!=this->actor_list.end())

  {

   /* For each actor, iterate through all the movies that they're in */

   for(unsigned int i = 0; i < this->actor_database.at(it->first).size(); i++)

   {  

     //Get the current movie

     string insert_movie = this->actor_database.at(it->first).at(i).first;

   //Movie name + Year key string
     string search_movie = this->actor_database.at(it->first).at(i).first + to_string(this->actor_database.at(it->first).at(i).second);

     //Get the year of that current movie

     int insert_movie_year = this->actor_database.at(it->first).at(i).second;

   

     //Get all the actors associated with that movie

     vector<ActorNode*> insert_actors = this->movie_database.at(search_movie);

     // Now insert into actor node's movie_edges member variable

     it->second->movie_edges.push_back(MovieEdges(insert_movie,insert_movie_year, insert_actors, is_weighted));

   }

   it++;

  }

}

bool ActorGraph::sortbyWeight(MovieEdges a, MovieEdges b)

{

  return (a.movie_weight < b.movie_weight);

}

void ActorGraph::sortMovieEdges()

{

  auto it = actor_list.begin();

  while(it != actor_list.end())

  { 

    std::sort(actor_list.at(it->first)->movie_edges.begin(), actor_list.at(it->first)->movie_edges.end(), sortbyWeight);

    it++;

  }

}

void ActorGraph::dijkstraSearch(string startActor, string endActor)

{

  sortMovieEdges();

  std::priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string> >> pq;

  std::pair< int, string > currPQNode;

  //Push the first object onto the queue

  pq.push(std::make_pair(0, startActor));

  while(!pq.empty())

  {

    currPQNode = pq.top();

    pq.pop();       

  //  if(currPQNode.second == endActor){return;}    

    if(get<2>(Table.at(currPQNode.second)) == false)

    {    

  

      get<2>(Table.at(currPQNode.second)) = true;      

      if(currPQNode.second == endActor){return;}    
      for(unsigned int i = 0; i < actor_list.at(currPQNode.second)->movie_edges.size(); i++)

      {

        for(unsigned int j = 0; j < actor_list.at(currPQNode.second)->movie_edges.at(i).link.size(); j++)

        {

      ActorNode * curr_actor = actor_list.at(currPQNode.second)->movie_edges.at(i).link.at(j);

	  if(curr_actor->actor_name != currPQNode.second && get<2>(Table.at(curr_actor->actor_name)) == false)

          {

           // c = distance(currNode) + distance(specific neghbor)

           int build_distance = currPQNode.first + actor_list.at(currPQNode.second)->movie_edges.at(i).movie_weight;

            //If c < distance already there(i.e. smaller weight path found),            // then replace distance 

            //and update previous node   

	    if(build_distance < get<0>(Table.at(curr_actor->actor_name)))

            {

        //Update the previous actor from this specific neighbor to current 

              get<1>(Table.at(curr_actor->actor_name)) = currPQNode.second;

        //Update the distance of this specific neighbor   

              get<0>(Table.at(curr_actor->actor_name)) = build_distance;

        //Update what movie brought us to this actor

	      get<3>(Table.at(curr_actor->actor_name)) = actor_list.at(currPQNode.second)->movie_edges.at(i).movie_name;

        //Update what movie(year) brought us to this actor

	      get<4>(Table.at(curr_actor->actor_name)) = actor_list.at(currPQNode.second)->movie_edges.at(i).movie_year;

	//Repush this neighbor with new updated shortest distance     

	       

	    pq.push(std::make_pair(build_distance , curr_actor->actor_name));

	    
            }

          }

	}

      }  

    }

  }

}

