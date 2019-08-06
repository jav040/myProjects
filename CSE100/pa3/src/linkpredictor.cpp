
#include "linkGraph.hpp"
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
#include "MatrixMultiply.hpp"


using namespace std;

int main(int argc, char *argv[]) {
  /* First create an linkGraph class object */
  linkGraph * main_test = new linkGraph();
   
//  MatrixOperations theProduct = new MatrixOperations();
  
  //Unweighted => breadth first search
  main_test->is_weighted = false;

  vector<string> final_output;   

  //Initialize linkGraph object
  main_test->loadFromFile(argv[1], 0);
  main_test->makeNodes();  
  main_test->zeroFillMatrix();
  main_test->fillConnections();


  // Initialize the input file stream
  ifstream infile(argv[2]);

  //Initialize the output file stream
  //Just doing future interactions rn, not collaborations yet
  ofstream outfile(argv[3]);
  string string1 = "Actor1,Actor2,Actor3,Actor4";
  outfile << string1;
  outfile << endl;

  bool have_header = false;
  string build_path_string;

  /* Begin reading in the pairs of start/end actors */
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
    if (record.size() != 1) 
    {
      // we should have exactly 2 columns
      continue;
    }

    string start_actor(record[0]);
  //  string end_actor(record[1]);
/* At this point we have a start actor/end actor relationship */


 
 vector<vector<int>> actor_matrix = main_test->matrix; 
 vector<vector<int>> single_matrix = main_test->findActorRow(start_actor);
 
 MatrixOperations<int> * theProduct = new MatrixOperations<int>(single_matrix, actor_matrix);
 vector<vector<int>> result_matrix = theProduct->matrixMultiply();



 
  



//Make sure the start actor actually exist in our graph
/* 
  string build_path_string = ""; 
  std::priority_queue< pair<string, int> > top_four;
  auto it = canidate_actors.begin();
  while(it!=canidate_actors.end())
  {
    top_four.push(std::make_pair(it->first, it->second));
    it++;
  }

   //Pop off the top four neighbors
   for(int i = 0; i <4; i++)
   {     
     build_path_string += top_four.top().second;
     build_path_string += ", ";
     top_four.pop();
   }
   
   outfile << build_path_string;
 
   //Clear for the next iteration
   main_test->resetTable();
   build_path_string.clear(); 
  */
    outfile << endl;
  

} //end while loop

  infile.close();
  outfile.close();  

//  delete main_test;
  return 0;

}
