#ifndef MWTNODE_HPP
#define MWTNODE_HPP
#include <string>
#include <unordered_map>

using namespace std;

class MWTNode 
{
    public:    
    unordered_map<char, int> word_frequency;
    unordered_map<char, bool> char_is_word; 
    unordered_map<char, MWTNode*> alphabet; 
   /**  Default argument constructor */ 
    MWTNode();

};




#endif //MWTNODE_HPP
