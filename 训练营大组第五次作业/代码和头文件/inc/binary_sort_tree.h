//
// Created by eke_l on 2021/4/21.
//

#ifndef BINARYSORTTREE_BINARY_SORT_TREE_H
#define BINARYSORTTREE_BINARY_SORT_TREE_H

#define true 1
#define false 0
#define succeed 1
#define failed 0
#define BST_status int

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int ElemType;

typedef struct Node {
    ElemType value;
    struct Node *left;
    struct Node *right;
} Node, *NodePtr;

typedef struct BinarySortTree {
    Node *root ;
} BinarySortTree, *BinarySortTreePtr;

/**
 * BST initialize
 * @param BinarySortTreePtr BST
 * @return is complete
 */
BST_status BST_init(BinarySortTreePtr BST,ElemType data);

/**
 * BST insert
 * @param BinarySortTreePtr BST
 * @param ElemType value to insert
 * @return is successful
 */
BST_status BST_insert(BinarySortTreePtr BST, ElemType data);

/**
 * BST search
 * @param BinarySortTreePtr BST
 * @param ElemType the value to search
 * @return is exist
 */
BST_status BST_search(BinarySortTreePtr BST, ElemType data);

/**
 * BST delete
 * @param BinarySortTreePtr BST
 * @param ElemType the value for Node which will be deleted
 * @return is successful
 */
BST_status BST_delete(BinarySortTreePtr BST, ElemType data);

/**
 * BST preorder traversal with recursion
 * @param BinarySortTreePtr BST
 * @param 
 * @return is successful
 */
BST_status BST_preorderR(NodePtr root);

/**
 * BST inorder traversal with recursion
 * @param BinarySortTreePtr BST
 * @param 
 * @return is successful
 */
BST_status BST_inorderR(NodePtr root);

/**
 * BST postorder traversal with recursion
 * @param BinarySortTreePtr BST
 * @param 
 * @return is successful
 */
BST_status BST_postorderR(NodePtr root);

/**
 * BST preorder traversal without recursion
 * @param BinarySortTreePtr BST
 * @param 
 * @return is successful
 */
BST_status BST_preorderI(BinarySortTreePtr BST);

/**
 * BST inorder traversal without recursion
 * @param BinarySortTreePtr BST
 * @param 
 * @return is successful
 */
BST_status BST_inorderI(BinarySortTreePtr BST);

/**
 * BST preorder traversal without recursion
 * @param BinarySortTreePtr BST
 * @param 
 * @return is successful
 */
BST_status BST_postorderI(BinarySortTreePtr BST);

/**
 * BST level order traversal
 * @param BinarySortTreePtr BST
 * @param 
 * @return is successful
 */
BST_status BST_levelOrder(BinarySortTreePtr BST);

#endif //BINARYSORTTREE_BINARY_SORT_TREE_H


