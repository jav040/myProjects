/*
 * linkGraph.cpp
 *
 * This file is meant to exist as a container for starter code that you can use
 * to read the input file format defined in movie_casts.tsv.
 *
 * Feel free to modify any/all aspects as you wish.
 */

#include "linkGraph.hpp"
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
#include <set>

using namespace std;

  /* Declare actor_list and database maps */
  unordered_map<string, ActorNode*> actor_list;
  unordered_map<string, vector< ActorNode*  >> movie_database;
  unordered_map<string, vector< pair<string, int>> > actor_database;

  vector<  vector<int>    > matrix; 
  unordered_map<string, int> actor_indices; 


  //if weighted or unweighted
  bool is_weighted;


linkGraph::linkGraph(void) {}
linkGraph::~linkGraph()
{
  deleteAll();
}

void linkGraph::deleteAll()
{
  auto it = this->actor_list.begin();
  while(it!= this->actor_list.end())
  {
    delete(it->second);
    it++;
  }
}

bool linkGraph::loadFromFile(const char *in_filename,

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
    unordered_map<string, int> a;
    string combined_string = movie_title + to_string(movie_year);

    // TODO: we have an actor/movie relationship, now what?

  /* Create new actor_name->actorNode mapping if not already there */

  actor_list.insert(std::make_pair(actor_name, new ActorNode(actor_name)));

  /* Create actorNode with actor name and put in Table */


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
  else
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
}//END LOADFROMFILE



void linkGraph::makeNodes()
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



//Fill matrix with zeros, and fill actor_indices unordered-map
void linkGraph::zeroFillMatrix()
{ 
  int actor_size = this->actor_list.size();
  auto it = actor_list.begin();
  for(unsigned int i = 0; i < actor_size; i++)
  {
    vector<int> store;
    matrix.push_back(store);  
    /* Add actor_name  */
    if(actor_indices.find(it->second->actor_name) == actor_indices.end())
    {
      actor_indices[it->second->actor_name];
      actor_indices.at(it->second->actor_name) = i;
    }
    for(unsigned int j = 0; j < actor_size; j++)
    {
      matrix.at(i).push_back(0);
    }
    it++;
  } 
}


void linkGraph::fillConnections()
{
  auto it = actor_list.begin();  
  while(it != actor_list.end())
  {
    for(unsigned int i = 0; i < actor_list.at(it->first)->movie_edges.size(); i++)
    {
      for(unsigned int j = 0; j < actor_list.at(it->first)->movie_edges.at(i).link.size(); j++)
      {
        ActorNode * temp_actor = actor_list.at(it->first)->movie_edges.at(i).link.at(j);
        if(temp_actor != actor_list.at(it->first))
        {
          int row_actor_index = actor_indices.at(it->first);
          int col_actor_index = actor_indices.at(temp_actor->actor_name);

     	  matrix.at(row_actor_index).at(col_actor_index) = 1;
        }
      }      
    }  
    it++;
  }
}


//Return single row of actor we're interested in
vector<  vector<int>  > linkGraph::findActorRow(string actorRow)
{
  vector<  vector<int> > row_matrix;
  int row_index = actor_indices.at(actorRow);
 /*
  vector<int> blank_vector; 
  row_matrix.push_back(blank_vector);
  for(unsigned int i = 0; i < matrix.at(row_index).size(); i++)
  {
    row_matrix.at(0).at(i) = matrix.at(row_index).at(i);
  }
*/
  for(unsigned int i = 0; i < matrix.at(row_index).size(); i++)
  {
    vector<int> blank_vector;
    row_matrix.push_back(blank_vector);
    row_matrix.at(i).at(0) = matrix.at(row_index).at(i);
  }

  return row_matrix;
}














