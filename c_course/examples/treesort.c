/*
   Kara's C Course

   Example 4         © Kara Ottewell 1998-2018

   Purpose:
            Binary tree example demonstrating structure and pointer usage
*/
/*---- Illustration of pointer manipulation ("treesort.c") -------------------*/
/* Example provided by Rob Cannings:                                          */
/* (Excess white space removed by Kara O. ;-))                                */
/* We implement a sorting routine with the sorted list stored in a tree.      */

/* ANSI C Headers */
#include <stdio.h>
#include <stdlib.h>

/* Structures */
struct treeNode {
  int data;
  struct treeNode *left;
  struct treeNode *right;
};

/* Function prototypes */
void AddNode(struct treeNode **branch,struct treeNode *newNode);
void PrintTree(struct treeNode *node);

/* Defines and macros */
#define NUMBER_OF_NUMBERS 4

/* Main Program starts here */
int main(int argc,char *argv[])
{
    int i;
    int toBeSorted[NUMBER_OF_NUMBERS] = { 93, 27, 15, 47};
    struct treeNode dataNode[NUMBER_OF_NUMBERS];
    struct treeNode *sortedTree;
    struct treeNode *newNode;
/*  End of declarations ... */

/*  Initialise one node for each item of data */
    for (i = 0; i < NUMBER_OF_NUMBERS; i++) {
      dataNode[i].left = NULL;
      dataNode[i].right = NULL;
      dataNode[i].data = toBeSorted[i];
    }

/*  Build a sorted tree out of the data nodes, printing it */
/*  out after each new node is added to the tree           */
    sortedTree = NULL; /* the tree starts as just a stump */

    for (i = 0; i < NUMBER_OF_NUMBERS; i++) {
      newNode = &dataNode[i];
      AddNode(&sortedTree,newNode);
      printf("\nSorted list of %d items:\n",i + 1);
      PrintTree(sortedTree);
    }
    exit(EXIT_SUCCESS);
}

void AddNode(struct treeNode **branch,struct treeNode *newNode)
{
    struct treeNode *currentNode;
/*  End of declarations ... */

    currentNode = *branch; /* branch is a pointer to a pointer */

/*  Have we reached the end of a branch ? */
    if (currentNode == NULL) {
      *branch = newNode;
    } else {
/*    We have not reached the end of a branch */
      if (currentNode->data > newNode->data) {
        AddNode(&(currentNode->right),newNode);
      } else {
        AddNode(&(currentNode->left),newNode);
      }
    }
}

void PrintTree(struct treeNode *node)
{
/*  End of declarations ... */
    if (node != NULL) {
      PrintTree(node->left);
      printf("%d\n",node->data);
      PrintTree(node->right);
    }
}
