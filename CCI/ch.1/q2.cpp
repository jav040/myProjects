/*
 * Given two strings, determine if one is a palindrome of the other
 */

#include <iostream>
#include <vector>
using namespace std;



int main(int argc, char*argv[])
{
    string w1, w2; 
    cout << "Enter the first word \n";
    cin >> w1;
    cout << "Enter the second word \n";
    cin >> w2;
    

    if (w1.size() != w2.size())
    { 
        cout << "Not same size, not a palindrom of each other \n";
        return 0; 
    }


    std::vector<int> char_freq(256,0);
    for(int i = 0; i < w1.size(); i++)
    {
        char_freq.at(w1.at(i))++;
    }

    for(int j = 0; j < w2.size(); j++)
    {
        int val = (int)w2.at(j);
        char_freq.at(val)--;
        if(char_freq.at(val) < 0 ){
            cout << "words are not palindromes of each other\n";
            return false;
        }
    }
    
    cout << "words are palindromes of each other\n";
    return true;

}
