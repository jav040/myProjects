/*
 * Given two strings, return true if each character in the string is unique,
 * return false otherwise
 *
 */

#include <iostream>
#include <vector>

using namespace std;


int main(int argc, char*argv[])
{

    std::vector<int> char_array(256,0);
    string word;
    cout << "Enter the string to be checked\n";
    cin >> word;
    for(int i = 0; i < word.size(); i++)
    {
        if((char_array.at(word.at(i))) == 0)
        {
            char_array.at(word.at(i)) = 1;
        }
        else{
            cout << "Not unique";
            return 0;
        }
    }

    cout << "Each character is unique";

}
