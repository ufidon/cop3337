#ifndef BST_H
#define BST_H

#include <vector>
#include <stdexcept>
using namespace std;

template<typename T>
class TreeNode
{
public:
  T element; // Element contained in the node
  TreeNode<T>* left; // Pointer to the left child
  TreeNode<T>* right; // Pointer to the right child

  TreeNode(T element) // Constructor
  {
    this->element = element;
    left = NULL;
    right = NULL;
  }
};

template <typename T>
class Iterator : public std::iterator<std::forward_iterator_tag, T>
{
public:
  Iterator(TreeNode<T>* p)
  {
    if (p == NULL)
      current = -1; // The end
    else
    {
      // Get all the elements in inorder
      treeToVector(p);
      current = 0;
    }
  }

  Iterator operator++()
  {
    current++;
    if (current == v.size())
      current = -1; // The end
    return *this;
  }

  T &operator*()
  {
    return v[current];
  }

  bool operator == (const Iterator<T> &iterator) const
  {
    return current == iterator.current;
  }

  bool operator != (const Iterator<T> &iterator) const
  {
    return current != iterator.current;
  }

private:
  int current;
  vector<T> v;
  void treeToVector(TreeNode<T>* p)
  {
    if (p != NULL)
    {
      treeToVector(p -> left);
      v.push_back(p -> element);
      treeToVector(p -> right);
    }
  }
};

template <typename T>
class BST
{
public:
  BST();
  BST(T elements[], int arraySize);
  BST(BST<T> &tree);
  ~BST();
  bool search(T element) const;
  virtual bool insert(T element);
  virtual bool remove(T element);
  void inorder() const;
  void preorder() const;
  void postorder() const;
  int getSize() const;
  void clear();
  vector<TreeNode<T>* >* path(T element) const;

  Iterator<T> begin() const
  {
    return Iterator<T>(root);
  };

  Iterator<T> end() const
  {
    return Iterator<T>(NULL);
  };

protected:
  TreeNode<T>* root;
  int size;
  virtual TreeNode<T>* createNewNode(T element);

private:
  void inorder(TreeNode<T>* root) const;
  void postorder(TreeNode<T>* root) const;
  void preorder(TreeNode<T>* root) const;
  void copy(TreeNode<T>* root);
  void clear(TreeNode<T>* root);
};

template <typename T>
BST<T>::BST()
{
  root = NULL;
  size = 0;
}

template <typename T>
BST<T>::BST(T elements[], int arraySize)
{
  root = NULL;
  size = 0;

  for (int i = 0; i < arraySize; i++)
  {
    insert(elements[i]);
  }
}

/* Copy constructor */
template <typename T>
BST<T>::BST(BST<T> &tree)
{
  root = NULL;
  size = 0;
  copy(tree.root); // Recursively copy nodes to this tree
}

/* Copies the element from the specified tree to this tree */
template <typename T>
void BST<T>::copy(TreeNode<T>* root)
{
  if (root != NULL)
  {
    insert(root->element);
    copy(root->left);
    copy(root->right);
  }
}

/* Destructor */
template <typename T>
BST<T>::~BST()
{
  clear();
}

/* Return true if the element is in the tree */
template <typename T>
bool BST<T>::search(T element) const
{
  TreeNode<T>* current = root; // Start from the root

  while (current != NULL)
    if (element < current->element)
    {
      current = current->left; // Go left
    }
    else if (element > current->element)
    {
      current = current->right; // Go right
    }
    else // Element matches current.element
      return true; // Element is found

  return false; // Element is not in the tree
}

template <typename T>
TreeNode<T>*  BST<T>::createNewNode(T element)
{
  return new TreeNode<T>(element);
}

/* Insert element into the binary tree
 * Return true if the element is inserted successfully
 * Return false if the element is already in the list
 */
