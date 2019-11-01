#include "DocumentGenerator.hpp" 
#include <dirent.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>


using namespace std;

struct dirent * directory_input;
DIR * passed_directory;
unordered_map<string, vector<string> > word_list;


/*      DocumentGenerator constructor      */
//Given a directory, traverse through it and access it's files
DocumentGenerator::DocumentGenerator(const string & documentDirectory)
{   
    srand(time(NULL)); 
    passed_directory = opendir(documentDirectory.c_str());
    string build_line;
    bool firstWord = false;  

  //Iterate/traverse through directory
  while((directory_input = readdir(passed_directory)) != NULL)
  {
     vector<string> * words = new vector<string>();    
     string build_line;
     ifstream curr_file;
      string finalpath = documentDirectory + "/" + std::string(directory_input->d_name);
      curr_file.open(finalpath);
      
     firstWord = true;     

     //Access current file
     while(getline(curr_file, build_line))
     { 
        vector<string> * temp_line = tokenize(build_line); 
        words->insert(words->end(), temp_line->begin(), temp_line->end());
        populateList(words, firstWord);
        delete temp_line;
        firstWord = false;
     }
     delete words;
     curr_file.close();
  }
 /* 
  //Test tokenized results
  for(unsigned int i = 0; i<words->size(); i++)
  {
    cout << words->at(i) << endl;
  }
*/
closedir(passed_directory);
}   



/* Toeknizer */
//If an unwanted character is found, skip over it
//If a white space separator is found, break line over it
vector<string> * DocumentGenerator::tokenize(const string& line)
{
  vector<string> * words = new vector<string>();
  vector<char> word;
  for (unsigned char c : line)
  {

    //If an unwanted character is found, skip over it
    if (DocumentGenerator::UNWANTED_CHARACTERS.find(c) != string::npos)
    { 
      continue;
    }
    
   //If a punctuation mark is found, include it as it's own token
    if (DocumentGenerator::PUNCTUATION.find(c) != string::npos)
    {
      if(string(word.begin(),word.end()) != "")
      {
        words->push_back(string(word.begin(), word.end()));
      }
      words->push_back(string(1,c));    
      word.clear();
      continue;
    }

   
    //If no white space is found, add to vector<char> word
    if (DocumentGenerator::whitespace.find(c) == string::npos)
    {
      word.push_back(c);
    }
    

    //Whitespace was found. Add word
    else if (word.size() > 0)
    {
         words->push_back(string(word.begin(), word.end())); 
         word.clear();  
    }
  }//End for loop

  //If any words left over, add them 
  if (word.size()>0)
  {
    words->push_back(string(word.begin(), word.end()));
  }

  return words; 
}







  //Method that populates the words_list map
  void DocumentGenerator::populateList(vector<string> * input1, bool documentCheck)
  {
    
    //Make the first word in the document be preceeded by a period
    if(documentCheck == true)
    {
      DocumentGenerator::word_list["."].push_back(input1->at(0));
    }
  
    //First populate the map in case not all keys have been inserted
    for(unsigned int i = 0; i < input1->size()-1; i++)
    {
      DocumentGenerator::word_list[input1->at(i)]; 
    }

    //Assign the map values
    for(unsigned int i = 0; i < input1->size()-1; i++)
    {
      for(unsigned int j = i; j < i+1; j++)
      {
        DocumentGenerator::word_list[input1->at(j)].push_back((input1->at(j+1)));
      }
    }   
  }

  string DocumentGenerator::generateNextWord(const string & prevWord)
  {
    string next_word;

    if(DocumentGenerator::word_list.find(prevWord) != DocumentGenerator::word_list.end())
    {
       int vector_size = DocumentGenerator::word_list[prevWord].size();
       int  rand_index = rand()%vector_size;
       next_word = DocumentGenerator::word_list[prevWord].at(rand_index);
    }  
    return next_word;  
  }



  string DocumentGenerator::generateDocument(const int numWords)
  {
    int i = 0;
    std::string return_word;
    return_word.reserve(10000000);
    string temp_word = generateNextWord(".");
     return_word += temp_word;
    while(i < numWords - 1)
    { 
      i++;
      temp_word = generateNextWord(temp_word);
      if(temp_word.size() == 1 && DocumentGenerator::PUNCTUATION.find(temp_word) != string::npos)
      {
       // return_word = return_word + temp_word;
          return_word+=temp_word;
      }
      else
      {
       // return_word.push_back(" ");
       // return_word.push_back(temp_word);
//        return_word = return_word + " " + temp_word;
       return_word+=" ";
       return_word+=temp_word;
      }
    }
    return return_word;
  }





































