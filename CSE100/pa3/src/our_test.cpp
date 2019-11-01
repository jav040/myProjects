#include <iostream>

#include <vector>

#include <sstream>

#include <fstream>

#include <string>

#include "ActorGraph.hpp"

#include "ActorNode.hpp"

#include "MovieEdges.hpp"

using namespace std;

/* Our tests */

int main()

{

  vector<string> final_output;

  ActorGraph * test1 = new ActorGraph();

  test1->loadFromFile("test_file.tsv", 0);

  test1->makeNodes();
 

  /* PRINT OUT INFO FROM WITHIN MOVIE EDGE OBJECTS/ACTOR NODE OBJECT

   //Print out the movie edge object items(via actor list) 

  auto it = test1->actor_list.begin();

  

  for(it; it!=test1->actor_list.end(); it++)

  {

    for(unsigned int j = 0; j < test1->actor_list.at(it->first)->movie_edges.size(); j++)

    {

        cout << test1->actor_list.at(it->first)->movie_edges.at(j).movie_name << " " << test1->actor_list.at(it->first)->movie_edges.at(j).movie_weight << endl;

      for(unsigned int k = 0; k < test1->actor_list.at(it->first)->movie_edges.at(j).link.size(); k++)

      {

        cout << test1->actor_list.at(it->first)->movie_edges.at(j).link.at(k)->actor_name << endl;

      }

        cout << test1->actor_list.at(it->first)->movie_edges.at(j).movie << endl;

      }

   } 

*/ 

  /* Test find */

/*

  test1->dijkstraSearch("NEWTON, THANDIE", "KUTCHER, ASHTON");

  auto it = test1->Table.find("KUTCHER, ASHTON");

  string build_path_string = "Actor: " + it->first + "; Movie: " + get<3>(it->second); 

  while(get<1>(it->second) != "x")

  {

    build_path_string += " Actor: " + get<1>(it->second) + "; Movie:" + get<3>(it->second);

    it = test1->Table.find(get<1>(it->second));
 82,151
  }

    cout << "The shortest path is: " << build_path_string << endl;

*/

 

  test1->dijkstraSearch("SMITH, JADEN", "HEMSWORTH, CHRIS");

  auto it = test1->Table.find("HEMSWORTH, CHRIS");

 // string build_path_string = "Actor: " + it->first + "; Movie: " + get<3>(it->second);

  string build_path_string = ""; 

  final_output.insert(final_output.begin(), it->first); 

  while(get<1>(it->second) != "x")

  {

   // it = test1->Table.find(get<1>(it->second));

    string year = to_string(get<4>(it->second));

    build_path_string += "(" + get<1>(it->second) + ")--[" + get<3>(it->second) + "#@" + year + "]-->";

    final_output.insert(final_output.begin(), build_path_string);  

  

    it = test1->Table.find(get<1>(it->second));

    build_path_string.clear();

  }

 

   cout <<  "The size of the vector is: " << final_output.size() << endl;  

   for(unsigned int i = 0; i < final_output.size(); i++)

   {

     cout << final_output.at(i);   

   }

 

   // cout << "The shortest path is: " << build_path_string << endl;
  delete test1;
}
