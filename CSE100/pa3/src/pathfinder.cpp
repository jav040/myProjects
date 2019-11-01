
#include "ActorGraph.hpp"

#include <iostream>

#include <fstream>

#include <sstream>

#include <string>

#include <vector>

#include <queue>

#include <utility>

#include <functional>

#include <algorithm>

#include "MovieEdges.hpp"

#include <climits>

#include <tuple>

using namespace std;

int main(int argc, char *argv[]) {

  // TODO: Implement code for "Part 1: Path Finder"

//	cout << argv[0] << endl;

  /* First create an ActorGraph class object */

  

  ActorGraph * main_test = new ActorGraph();

   

  //weighted or unweighted

  if(*argv[2] == 'w')

  {

    main_test->is_weighted = true;

  }

  else

  {

    main_test->is_weighted = false;

  }

  

  //Get the input filename

  vector<string> final_output;  

 

 

  //Initialize ActorGraph object

  main_test->loadFromFile(argv[1], 0);

  main_test->makeNodes();  

  // Initialize the input file stream

  ifstream infile(argv[3]);

  //Initialize the output file stream

  ofstream outfile(argv[4]);
  string string1 = "(actor)--[movie#@year]-->(actor)--...";
  outfile << string1;
  outfile << endl;
  

  bool have_header = false;

  string build_path_string;

  // keep reading lines until the end of file is reached

  while (infile) 

  {

    string s;

    // get the next line

    if (!getline(infile, s)) break;

    if (!have_header) 

    {

      // skip the header
      have_header = true;
      continue;

    }

    istringstream ss(s);

    vector<string> record;

    while (ss) 

    {

      string next;

      // get the next string before hitting a tab character and put it in 'next'

      if (!getline(ss, next, '\t')) break;

      record.push_back(next);

    }

    if (record.size() != 2) 

    {

      // we should have exactly 2 columns

      continue;

    }

    string start_actor(record[0]);
    string end_actor(record[1]);
if(main_test->actor_list.find(start_actor)!= main_test->actor_list.end() && main_test->actor_list.find(end_actor) != main_test->actor_list.end()){
    main_test->dijkstraSearch(start_actor, end_actor);}
 
 //  cout << "searched two actors " << endl;
 
   auto it = main_test->Table.find(end_actor);

 // string build_path_string = "Actor: " + it->first + "; Movie: " + get<3>(it->second);

  string build_path_string = ""; 

  string last_one = "(" + it->first + ")";
  final_output.insert(final_output.begin(), last_one); 

  while(get<1>(it->second) != "x")

  {

    string year = to_string(get<4>(it->second));

    build_path_string += "(" + get<1>(it->second) + ")--[" + get<3>(it->second) + "#@" + year + "]-->";

    final_output.insert(final_output.begin(), build_path_string);  

  

    it = main_test->Table.find(get<1>(it->second));

    build_path_string.clear();

  }

 

  // cout <<  "The size of the vector is: " << final_output.size() << endl;  

   for(unsigned int i = 0; i < final_output.size(); i++)

   {

     outfile << final_output.at(i);   

   }

   

   //CLear for the next iteration

   final_output.clear();

   main_test->resetTable(); 

   outfile << endl;
  

} //end while loop

  infile.close();

  outfile.close();  

  delete main_test;
  return 0;

}
