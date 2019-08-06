#ifndef MWT_HPP
#define MWT_HPP
#include "MWTNode.hpp"
#include<string>
#include<unordered_map>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class MWT {

  public:

  MWTNode * root;
  vector< pair<unsigned int, string> > suggestions;  

  /** Default constructor */
  MWT();
  

 //  Default destructor 
  ~MWT(); 

  static bool sortVectorAlpha(pair<unsigned int, string> word1, pair<unsigned int, string> word2);
 

  static bool sortVectorFreq(pair<unsigned int, string> word1, pair<unsigned int, string> word2);
 
  bool insertNode(const string word);
    
   MWTNode * findNode(const string & word, MWTNode * tree);
 
  void searchDFS(MWTNode * curr_node, string beg_word, string prefix);

//  void searchDF2(MWTNode * curr_node, string beg_word, string prefix);

 // vector<string> returnSuggestions(vector< pair<unsigned int, string> > input); 
 
  void deleteAll(MWTNode *node);
  


};
#endif //MWT_HPP
