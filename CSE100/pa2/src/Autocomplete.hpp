/**
 *  CSE 100 PA2 C++ Autocomplete
*/

#ifndef AUTOCOMPLETE_HPP
#define AUTOCOMPLETE_HPP

#include <vector>
#include <string>
#include "MWT.hpp"
#include <unordered_map>
#include <algorithm>



using namespace std;

/**
 *  You may implement this class as either a mulit-way trie
 *  or a ternary search trie.
 *
 *  You may not use std::map in this implementation
 */

class Autocomplete
{
public:

  MWT * autocomp_mwt;
  int size;
  /* 
  Create an Autocomplete object.
  This object should be trained on the corpus vector
  That is - the predictCompletions() function below should pull autocomplete
  suggestions from this vector
  This vector will likely contain duplicates.
  This duplication should be your gauge of frequencey.

  Input: corpus - the corpus of words to learn from.
  Assume preprocessing has been done for you on this! E.g.
  if one of the words is "dán't", assume that each of those characters
  should be included in your trie and don't modify that word any further
  */


 
    Autocomplete(const vector<string> & corpus);


  /* Return up to 10 of the most frequent completions
   * of the prefix, such that the completions are words in the dictionary.
   * These completions should be listed from most frequent to least.
   * If there are fewer than 10 legal completions, this
   * function returns a vector with as many completions as possible.
   * Otherwise, 10 completions should be returned.
   * If no completions exist, then the function returns a vector of size 0.
   * The prefix itself might be included in the returned words if the prefix
   * is a word (and is among the 10 most frequent completions
   * of the prefix)
   * If you need to choose between two or more completions which have the same frequency,
   * choose the one that comes first in alphabetical order.
   *
   * Inputs: prefix. The prefix to be completed. Must be of length >= 1.
   * Return: the vector of completions
   */
  vector<string> predictCompletions(const string & prefix) const;



  /* Destructor */
  ~Autocomplete();
};

#endif // AUTOCOMPLETE_HPP
