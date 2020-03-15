#include <stdio.h>
#include <stdlib.h>

#include "../include/AVL.h"

AVLTreePtr AVLTree_Init()
{
    AVLTreePtr tree = NULL;

    if((tree = malloc(sizeof(AVLTree))) == NULL) {
        perror("malloc failed");
        return NULL;
    }

    tree->elements = 0;
    tree->root = NULL;

    return tree;
}

void AVLTree_Close(AVLTreePtr tree)
{
    AVLNode_Close(tree->root);

    free(tree);
}

void AVLNode_Close(AVLNodePtr node)
{
    if(node == NULL) {
        return;
    }

    AVLNode_Close(node->left);
    AVLNode_Close(node->right);

    List_Close(node->list, DF_PATIENT);
    free(node);
}

int max(const int a, const int b)
{
    return (a > b)? a : b;
}

int AVLNode_getHeight(const AVLNodePtr node)
{
    if (node == NULL) {
        return 0;
    }

    return node->height;
}

int AVLNode_isBalanced(const AVLNodePtr node)
{
    if(node == NULL) {
        return 0;
    }

    return AVLNode_getHeight(node->left) - AVLNode_getHeight(node->right);
}

AVLNodePtr AVLTree_RotateLeft(AVLNodePtr node)
{
    AVLNodePtr pr1 = node->right;
    AVLNodePtr pr2 = pr1->left;

    pr1->left = node;
    node->right = pr2;

    node->height = max(AVLNode_getHeight(node->left), AVLNode_getHeight(node->right)) + 1;
    pr1->height = max(AVLNode_getHeight(pr1->left), AVLNode_getHeight(pr1->right)) + 1;

    return pr1;
}

AVLNodePtr AVLTree_RotateRight(AVLNodePtr node)
{
    AVLNodePtr pr1 = node->left;
    AVLNodePtr pr2 = pr1->right;

    pr1->right = node;
    node->left = pr2;

    node->height = max(AVLNode_getHeight(node->left), AVLNode_getHeight(node->right)) + 1;
    pr1->height = max(AVLNode_getHeight(pr1->left), AVLNode_getHeight(pr1->right)) + 1;

    return pr1;
}

int AVLTree_Insert(AVLTreePtr tree, const DatePtr key, const PatientPtr value)
{
    if((tree->root = AVLNode_Insert(tree->root, key, value)) == NULL) {
        return -1;
    }

    tree->elements++;

    return 0;
}

AVLNodePtr AVLNode_Insert(AVLNodePtr node, const DatePtr key, const PatientPtr value)
{
    int isBalanced = 0;

    if(node == NULL) {
        AVLNodePtr newNode = NULL;

        if((newNode = malloc(sizeof(AVLNode))) == NULL) {
            perror("malloc failed");
            return NULL;
        }

        if((newNode->list = List_Init()) == NULL) {
            return NULL;
        }

        newNode->key = key;
        if(List_Insert(newNode->list, value) == -1) {
            free(node);
            return NULL;
        }
        newNode->height = 1;
        newNode->left = NULL;
        newNode->right = NULL;

        return newNode;
    }

    switch (Date_Compare(key, node->key)) {
        case -1:
            if((node->left = AVLNode_Insert(node->left, key, value))== NULL) {
                return NULL;
            }
            break;

        case 1:
            if((node->right = AVLNode_Insert(node->right, key, value)) == NULL) {
                return NULL;
            }
            break;

        default:
            if(List_Insert(node->list, value) == -1) {
                return NULL;
            }
            return node;
    }

    node->height = max(AVLNode_getHeight(node->left), AVLNode_getHeight(node->right)) + 1;

    isBalanced = AVLNode_isBalanced(node);

    if(isBalanced > 1) {
        switch(Date_Compare(key, node->left->key)) {
            case -1:
                return AVLTree_RotateRight(node);

            case 1:
                node->left = AVLTree_RotateLeft(node->left);
                return AVLTree_RotateRight(node);
        }
    }
    else if(isBalanced < -1) {
        switch(Date_Compare(key, node->right->key)) {
            case -1:
                node->right = AVLTree_RotateRight(node->right);
                return AVLTree_RotateLeft(node);

            case 1:
                return AVLTree_RotateLeft(node);
        }
    }

    return node;
}