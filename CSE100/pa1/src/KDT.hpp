#ifndef KDT_HPP
#define KDT_HPP

#include <math.h>     // pow, abs
#include <algorithm>  // sort, max, min
#include <iostream>   // cout, cin, and cerr
#include <limits>     // numeric_limits<type>::max()
#include <vector>     // vector<typename>
#include "BST.hpp"

using namespace std;

class Point 
{
   private:
   double delta = 0.00005;

   public:
    /** x and y point coordinates */
   double x, y;

    /** Default constructor: point at (0, 0) */
    Point() : x(0.0), y(0.0) {}

    /** constructor that defines point location */
    Point(double x, double y) : x(x), y(y) {}

    /** Equals operator */
    bool operator==(const Point &other) const {
        return abs(x - other.x) < delta && abs(y - other.y) < delta;
    }

    /** Not-equals operator */
    bool operator!=(const Point &other) const {
        return abs(x - other.x) > delta || abs(y - other.y) > delta;
    }

    /** Less than operator */
    bool operator<(const Point &other) const {
        cerr << "This operator should not be called, you will need "
             << "check the x and y components each time" << endl;
        return false;
    }

    /** Return the squre of the Euclidean distance between two points p1 and p2
     */
    // TODO
    static double squareDistance(const Point &p1, const Point &p2) 
    {
        double delta_x = p2.x-p1.x;
	double delta_y = p2.y-p1.y;
	double dist = pow(delta_x,2) + pow(delta_y,2);
	return dist;
    }
};

std::ostream &operator<<(std::ostream &out, const Point &data) {
    out << "(" << data.x << ", " << data.y << ")";
    return out;
}

bool xLessThan(const Point &p1, const Point &p2) { return p1.x < p2.x; }

bool yLessThan(const Point &p1, const Point &p2) { return p1.y < p2.y; }

class KDT : public BST<Point> {
   public:
    /** Given a vector of Point references, insert a copy into the BST.
     *  Return the number of elements that the fully constructed tree contains
     *  Note. Because of the nature of the KDTree, a simple < operator
     *        will not be sufficient.  You will need to check the x and y
     *        coordinates individually.  Two functions have been provided
     *        for your convenience above, (xLessThan and yLessThan). You may
     *        find them useful for the sort function from #include<algorithm>.
     *  Note. Since KDT inherits from BST, you still have access to the
     *        root, isize, and iheight instance variables and should modify
     *        them accordingly.
     *  Note. We have also provided a private helper method for the build
     *        function called buildSubset defined below.
     */
    // TODO
    virtual unsigned int build(vector<Point> &items) 
    {
	isize = 0;
	if (items.size() == 0)
	{
		isize = 0;
		return isize;
	}
	this->root = buildSubset(items, 0, items.size(), 0, 1);
	//printTree(this->root); 
	//cout << "root: " << this->root->data << endl;
	//cout << "left kid: " << this->root->left->data << endl;
	//cout << "right kid: " << this->root->right->data << endl;
	//cout << "left-right kid: " << this->root->left->right->data << endl;
	//cout << "right-right kid: " << this->root->right->right->data << endl;

	return isize;
    }

    /** Find the nearest neighbor to a given point
     *  Returns the point in the kd-tree nearest to the parameter item.
     *  Note. THIS IS DIFFERENT THAN HOW THE PREVIOUS FIND FUNCTION WORKS
     *  Note. Since KDT inherits from BST, you still have access to the
     *        root, isize, and iheight member variables.
     *  Note. The dimension ordering you used to build the tree must be used
     *        to search through it.
     *  Note. We have added a private helper method for your convenience called
     *        findNNHelper defined below.
     */
    // TODO
    virtual iterator findNearestNeighbor(const Point &item) const 
    {	
	// Make a pointer to a pointer (**closest)
	BSTNode<Point> *temp = this->root;
   	BSTNode<Point> **closest_node = &temp;
		
	// Call NNHelper with **closest passed in as a parameter for **closestPoint
	double smallest_dist = item.squareDistance(this->root->data, item);
	double *dist_ptr = &smallest_dist;
	findNNHelper(this->root, item, dist_ptr, closest_node, 0);
	
	// Store that node inside an iterator 
	// Return the iterator 	
	return BSTIterator<Point>(*closest_node);
    }

    /** For the kd-tree, the find method should not be used.  Use the function
     *  findNearestNeighbor instead.
     */
    virtual iterator find(const Point &item) const override {
        cerr << "The KD Tree find method should not be called" << endl;
        cerr << "Use findNearestNeighbor instead" << endl;
        return 0;
    }

    /** For the kd-tree, the insert method should not be used.  The tree is
     *  built all at once.  There should be no scenario where you add individual
     * points.
     */
    virtual bool insert(const Point &item) override {
        cerr << "The KD Tree insert method should not be called" << endl;
        return false;
    }

