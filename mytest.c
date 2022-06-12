#include "unittest.h"
#include "assert.h"

#include "closest.c" // Imports your code

int main(int argc, char *argv[]) {

    //Test 1
    printf("Test 1\n");
    AVLNode* t1 = NULL;
    t1 = insert(t1, 1);
    t1 = insert(t1, 4);
    t1 = insert(t1, 3);
    t1 = insert(t1, 10);
    t1 = insert(t1, 2);
    
}