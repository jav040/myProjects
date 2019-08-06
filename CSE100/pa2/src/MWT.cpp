#include "MWTNode.hpp"
#include "MWT.hpp"
#include<string>
#include<unordered_map>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;



  MWTNode * root;
  vector< pair<unsigned int, string> > suggestions;// = new vector<  pair<unsigned int, string>  >;  
  

  /** Default constructor */
  MWT::MWT() : root(0){}
  

 //  Default destructor 
  MWT:: ~MWT() {
  
    deleteAll(root);
  
  }
  
  bool MWT::sortVectorAlpha(pair<unsigned int, string> word1, pair<unsigned int, string> word2)
  {
    return (word1.second < word2.second);
  }

  bool MWT::sortVectorFreq(pair<unsigned int, string> word1, pair<unsigned int, string> word2)
  {
    return (word1.first > word2.first);
  }



  bool MWT::insertNode(const string word)
  {
    MWTNode * currNode = this->root;
    char word_char;
    /** If tree is empty, set root to a new MWTNode */
    if(currNode == nullptr)
    {
      this->root = new MWTNode();
      currNode = this->root;
    }  
     
    for(unsigned int i = 0; i<word.size(); i++)
    {
      word_char = word[i];
      auto find_iterator = currNode->alphabet.find(word_char);
      if(find_iterator == currNode->alphabet.end())//char[i] IS NOT present in current MWTNode
      {
        currNode->alphabet.insert(make_pair(word_char, new MWTNode()));
        if(i!=word.size()-1)
        {
          currNode = currNode->alphabet.at(word_char);
        }
      }   
      else//char[i] IS present in current MWTNode
      {
        if(i != word.size()-1)
        {
          currNode = currNode->alphabet.at(word_char); 
        }
      }     
    }
      currNode->word_frequency[word_char]+=1;
      currNode->char_is_word[word_char] = true;
            
      return true;
   }


  
   MWTNode * MWT::findNode(const string & word, MWTNode * curr_node)
   {
     curr_node = this->root;
     for(unsigned int i = 0; i<word.size(); i++)
     {
       //Check to see if letter even exists in node. If not, exit early
       if(curr_node->alphabet.find(word[i]) == curr_node->alphabet.end())
       {
         return curr_node;
       }
    
       if(i != word.size()-1)
       {
         curr_node = curr_node->alphabet.at(word[i]);   
       }
     }
     return curr_node;
   }
  
 

  void MWT::searchDFS(MWTNode * curr_node, string beg_word, string prefix)
  {
    if(curr_node == nullptr || curr_node->alphabet.size() == 0)
    {
      return;
    }
    auto map_iterator = curr_node->alphabet.begin();
    while(map_iterator != curr_node->alphabet.end())
    {
      char word_char = map_iterator->first;
      string start_word = beg_word;
      start_word = start_word + word_char;
      if(curr_node->char_is_word[word_char] == true && start_word.find(prefix) != std::string::npos )
      {
        this->suggestions.push_back( make_pair(curr_node->word_frequency[word_char], start_word  )  );     
      }
      searchDFS(curr_node->alphabet.at(map_iterator->first), start_word, prefix);
      map_iterator++; 
    }
    return;
  }

/*
  vector<string> MWT::returnSuggestions(vector< pair<unsigned int, string> > input)  
  {
    vector<string> output1;
    if(input.size() == 0)
    {
      return output1;
    }

   sort(input.begin(), input.end(), sortVectorAlpha);
   stable_sort(input.begin(), input.end(), sortVectorFreq);
  
 
   for(unsigned int i = 0; i < 10; i++)
   {
     if(i == output1.size())
     {
         break;
     }
     output2.push_back(output1.at(i));
   }
  
 

       
    vector<string> output1;
    if(input.size() == 0)
    {
      return output1;
    }
    vector<string> output2;
    vector<int> frequency_vector;
    vector<int> double_frequency;
    unordered_map<int, int> double_map;

    //Create vector of max size 10 that's sorted by frequency in decreasing order
    for(unsigned int i = 0; i<input.size(); i++)
    { 
      frequency_vector.push_back(input.at(i).first); 
      auto it = double_map.find(input.at(i).first);
      //Case 1: not there
      if(it == double_map.end())
      {
        double_map[input.at(i).first] = 1;
      }
      //Case 2: It is there
      else
      {
        double_map[input.at(i).first]++;
      }
 
      output1.push_back(input.at(i).second);
    }
    for(unsigned int i = 0; i<frequency_vector.size(); i++)
    {
      if(double_map.find(frequency_vector.at(i)) != double_map.end())
      {
        //If frequency_vector.at(i) still in map, then hasn't been deleted yet. Add to double_frequency vector
        double_frequency.push_back(double_map[frequency_vector.at(i)]);
        double_map.erase(frequency_vector.at(i));
      }
    }



    auto final_beg = output1.begin();
    auto final_end = output1.begin();
    unsigned int j = 0;
    advance(final_end, double_frequency.at(j));
    sort(final_beg, final_end);
    while( j < double_frequency.size()-1)
    {
       advance(final_beg, double_frequency.at(j));
       j++;
       advance(final_end, double_frequency.at(j));
       sort(final_beg, final_end);
       
    }


     for(unsigned int i = 0; i < 10; i++)
     {
       if(i == output1.size())
       {
         break;
       }
       output2.push_back(output1.at(i));
     }

     return output1;
  }
*/

  void MWT::deleteAll(MWTNode *node)
  {
    if(node == nullptr)
    {
      return;
    }
    auto del_iterator = node->alphabet.begin();
    while(del_iterator != node->alphabet.end())
    {
      if(del_iterator->second != nullptr)
      {
        deleteAll(del_iterator->second);
      }
      del_iterator++;
    }
      delete(node);
  }



  

