#ifndef AVL_H
#define AVL_H

#include "Patient.h"

typedef struct AVLNode {
    int height;
    DatePtr key;
    PatientPtr value;
    struct AVLNode *left;
    struct AVLNode *right;
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

int max(const int a, const int b);

int AVLNode_getHeight(const AVLNodePtr node);

int AVLNode_isBalanced(const AVLNodePtr node);

AVLNodePtr AVLTree_RotateLeft(AVLNodePtr node);

AVLNodePtr AVLTree_RotateRight(AVLNodePtr node);

int AVLTree_Insert(AVLTreePtr tree, const DatePtr key, const PatientPtr value);

AVLNodePtr AVLNode_Insert(AVLNodePtr node, const DatePtr key, const PatientPtr value);

#endif