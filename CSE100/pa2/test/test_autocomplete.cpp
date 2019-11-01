#include "../src/Autocomplete.hpp"
#include <vector>
#include <string>
#include "../src/MWT.hpp"
#include <unordered_map>
#include <iostream>


int main() {

 
  cout << "--------------TEST1------------------" << endl;
/*    TEST1       */
/* TEST WHERE PREFIX IS ONE OF THE WORDS IN THE MWT */

  vector<string> test1_strings;
  vector<string> return_strings;
  test1_strings.push_back("happening");
  test1_strings.push_back("happy");
  test1_strings.push_back("hack");
  test1_strings.push_back("hat");
  test1_strings.push_back("labtop");
  test1_strings.push_back("imperialbeach");
  test1_strings.push_back("chulavista");
  test1_strings.push_back("california");

  Autocomplete * test1 = new Autocomplete(test1_strings);
  return_strings = test1->predictCompletions("chula");
  for(int i = 0; i < return_strings.size(); i++)
  {
    cout << return_strings.at(i) << endl;
  }
  cout << "--------------TEST2------------------" << endl;
   

/*      TEST2       */

  vector<string> test2_strings;
  vector<string> return_strings2;
  test2_strings.push_back("peter");
  test2_strings.push_back("pete");
  test2_strings.push_back("pete");
  test2_strings.push_back("pete");
  test2_strings.push_back("penut");
  test2_strings.push_back("penut");
  test2_strings.push_back("penut");
  test2_strings.push_back("penut");
  test2_strings.push_back("penut");
  test2_strings.push_back("penut");
  test2_strings.push_back("phone");
  
  Autocomplete * test2 = new Autocomplete(test2_strings);
  return_strings2 = test2->predictCompletions("pe");
  for(int i = 0; i < return_strings2.size(); i++)
  {
    cout << return_strings2.at(i) << endl;
  }
  cout << "-----------------TEST3--------------------" << endl;

   /*TEST3 */ 
  /* Test empty function */

  vector<string> empty_corpus;
  vector<string> return_strings3;
  Autocomplete * test3 = new Autocomplete(empty_corpus);
  return_strings3 = test3->predictCompletions("hi");
  cout << "size of predictCompletions on empty corpus is: " << return_strings3.size() << endl;

  cout << "---------------TEST4--------------------" << endl;


   /*     TEST4      */
   /* Test predictions on a word that's not there */

   vector<string> test4_strings;
   vector<string> return_strings4;
   test4_strings.push_back("hi");
   test4_strings.push_back("he");
   test4_strings.push_back("ha");
   test4_strings.push_back("lol");
   Autocomplete * test4 = new Autocomplete(test4_strings);
   return_strings4 = test4->predictCompletions("win");
   for(int i = 0; i < return_strings4.size(); i++)
   {
     cout << return_strings4.at(i) << endl;
   } 
   cout << "the size of a return_strings vector that didn't contain the prefix is " << return_strings4.size() << endl;

   cout << "--------------TEST5------------------" << endl;




   /*      TEST5    */
   /* Test a single word corpus where prefix EXISTS*/

   vector<string> test5_strings;
   vector<string> return_strings5;
   test5_strings.push_back("hi");
   Autocomplete * test5 = new Autocomplete(test5_strings); 
   return_strings5 = test5->predictCompletions("h");  
   for(int i = 0; i<return_strings5.size(); i++)  
   {
     cout << return_strings5.at(i) << endl;
   }

   cout << "-------------TEST6------------" << endl;
   

	/*      TEST6    */
   /* Test a single word corpus where prefix DOES NOT EXIST*/

   vector<string> test6_strings;
   vector<string> return_strings6;
   test6_strings.push_back("hi");
   Autocomplete * test6 = new Autocomplete(test6_strings); 
   return_strings6 = test6->predictCompletions("j");  
   for(int i = 0; i<return_strings6.size(); i++)  
   {
     cout << return_strings6.at(i) << endl;
   }

   cout << "the size of a return_strings vector that didn't contain the prefix is " << return_strings6.size() << endl;

    cout << "---------------TEST7---------------------" << endl;


   /*       TEST7      */
   /*       TEST WORDS THAT ARE INSERTED IN INCREASING FREQUENCY */

   vector<string> test7_strings;
   vector<string> return_strings7;
   test7_strings.push_back("hi");
   test7_strings.push_back("hi");
   test7_strings.push_back("hit");
   test7_strings.push_back("hit");
   test7_strings.push_back("hit");
   test7_strings.push_back("hiss");
   test7_strings.push_back("hiss");
   test7_strings.push_back("hiss");
   test7_strings.push_back("hiss");
   test7_strings.push_back("hise");
   test7_strings.push_back("hide");
   test7_strings.push_back("hide");
   test7_strings.push_back("hide");
   test7_strings.push_back("hide");
   test7_strings.push_back("hike");
   test7_strings.push_back("hike");
   test7_strings.push_back("hike");
   test7_strings.push_back("hike");
   test7_strings.push_back("hike");
   test7_strings.push_back("hike");
   test7_strings.push_back("a");
   test7_strings.push_back("b");
   test7_strings.push_back("c");
   test7_strings.push_back("d");
   test7_strings.push_back("f");
   test7_strings.push_back("g");
   test7_strings.push_back("i");
   Autocomplete * test7 = new Autocomplete(test7_strings);
   return_strings7 = test7->predictCompletions("h");
   for(int i = 0; i < return_strings7.size(); i++)
   {
     cout << return_strings7.at(i) << endl;
   }

  cout << "------------TEST8----------" << endl;




   /*      TEST8     */
   /* TEST THAT MAX OF 10 WORDS ARE RETURNED FOR SUGGESTIONS */

   vector<string> test8_strings;
   vector<string> return_strings8;
   test8_strings.push_back("wo");
   test8_strings.push_back("wor");
   test8_strings.push_back("woke");
   test8_strings.push_back("woops");
   test8_strings.push_back("wont");
   test8_strings.push_back("wood");
   test8_strings.push_back("wolf");
   test8_strings.push_back("won");
   test8_strings.push_back("worth");
   test8_strings.push_back("what");
   test8_strings.push_back("why");
   test8_strings.push_back("when");
   test8_strings.push_back("who");
   Autocomplete * test8 = new Autocomplete(test8_strings);
   return_strings8 = test8->predictCompletions("w");
   for(int i = 0; i<return_strings8.size(); i++)
   {
     cout << return_strings8.at(i) << endl;
   }

  cout << "---------TEST9-------------" << endl;



  /*       TEST9      */
  /* TEST THAT WORDS COME BACK IN ALPHABETICAL ORDER */

  vector<string> test9_strings;
  vector<string> return_strings9;
  test9_strings.push_back("abc");
  test9_strings.push_back("abc");
  test9_strings.push_back("abc");
  test9_strings.push_back("acc");
  test9_strings.push_back("acd");    
  test9_strings.push_back("acc");
  test9_strings.push_back("acd");    
  test9_strings.push_back("azz");
  test9_strings.push_back("azz");
  test9_strings.push_back("azz");
  Autocomplete * test9 = new Autocomplete(test9_strings);
  return_strings9 = test9 ->predictCompletions("a");
  for(int i = 0; i < return_strings9.size(); i++)
  {
    cout << return_strings9.at(i) << endl;
  }


  cout << "---------TEST10-------------" << endl;
  /*        TEST10        */
  /* TEST FINDING SINGLE CHARACTER ON MANY WORDED MWT */

  vector<string> test10_strings;
  vector<string> return_strings10;
  test10_strings.push_back("ta");
  test10_strings.push_back("ta");
  test10_strings.push_back("ta");
  test10_strings.push_back("ta");
  test10_strings.push_back("tb");
  test10_strings.push_back("tb");
  test10_strings.push_back("tb");
  test10_strings.push_back("tb");
  test10_strings.push_back("tc");
  test10_strings.push_back("tc");
  test10_strings.push_back("tc");
  test10_strings.push_back("tc");
  test10_strings.push_back("tc");
  test10_strings.push_back("td");
  test10_strings.push_back("td");
  test10_strings.push_back("td");
  test10_strings.push_back("td");
  test10_strings.push_back("td");
 
  Autocomplete * test10 = new Autocomplete(test10_strings);
  return_strings10 = test10->predictCompletions("t");
  for(int i = 0; i < return_strings10.size(); i++)
  {
    cout << return_strings10.at(i) << endl;
  }









}


