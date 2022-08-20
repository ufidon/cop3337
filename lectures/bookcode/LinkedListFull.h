#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <stdexcept>
using namespace std;

template<typename T>
class Node
{
public:
  T element;  // Element contained in the node
  Node<T> *next; // Pointer to the next node

  Node() // No-arg constructor
  {
    next = NULL;
  }

  Node(T element) // Constructor
  {
    this->element = element;
    next = NULL;
  }
};

template<typename T>
class LinkedList
{
public:
  LinkedList();
  void addFirst(T element);
  void addLast(T element);
  T getFirst() const;
  T getLast() const;
  T removeFirst() throw (runtime_error);
  T removeLast();
  void add(T element);
  void add(int index, T element);
  void clear();
  bool contains(T element);
  T get(int index) const;
  int indexOf(T element) const;
  bool isEmpty() const;
  int lastIndexOf(T element) const;
  bool remove(T element);
  int getSize() const;
  T remove(int index);
  T set(int index, T element);

private:
  Node<T> *head, *tail;
  int size;
};

template<typename T>
LinkedList<T>::LinkedList()
{
  head = tail = NULL;
  size = 0;
}

template<typename T>
void LinkedList<T>::addFirst(T element)
{
  Node<T> *newNode = new Node<T>(element);
  newNode->next = head;
  head = newNode;
  size++;

  if (tail == NULL)
    tail = head;
}

template<typename T>
void LinkedList<T>::addLast(T element)
{
  if (tail == NULL)
  {
    head = tail = new Node<T>(element);
  }
  else {
    tail->next = new Node<T>(element);
    tail = tail->next;
  }

  size++;
}

template<typename T>
T LinkedList<T>::getFirst() const
{
  if (size == 0)
    throw runtime_error("Index out of range");
  else
    return head->element;
}

template<typename T>
T LinkedList<T>::getLast() const
{
  if (size == 0)
    throw runtime_error("Index out of range");
  else
    return tail->element;
}

template<typename T>
T LinkedList<T>::removeFirst() throw (runtime_error)
{
  if (size == 0)
   throw runtime_error("No elements in the list");
  else
  {
    Node<T> *temp = head;
    head = head->next;
    size--;
    T element = temp->element;
    delete temp;
    return element;
  }
}

template<typename T>
T LinkedList<T>::removeLast()
{
  if (size == 0)
    throw runtime_error("No elements in the list");
  else if (size == 1)
  {
    Node<T> *temp = head;
    head = tail = NULL;
    size = 0;
    T element = temp->element;
    delete temp;
    return element;
  }
  else
  {
    Node<T> *current = head;

    for (int i = 0; i < size - 2; i++)
      current = current->next;

    Node<T> *temp = tail;
    tail = current;
    tail->next = NULL;
    size--;
    T element = temp->element;
    delete temp;
    return element;
  }
}

template<typename T>
void LinkedList<T>::add(T element)
{
  addLast(element);
}

template<typename T>
void LinkedList<T>::add(int index, T element)
{
  if (index == 0)
    addFirst(element);
  else if (index >= size)
    addLast(element);
  else
  {
    Node<T> *current = head;
    for (int i = 1; i < index; i++)
      current = current->next;
    Node<T> *temp = current->next;
    current->next = new Node<T>(element);
    (current->next)->next = temp;
    size++;
  }
}

template<typename T>
void clear()
{
  while (head != NULL)
  {
    Node<T> *temp = head;
    delete temp;
    head = head->next;
  }

  tail = NULL;
}

template<typename T>
T LinkedList<T>::get(int index) const
{
  if (index < 0 || index > size - 1)
    throw runtime_error("Index out of range");

  Node<T> *current = head;
  for (int i = 0; i < index; i++)
    current = current->next;

  return current->element;
}

template<typename T>
int LinkedList<T>::indexOf(T element) const
{
  // Implement it in this exercise
  Node<T> *current = head;
  for (int i = 0; i < size; i++)
  {
    if (current->element == element)
      return i;
    current = current->next;
  }

  return -1;
}

template<typename T>
bool LinkedList<T>::isEmpty() const
{
  return head == NULL;
}

template<typename T>
int LinkedList<T>::getSize() const
{
  return size;
}

template<typename T>
T LinkedList<T>::remove(int index)
{
  if (index < 0 || index >= size)
    throw runtime_error("Index out of range");
  else if (index == 0)
    return removeFirst();
  else if (index == size - 1)
    return removeLast();
  else {
    Node<T> *previous = head;

    for (int i = 1; i < index; i++)
    {
      previous = previous->next;
    }

    Node<T> *current = previous->next;
    previous->next = current->next;
    size--;
    T element = current->element;
    delete current;
    return element;
  }
}
template<typename T>
bool LinkedList<T>::remove(T element)
{
  Node<T> *previous = head;
  Node<T> *current;

  if (head != NULL)
  {
    if (element == head->element)
    {
      head = head->next;
      size--;
      return true;
    }
    else
    {
      current = head->next;
    }
  }
  else
    return false;

  for (int i = 0; i < size - 1; i++)
  {
    if (element == current->element) {
      previous->next = current->next; // Remove the current element
      size--;
      return true;
    }
    else
    {
      previous = current;
      current = current->next;
    }
  }

  return false;
}

template<typename T>
int LinkedList<T>::lastIndexOf(T element) const
{
  int lastIndex = -1;
  Node<T> *current = head;
  for (int i = 0; i < size; i++)
  {
    if (current->element == element)
      lastIndex = i;
    current = current->next;
  }

  return lastIndex;
}

template<typename T>
bool LinkedList<T>::contains(T element)
{
  // Implement it in this exercise
  Node<T> *current = head;
  for (int i = 0; i < size; i++)
  {
    if (current->element == element)
      return true;
    current = current->next;
  }

  return false;
}

template<typename T>
T LinkedList<T>::set(int index, T element)
{
  if (index < 0 || index >= size)
    throw runtime_error("Index out of range");

  Node<T> *current = head;
  for (int i = 0; i < index; i++)
  {
    current = current->next;
  }

  T oldElement = current->element;
  current->element = element;
  return oldElement;
}

#endif
