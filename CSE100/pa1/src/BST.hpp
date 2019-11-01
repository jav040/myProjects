#ifndef BST_HPP
#define BST_HPP
#include <iostream>
#include <math.h>
#include "BSTIterator.hpp"
#include "BSTNode.hpp"
using namespace std;

template <typename Data>
class BST {
   protected:
    /** Pointer to the root of this BST, or 0 if the BST is empty */
    BSTNode<Data> *root;

    /** Number of Data items stored in this BST. */
    unsigned int isize;

    /** Height of this BST. */
    unsigned int iheight;

   public:
    /** define iterator as an aliased typename for BSTIterator<Data>. */
    typedef BSTIterator<Data> iterator;

    /** Default constructor.
        Initialize an empty BST.
     */
    BST() : root(0), isize(0), iheight(0) {}

    /** Default destructor.
        Delete every node in this BST.
     */
    // TODO
    virtual ~BST() {

	deleteAll(root);
     
     }

    /** Given a reference to a Data item, insert a copy of it in this BST.
     *  Return  true if the item was added to this BST
     *  as a result of this call to insert,
     *  false if an item equal to this one was already in this BST.
     *  Note: This function should use only the '<' operator when comparing
     *  Data items. (should not use ==, >, <=, >=)  For the reasoning
     *  behind this, see the assignment writeup.
     */
    // TODO
    virtual bool insert(const Data &item) 
    {
      BSTNode <Data> *new_node = new BSTNode<Data>(item);
      BSTNode <Data> *temp = this->root;
      unsigned int height = 1;

      if(temp == nullptr) //CASE 1: If tree was all NULL
      {
        this->root = new_node;
	height++;
	iheight = max(iheight, height);
	isize++;
	return true; 
      }

      while(temp->data != new_node->data)
      {
      	if(new_node->data < temp->data)// DECIDE TO GO LEFT OR RIGHT
        {
 	  if(temp->left == nullptr) // LEFT CHILD D.N.E
          {
	    new_node->parent = temp;
	    temp->left = new_node;
	    height++;
	    iheight = max(iheight, height);
 	    this->isize++;
	    return true;
	  } 
          else// LEFT CHILD EXISTS
	  {
	    temp = temp->left;
	    height++;
	    //iheight = max(iheight, height);
	  }
        }
	else if(temp->data < new_node->data)// DECIDE TO GO LEFT OR RIGHT
        {
 	  if(temp->right == nullptr) // RIGHT CHILD D.N.E
          {
	    new_node->parent = temp;
	    temp->right = new_node;
            height++;
	    iheight = max(iheight, height);
 	    isize++;
	    return true;
	  } 
          else// RIGHT CHILD EXISTS
	  {
	    temp = temp->right;
	    height++;
	    //iheight = max(iheight, height);
	  }
	}
	else
        {
	  break;
	}
  
      }
      return false;     
    }
   
    /** Find a Data item in the BST.
     *  Return an iterator pointing to the item, or pointing past
     *  the last node in the BST if not found.
     *  Note: This function should use only the '<' operator when comparing
     *  Data items. (should not use ==, >, <=, >=).  For the reasoning
     *  behind this, see the assignment writeup.
     */
    // TODO
    virtual iterator find(const Data &item) const {
	BSTNode<Data> *temp = this->root;
	while (temp != NULL)
        {
		if(!(item < temp->data) && !(temp->data < item)) //DATA == CURRENT NODE
        	{
        		return (BSTIterator<Data>(temp));
        	}
		else if(item < temp->data) 
          	{
        		// go left
        		temp = temp->left;
          	}
         	 else
          	{
  	  		// go right
  	  		temp = temp->right;
          	}
	}
       return typename BST<Data>::iterator(0); 
     }

    /** Return the number of items currently in the BST.
     */
    // TODO 
    unsigned int size() const {
	return isize;
    }

    /** Return the height of the BST.
     */
    // TODO
    unsigned int height() const {
	return iheight;
    }

/*
    unsigned int calcHeight(BSTNode<Data> *n)
    {
	if (n == NULL)
	{
		return 0;
	}
	else 
	{
		return max(calcHeight(n->left)+1, calcHeight(n->right)+1);
	}
    }*/

    /** Return true if the BST is empty, else false.
     */
    // TODO
    bool empty() const {
	if (this->root==NULL) 
	{
		return true;
	}
	return false;
    }

    /** Return an iterator pointing to the first item in the BST (not the root).
     */
    // TODO
    iterator begin() const 
     {
	//BSTIterator <Data>iter = new BSTIterator<Data>(this->root);
	 BSTNode<Data> *temp = this->root;
	 while(temp->left!=NULL)
         {
	   temp = temp->left;
	 }
	return BSTIterator<Data>(temp);

     }

    /** Return an iterator pointing past the last item in the BST.
     */
    iterator end() const { return typename BST<Data>::iterator(0); }

    /** Perform an inorder traversal of this BST.
     */
    void inorder() const { inorder(root); }

   private:
    /** Recursive inorder traversal 'helper' function */

    /** Inorder traverse BST, print out the data of each node in ascending
       order. Implementing inorder and deleteAll base on the pseudo code is an
       easy way to get started.
     */
    // TODO
    void inorder(BSTNode<Data> *n) const {
        /* Pseudo Code:
          if current node is null: return;
          recursively traverse left sub-tree
          print current node data
          recursively traverse right sub-tree
        */
	  if(n == NULL)
          {
            return;
	  }
	  inorder(n->left);
	  cout << n->data << endl;		
	  inorder(n->right);
    }

    /** Find the first element of the BST
     */
    static BSTNode<Data> *first(BSTNode<Data> *curr) {
        if (curr == 0) return 0;
        while (curr->left != 0) curr = curr->left;
        return curr;
    }

    /** do a postorder traversal, deleting nodes
     */
    // TODO
    static void deleteAll(BSTNode<Data> *n) {
        /* Pseudo Code:
          if current node is null: return;
          recursively delete left sub-tree
          recursively delete right sub-tree
          delete current node
        */
	  if(n == NULL)
          {
            return;
	  }
	  deleteAll(n->left);		
	  deleteAll(n->right);
	  delete(n);
    }
};

#endif  // BST_HPP

