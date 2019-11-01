#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "KDT.hpp"
#include <sstream>
using namespace std;

/**
 *  IMPORTANT!! YOU MUST USE THE FOLLOWING LINES OF CODE FOR PROMPTS AND
 * OUTPUTS: To output size of tree: cout << "Size of tree: " << size << "\n"; To
 * output height of tree: cout << "Height of tree: " << height << "\n"; To
 * prompt the user to enter a coordinate: cout << "Enter coordinate (x y): " <<
 * "\n";
 *
 *  To show the result of the nearest neighbor search: cout << "Nearest point in
 * tree: " << nearestNeighbor << "\n"; To prompt the user to try again: cout <<
 * "Search again? (y/n)" << "\n";
 *
 *  Use cin to process user input.
 *
 *  You MUST output size, then height, then prompt the user to search, as above.
 *
 *  You MUST have the prompt for entering the name appear if and only if
 *  the user input for trying again is "y" followed by the return key
 *  You MUST have the program exit (exiting the prompt loop) if and only if
 *  the user input for trying again is "n" followed by the return key
 *  You should handle other inputs for the retry prompt,
 *  but we will not be testing them.
 *
 *  Note that size, height, and nearestNeighbor are local variables in main that
 *  you should update accordingly.
 */

using namespace std;

int main(int argc, char *argv[]) {
    // Size of tree should be stored in local variable size.
    // Height of tree should be stored in local variable height.
    // Input name will be stored in a string name
    unsigned int size = 0;
    unsigned int height = 0;
    Point nearestNeighbor;

    // Check for Arguments
    if (argc != 2) {
        cout << "Invalid number of arguments.\n"
             << "Usage: ./main <input filename>.\n";
        return -1;
    }

    // Open file
    ifstream in;
    in.open(argv[1], ios::binary);

    // Check if input file was actually opened
    if (!in.is_open()) {
        cout << "Invalid input file. No file was opened. Please try again.\n";
        return -1;
    }

    // Check for empty file
    in.seekg(0, ios_base::end);
    unsigned int len = in.tellg();
    if (len == 0) {
        cout << "The file is empty. \n";
        return -1;
    }

    // Resets the stream to beginning of file
    in.seekg(0, ios_base::beg);

    // TODO
    // main function implementation should go here
    
	string coord = "";
	double xCord;
	double yCord;
	vector<Point> set_points;// Create a vector of points on the stack

    while(getline(in,coord))
    {
	istringstream inputStream (coord);//istringstream is used to separate strings
	inputStream >> xCord;
	inputStream >> yCord;
	set_points.push_back(Point(xCord, yCord));
	//cout << "coordinate points are: " << xCord << "," << yCord << endl;
    }

    KDT tree;
    size = tree.build(set_points);
    height = tree.height();

    cout << "Size of tree: " << size << "\n"; 
    cout << "Height of tree: " << height << "\n";

    char response = 'y';
    while (response == 'y') {
	cout << "Enter coordinate (x y): " << "\n";
	getline(cin, coord);
	istringstream inputStream (coord);//istringstream is used to separate strings
	inputStream >> xCord >> yCord;

	Point myPoint = Point(xCord, yCord);
	BST<Point>::iterator item = tree.findNearestNeighbor(myPoint);
	nearestNeighbor = *item;
	

	cout << "Nearest point in tree: " << nearestNeighbor << "\n";

	cout << "Search again? (y/n)"
             << "\n";
        cin >> response;
        cin.ignore();
        if (response != 'n' && response != 'y') {
            cout << "Invalid Response" << endl;
            return 1;
        }	
    }
  



    if (in.is_open()) {
        in.close();
    }

    return 0;
}

