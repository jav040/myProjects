/**
 *  CSE 100 PA2 C++ Autocomplete
*/

#include "Autocomplete.hpp"
#include "MWT.hpp"
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>



using namespace std;

  MWT * autocomp_mwt;
  unsigned int size; 




  Autocomplete::Autocomplete(const vector<string> & corpus)
  {
      this->autocomp_mwt = new MWT();
      this->size = 0;
    for(unsigned int i = 0; i<corpus.size(); i++)
    {
      autocomp_mwt->insertNode(corpus.at(i));
      this->size++;
    }
  }


  vector<string> Autocomplete::predictCompletions(const string & prefix) const
  { 
    /*First check for case of empty corpus*/
    if(this->size == 0)
    {
      return {};
    }
 
    vector<string> final_words;
    string beg_word = prefix;
    if(!beg_word.empty() && beg_word.size()!=1)
    {
      beg_word.resize(beg_word.size()-1);
    }
    MWTNode* passed_in_node = autocomp_mwt->findNode(prefix, this->autocomp_mwt->root);
    if(prefix.size() == 1)// If it's a single character    
    {
      // If single character has no prefix in tree
      
      if(passed_in_node->alphabet.find(prefix[0]) == passed_in_node->alphabet.end())
      {
        return final_words;
      }
      else
      {
        passed_in_node = passed_in_node->alphabet.at(prefix[0]);
      }
    }
    autocomp_mwt->searchDFS(passed_in_node, beg_word, prefix);
    if(autocomp_mwt->suggestions.size() != 0)
    {
      sort(autocomp_mwt->suggestions.begin(), autocomp_mwt->suggestions.end(), MWT::sortVectorAlpha);
      stable_sort(autocomp_mwt->suggestions.begin(), autocomp_mwt->suggestions.end(), MWT::sortVectorFreq);
      for(unsigned int i = 0; i < 10; i++)
      {
        if(i  == autocomp_mwt->suggestions.size())
        {
          break;
        }
        final_words.push_back(autocomp_mwt->suggestions.at(i).second);
      }
    }
      autocomp_mwt->suggestions.clear();
      return final_words;
    
    
   // final_words = autocomp_mwt->returnSuggestions(autocomp_mwt->suggestions);
    
  }


  /* Destructor */
  Autocomplete::~Autocomplete(){
   delete(autocomp_mwt);
   }