template <typename T>
bool BST<T>::insert(T element)
{
  if (root == NULL)
    root = createNewNode(element); // Create a new root
  else
  {
    // Locate the parent node
    TreeNode<T>* parent = NULL;
    TreeNode<T>* current = root;
    while (current != NULL)
      if (element < current->element)
      {
        parent = current;
        current = current->left;
      }
      else if (element > current->element)
      {
        parent = current;
        current = current->right;
      }
      else
        return false; // Duplicate node not inserted

    // Create the new node and attach it to the parent node
    if (element < parent->element)
      parent->left = createNewNode(element);
    else
      parent->right = createNewNode(element);
  }

  size++;
  return true; // Element inserted
}

/* Inorder traversal */
template <typename T>
void BST<T>::inorder() const
{
  inorder(root);
}

/* Inorder traversal from a subtree */
template <typename T>
void BST<T>::inorder(TreeNode<T>* root) const
{
  if (root == NULL) return;
  inorder(root->left);
  cout << root->element << " ";
  inorder(root->right);
}

/* Postorder traversal */
template <typename T>
void BST<T>::postorder() const
{
  postorder(root);
}

/** Inorder traversal from a subtree */
template <typename T>
void BST<T>::postorder(TreeNode<T>* root) const
{
  if (root == NULL) return;
  postorder(root->left);
  postorder(root->right);
  cout << root->element << " ";
}

/* Preorder traversal */
template <typename T>
void BST<T>::preorder() const
{
  preorder(root);
}

/* Preorder traversal from a subtree */
template <typename T>
void BST<T>::preorder(TreeNode<T>* root) const
{
  if (root == NULL) return;
  cout << root->element << " ";
  preorder(root->left);
  preorder(root->right);
}

/* Get the number of nodes in the tree */
template <typename T>
int BST<T>::getSize() const
{
  return size;
}

/* Remove all nodes from the tree */
template <typename T>
void BST<T>::clear()
{
  // Left as exercise
}

/* Return a path from the root leading to the specified element */
template <typename T>
vector<TreeNode<T>*>* BST<T>::path(T element) const
{
  vector<TreeNode<T>* >* v = new vector<TreeNode<T>* >();
  TreeNode<T>* current = root;

  while (current != NULL)
  {
    v->push_back(current);
    if (element < current->element)
      current = current->left;
    else if (element > current->element)
      current = current->right;
    else
      break;
  }

  return v;
}

/* Delete an element from the binary tree.
 * Return true if the element is deleted successfully
 * Return false if the element is not in the tree */
template <typename T>
bool BST<T>::remove(T element)
{
  // Locate the node to be deleted and also locate its parent node
  TreeNode<T>* parent = NULL;
  TreeNode<T>* current = root;
  while (current != NULL)
  {
    if (element < current->element)
    {
      parent = current;
      current = current->left;
    }
    else if (element > current->element)
    {
      parent = current;
      current = current->right;
    }
    else
      break; // Element is in the tree pointed by current
  }

  if (current == NULL)
    return false; // Element is not in the tree

  // Case 1: current has no left children
  if (current->left == NULL)
  {
    // Connect the parent with the right child of the current node
    if (parent == NULL)
    {
      root = current->right;
    }
    else
    {
      if (element < parent->element)
        parent->left = current->right;
      else
        parent->right = current->right;
    }

    delete current; // Delete current
  }
  else
  {
    // Case 2: The current node has a left child
    // Locate the rightmost node in the left subtree of
    // the current node and also its parent
    TreeNode<T>* parentOfRightMost = current;
    TreeNode<T>* rightMost = current->left;

    while (rightMost->right != NULL)
    {
      parentOfRightMost = rightMost;
      rightMost = rightMost->right; // Keep going to the right
    }

    // Replace the element in current by the element in rightMost
    current->element = rightMost->element;

    // Eliminate rightmost node
    if (parentOfRightMost->right == rightMost)
      parentOfRightMost->right = rightMost->left;
    else
      // Special case: parentOfRightMost->right == current
      parentOfRightMost->left = rightMost->left;

    delete rightMost; // Delete rightMost
  }

  size--;
  return true; // Element inserted
}

#endif
