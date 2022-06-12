/************************************************************************
 *                       CSCB63
 *                  Assignment 1 - AVL Trees
 *                  (c) Mustafa Quraish
 *
 * This is the file which should be completed and submitted by you
 * for the assignment. Make sure you have read all the comments
 * and understood what exactly you are supposed to do before you
 * begin. A few test cases are provided in `testClosest.c`, which
 * can be run on the command line as follows:
 *
 *  $> gcc testClosest.c -o testClosest
 *  $> ./testClosest [optional testname]  (or .\testClosest.exe if on Windows)
 *
 * I strongly advise that you write more test cases yourself to see
 * if you have expected behaviour, especially on the edge cases for
 * insert(). You are free to make any reasonable design choices for
 * the implementation of the data structure as long as (1) the outputs
 * are consistent with the expected results, and (2) you meet the
 * complexity requirement. Your closestPair() function will only
 * be tested with cases where there are unique solutions.
 *
 * Mark Breakdown (out of 10):
 *  - 0 marks if the code does not pass at least 1 test case.
 *  - If the code passes at least one test case, then:
 *    - Up to 6 marks for successfully passing all the test cases
 *    - Up to 4 marks for meeting the complexity requirements for 
 *        the functions as described in the comments below.
 *
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
/**
 * This defines the struct(ure) used to define the nodes
 * for the AVL tree we are going to use for this
 * assignment. You need to add some more fields here to be
 * able to complete the functions in order to meet the
 * complexity requirements
 */
typedef struct avl_node {
  // Stores the value (key) of this node
  int value;

  // Pointers to the children
  struct avl_node *left;
  struct avl_node *right;

  int height;
  int balance;

  // TODO: Add the other fields you need here to complete the assignment!
  //      (Hint: You need at least 1 more field to keep balance)

} AVLNode;;

AVLNode *newNode(int value);
AVLNode *insert(AVLNode *root, int value);
AVLNode *insertHelper(AVLNode *root, int value);
AVLNode* leftRotation(AVLNode* root);
AVLNode* rightRotation(AVLNode* root);
void closestPair(AVLNode *root, int *a, int *b);
void updateHeightAndBalance(AVLNode* root);
int getHeight(AVLNode* root);
int MAX(int a, int b);

void printPreOrder(AVLNode* t){
  if(t != NULL){
  printf("%d ", t->value);
  printPreOrder(t->left);
  printPreOrder(t->right);
  }
}

/**
 * This function allocates memory for a new node, and initializes it. 
 * The allocation is already completed for you, in case you haven't used C 
 * before. For future assignments this will be up to you!
 * 
 * TODO: Initialize the new fields you have added
 */
AVLNode *newNode(int value) {

  AVLNode *node = calloc(sizeof(AVLNode), 1);
  if (node == NULL) {  // In case there's an error
    return NULL;
  }

  node->value = value;
  node->left = NULL;
  node->right = NULL;

  // Initialize values of the new fields here...

  node->height = 1;
  node->balance = 0;

  return node;
}

AVLNode* rightRotation(AVLNode* root){
  //Check if left child is right heavy B < 0
  if(root->left->balance < 0){ 
    root->left = leftRotation(root->left);
  }

  //Do necessary Swaps
  AVLNode* newHead = root->left;
  AVLNode* leftRightChild = root->left->right;

  root->left = leftRightChild;
  newHead->right = root;

  //Update Height and Balance;
  updateHeightAndBalance(newHead->right);
  updateHeightAndBalance(newHead);

  return newHead;
}

AVLNode* leftRotation(AVLNode* root){
  //Check if right child is left heavy B > 0 
  if(root->right->balance > 0){ 
    root->right = rightRotation(root->right);
  }

  //Do necessary Swaps
  AVLNode* newHead = root->right;
  AVLNode* rightLeftChild = root->right->left;

  root->right = rightLeftChild;
  newHead->left = root;

  //Update Height and Balance;
  updateHeightAndBalance(newHead->left);
  updateHeightAndBalance(newHead);

  return newHead;
}