   private:
    /** Recursively add a subset of the array to the KD tree
     *  Parameters items: the list of points that are used to build the kd tree
     *             start: the starting index for this subsection of the tree
     *             end: the non-inclusive ending index for this subtree
     *             dimension: 0 if sorting along the x-axis, and 1 if sorting
     *                        along the y-axis
     *  PostConditions: the parent node should have its left and right children
     *                  set if there are any available points and recursive
     *                  calls should be made for the left and right subtree
     *                  (again, if there are any remaining points).
     *  NOTE: We gave you two methods: xLessThan and yLessThan.  We expect you
     *        that you will find these methods very helpful.  For your sake,
     *        please keep this in mind.
     */
    // TODO
    BSTNode<Point> *buildSubset(vector<Point> items, unsigned int start,
                                unsigned int end, unsigned int dimension,
                                unsigned int height) {

	if(start>=end)
	{
		return nullptr;
	}

	unsigned int mid_value = (start+end-1)/2;
	isize++;
	BSTNode<Point> * median;

	// Sort in x dimension
	if(dimension == 0)
	{
		sort (items.begin()+start, items.begin()+end, xLessThan);	
	}
	//Sort in y dimension
	else
	{
		sort (items.begin()+start, items.begin()+end, yLessThan);
	}	

	median= new BSTNode<Point>(items.at(mid_value)); 

	median->left = buildSubset(items, start, mid_value, (dimension+1)%2, height+1);
	median->right = buildSubset(items, mid_value+1, end, (dimension+1)%2, height+1);
	if(median->left!=NULL)	
	{
	  median->left->parent = median;
	}
	if(median->right!=NULL)
	{
	  median->right->parent = median;
	}

	iheight = max(height, iheight);
	return median;

    }


    void printTree(BSTNode<Point> *n) const
    {
		if (n == NULL) { return; }
		printTree(n->left);
		cout << n->data << endl;
		printTree(n->right);
    }

    /** Find the node in the subtree with that is closest to the given point p
     *  Parameters: node the root of the subtree being searched
     *              queryPoint the point whose nearest neighbor should be found
     *              smallestSquareDistance the smallest distance value found in
     *                                     the tree so far which can be updated
     *              closestPoint the node corresponding to the current closest
     *                           node in the tree which can be udpated
     *              dimension flags whether the node parameter splits remaining
     *                        nodes in its subtree by the x or y dimension
     *                        (has the value of either 0 or 1)
     *  Return: a BSTNode object that represents the point in the subtree
     *          closest to the given point p (including the root node)
     */
    // TODO
 void findNNHelper(BSTNode<Point> *node, const Point &queryPoint,
                      double *smallestSquareDistance,
                      BSTNode<Point> **closestPoint,
                      unsigned int dimension) const {

	//bool isLeft;
	// Base case or for finished traversing
	if (node == NULL)
	{
		return;
	}
	// Check dimensions
	if (dimension == 0)
	{
		// Check which way to traverse
		if (queryPoint.x < node->data.x)
		{
			if (node->left == NULL)
			{	
			  return;
			}
			//isLeft = true;
			node = node->left;
		}
		else
		{
			if (node->right == NULL)
			{
				return;
			}
		//	isLeft = false;
			node = node->right;
		}
	}
	else //DImension ==1 
	{
		// Check which way to traverse
		if (queryPoint.y < node->data.y)
		{
			if (node->left == NULL)
			{
				return;
			}
		//	isLeft = true;
			node = node->left;
		}
		else
		{
			if (node->right == NULL)
			{
				return;
			}
		//	isLeft = false;
			node = node->right;
		}
	}
	
	// Recurse 
	findNNHelper(node, queryPoint, smallestSquareDistance, closestPoint, (dimension+1)%2);

	// Calculate squared distance 
//	double dist = (*closestPoint)->data.squareDistance((*closestPoint)->data, node->data);
	double dist = Point::squareDistance(node->data, queryPoint);
	
	// Compare distances and update if dist is smaller
	if (*smallestSquareDistance > dist)
	{
		*smallestSquareDistance = dist;
   		*closestPoint = node;
	}

	// Step 3
	double dimDist = 0;
	
	if (dimension == 0)
	{
		dimDist = node->data.x - queryPoint.x;
		//dimDist = pow(dimDist, 2);
	}
	else
	{
		dimDist = node->data.y - queryPoint.y;
		//dimDist = pow(dimDist, 2);
	}
	
	if(dimDist < *smallestSquareDistance)
	{

		findNNHelper(node, queryPoint, smallestSquareDistance, closestPoint, (dimension+1)%2);
	}
	return;
  }


};

#endif  // KDT_HPP

