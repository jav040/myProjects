#include "MWTNode.hpp"
#include <string>
#include <unordered_map>
using namespace std;

    
    unordered_map<char, unsigned int> word_frequency;
    unordered_map<char, bool> char_is_word; 
    unordered_map<char, MWTNode*> alphabet;
 

 
   /**  Default argument constructor */ 
   MWTNode::MWTNode(){} 