int getHeight(AVLNode* root){
  if(root == NULL){
    return 0;
  }
  return root->height;
}

void updateHeightAndBalance(AVLNode* root){
  root->height = MAX(getHeight(root->left), getHeight(root->right)) + 1; 
  root->balance = getHeight(root->left) - getHeight(root->right);
}

int MAX(int a, int b){
  if(a > b){
    return a;
  }
  else b;
}

/**
 * This function is supposed to insert a new node with the give value into the 
 * tree rooted at `root` (a valid AVL tree, or NULL)
 *
 *  NOTE: `value` is a positive integer in the range 1 - 1,000,000 (inclusive)
 *       The upper bound here only exists to potentially help make the 
 *                implementation of edge cases easier.
 *
 *  TODO:
 *  - Make a node with the value and insert it into the tree
 *  - Make sure the tree is balanced (AVL property is satisfied)
 *  - Return the *head* of the new tree (A balance might change this!)
 *  - Make sure the function runs in O(log(n)) time (n = number of nodes)
 * 
 * If the value is already in the tree, do nothing and just return the root. 
 * You do not need to print an error message.
 *
 * ----
 * 
 * An example call to this function is given below. Note how the
 * caller is responsible for updating the root of the tree:
 *
 *  AVLNod *root = (... some tree is initialized ...);
 *  root = insert(root, 5); // Update the root!
 */
AVLNode *insertHelper(AVLNode *root, int value) {

  //BaseCase
  if(root == NULL){
    return newNode(value);
  }

  //Recursive Case
  if(value < root->value){
    root->left = insertHelper(root->left, value);
  }else{
    root->right = insertHelper(root->right, value);
  }

  //Check Imbalance
  int balance = getHeight(root->left) - getHeight(root->right);
  if(balance > 1){
    return rightRotation(root);
  }
  else if(balance < -1){
    return leftRotation(root);
  }


  //Update Height And Balance
  //Occurs in Rotations now
  // root->height = MAX(getHeight(root->left), getHeight(root->right)) + 1; 
  // root->balance = getHeight(root->left) - getHeight(root->right);

  return root;  
}

AVLNode *insert(AVLNode *root, int value) {

  printf("Insert %d\n", value);

  AVLNode* newRoot = insertHelper(root, value);

  printPreOrder(newRoot);
  printf("\n");
  return newRoot;
}

/**
 * This function returns the closest pair of points in the tree rooted
 * at `root`. You can assume there are at least 2 values already in the
 * tree. Since you cannot return multiple values in C, for this function
 * we will be using pointers to return the pair. In particular, you need
 * to set the values for the two closest points in the locations pointed
 * to by `a` and `b`. For example, if the closest pair of points is
 * `10` and `11`, your code should have something like this:
 *
 *   (*a) = 10 // This sets the value at the address `a` to 10
 *   (*b) = 11 // This sets the value at the address `b` to 11
 *
 * NOTE: Make sure `(*a)` stores the smaller of the two values, and
 *                 `(*b)` stores the greater of the two values.
 * 
 * NOTE: The test cases will have a unique solution, don't worry about 
 *        multiple closest pairs here.
 *
 *
 * TODO: Complete this function to return the correct closest pair.
 *       Your function should not be any slower than O(log(n)), but if 
 *       you are smart about it you can do it in constant time.
 */
void closestPair(AVLNode *root, int *a, int *b) {
  

  (*a) = 0;  // Placeholder values for the closest pair,
  (*b) = 0;  // replace these with the actual ones.
  return;
}

/******************************************************************************
 * QUERY() and DELETE() are not part for this assignment, but I recommend you
 * try to implement them on your own time to make sure you understand how AVL
 * trees work.
 *
 *                              End of Assignment 1
 *****************************************************************************/
