#ifndef AVL_H
#define AVL_H

#include "Patient.h"

typedef struct AVLNode {
    DatePtr key;
    PatientPtr value;
    struct AVLNode *left;
    struct AVLNode *right;
    int height;
} AVLNode;

typedef AVLNode* AVLNodePtr;

typedef struct AVLTree {
    int elements;
    AVLNodePtr root;
} AVLTree;

typedef AVLTree* AVLTreePtr;

AVLTreePtr AVLTree_Init();

void AVLNode_Close(AVLNodePtr node);

void AVLTree_Close(AVLTreePtr tree);

int max(int a, int b);

int AVLNode_getHeight(AVLNodePtr node);

int AVLNode_isBalanced(AVLNodePtr node);

AVLNodePtr AVLTree_RotateLeft(AVLNodePtr node);

AVLNodePtr AVLTree_RotateRight(AVLNodePtr node);

int AVLTree_Insert(AVLTreePtr tree, DatePtr key, const PatientPtr value);

AVLNodePtr AVLNode_Insert(AVLNodePtr node, DatePtr key, const PatientPtr value);

#endif