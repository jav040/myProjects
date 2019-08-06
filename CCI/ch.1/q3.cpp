/*Interesting Notes: I first used cin >> sentence, but the sentence would stop reading after the first white space, instead I need to use std::getline(std::cin, sentence)
 */
/*Main question: Return the original inputted string, with a '%20' in the slot of every white space 
 */

#include <iostream>
#include <vector>
using namespace std;


int main(int argc, char * argvp[])
{

    int sentence_count = 0;
    string sentence;
    cout << "Please enter the sentence \n";
    std::getline(std::cin, sentence);
    cout << "Original sentence length: " + std::to_string(sentence.size()) + "\n";

    for(int i  = 0; i< sentence.size(); i++)
    {
        if(isspace(sentence.at(i)))
        {
            sentence_count++;
        }
    }

    int new_length = sentence.size() + 2*sentence_count;
    std::string new_sentence(new_length, '\0');
    int index = 0;
    cout << "sentence count: " + std::to_string(sentence_count) + "\n";
    cout << "New sentence length: " + std::to_string(new_sentence.size()) + "\n";
    for(int i = 0; i < sentence.size(); i++)
    {
        cout << "new sentence at iteration " + std::to_string(i) + " is " + "    " + new_sentence + "\n";
        if(sentence.at(i) != ' ')
        {
          new_sentence.at(index) = sentence.at(i);
          index++;
        }
        else
        {
            new_sentence.at(index) = '%';
            new_sentence.at(index+1) = '2';
            new_sentence.at(index+2) = '0';
            index += 3;
        }

    }

    cout << "The new sentence is: " + new_sentence + "\n";

}
