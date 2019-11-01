/* TEST FILE TO TEST DOCUMENTGENERATOR METHODS */


#include "DocumentGenerator.hpp"
#include <dirent.h>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main()
{
  string test1_dir = "./myTest1";
  DocumentGenerator test1 = DocumentGenerator(test1_dir); 
  string final_sentence = test1.generateDocument(5);
  cout << final_sentence << endl;

 


}
