/**
 * 
 */

//package hw2;

import java.util.*;

public class MyLinkedList<E> extends AbstractList<E> {
  
  private int nelems;
  private Node head;
  private Node tail;
  
  protected class Node {
    E data;
    Node next;
    Node prev;
    
    /** Constructor to create singleton Node */
    public Node(E element)
    {
		/* Add your implementation here */
    }
    /** Constructor to create singleton link it between previous and next 
      *   @param element Element to add, can be null
      *   @param prevNode predecessor Node, can be null
      *   @param nextNode successor Node, can be null 
      */
    public Node(E element, Node prevNode, Node nextNode)
    {
		/* Add your implementation here */
    }
    /** Remove this node from the list. Update previous and next nodes */
    public void remove()
    {
		/* Add your implementation here */
    }
    /** Set the previous node in the list
      *  @param p new previous node
      */
    public void setPrev(Node p)
    {
		/* Add your implementation here */
    }
	
    /** Set the next node in the list
      *  @param n new next node
      */
    public void setNext(Node n)
    {
		/* Add your implementation here */
    }
    
    /** Set the element 
      *  @param e new element 
      */
    public void setElement(E e)
    {
		/* Add your implementation here */
    }
    /** Accessor to get the next Node in the list */
    public Node getNext()
    {
      return (Node) null; // XXX-CHANGE-XXX
    }
    /** Accessor to get the prev Node in the list */
    public Node getPrev()
    {
      return (Node) null; // XXX-CHANGE-XXX
    } 
    /** Accessor to get the Nodes Element */
    public E getElement()
    {
      return (E) null; // XXX-CHANGE-XXX
    } 
  }
  
  /** ListIterator implementation */ 
  protected class MyListIterator implements ListIterator<E> {
    
    private boolean forward;
    private boolean canRemove;
    private Node left,right; // Cursor sits between these two nodes
    private int idx;        // Tracks current position. what next() would
    // return 
    public MyListIterator()
    {
		/* Add your implementation here */
    }
    @Override
    public void add(E e) throws  IllegalArgumentException
    {
		/* Add your implementation here */
    }
    @Override
    public boolean hasNext()
    {
      return false; // XXX-CHANGE-XXX
    }
    
    @Override
    public boolean hasPrevious()
    {
      return false; // XXX-CHANGE-XXX
    }
    @Override
    public E next() throws NoSuchElementException
    {
      return (E) null;  // XXX-CHANGE-XXX
    }
    @Override
    public int nextIndex()
    {
      return 0; // XXX-CHANGE-XXX
    }
    @Override
    public E previous() throws NoSuchElementException
    {
      return (E) null; // XXX-CHANGE-XXX
    }
    
    @Override
    public int previousIndex()
    {
      return 0;  // XXX-CHANGE-XXX
    }
    @Override
    public void remove() throws IllegalStateException
    {
		/* Add your implementation here */
    }
    @Override
    public void set(E e) 
      throws IllegalArgumentException,IllegalStateException
    {
		/* Add your implementation here */
    }
    
  }
  
  
  //  Implementation of the MyLinkedList Class
  
  
  /** Only 0-argument constructor is define */
  public MyLinkedList()
  {
  }
  @Override
  public int size()
  {
    // need to implement the size method
    return 0; // XXX-CHANGE-XXX 
  }
  
  @Override
  public E get(int index) throws IndexOutOfBoundsException
  {
    return (E) null;  // XXX-CHANGE-XXX
  }
  
  @Override
  /** Add an element to the list 
    * @param index  where in the list to add
    * @param data data to add
    * @throws IndexOutOfBoundsException
    * @throws IllegalArgumentException
    */ 
    public void add(int index, E data) 
    throws IndexOutOfBoundsException,IllegalArgumentException
  {
	  /* Add your implementation here */
  }
  /** Add an element to the end of the list 
    * @param data data to add
    * @throws IllegalArgumentException
    */ 
  public boolean add(E data) throws IllegalArgumentException
  {
    return true; // XXX-CHANGE-XXX
  }
  
  /** Set the element at an index in the list 
    * @param index  where in the list to add
    * @param data data to add
    * @return element that was previously at this index.
    * @throws IndexOutOfBoundsException
    * @throws IllegalArgumentException
    */ 
  public E set(int index, E data) 
    throws IndexOutOfBoundsException,IllegalArgumentException
  {
    return (E) null; // XXX-CHANGE-XXX
  }
  
  /** Remove the element at an index in the list 
    * @param index  where in the list to add
    * @return element the data found
    * @throws IndexOutOfBoundsException
    */ 
  public E remove(int index) throws IndexOutOfBoundsException
  {
    return (E) null; // XXX-CHANGE-XXX
  }
  
  /** Clear the linked list */
  public void clear()
  {
	  /* Add your implementation here */
  }
  
  /** Determine if the list empty 
    *  @return true if empty, false otherwise */
  public boolean isEmpty()
  {
    return true;  // XXX-CHANGE-XXX
  }
  
  public Iterator<E> QQQiterator()
  {
    return new MyListIterator();
  }
  public ListIterator<E> QQQlistIterator()
  {
    return new MyListIterator();
  }
  
  // Helper method to get the Node at the Nth index
  private Node getNth(int index) 
  {
    return (Node) null;  // XXX-CHANGE-XXX
  }
  
  
  
  
  /*  UNCOMMENT the following when you believe your MyListIterator class is
   functioning correctly
   public Iterator<E> iterator()
   {
   return new MyListIterator();
   }
   public ListIterator<E> listIterator()
   {
   return new MyListIterator();
   }
   */
}

// VIM: set the tabstop and shiftwidth to 4 
// vim:tw=78:ts=4:et:sw=4

