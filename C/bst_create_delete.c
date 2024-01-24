// 2. Program to construct a Binary Search Tree and perform deletion and
// inorder traversal algorithm
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Represent a node of the binary tree
struct node {
    int data;
    struct node *left;
    struct node *right;
};

// Represent the root of the binary tree
struct node *root = NULL;

// createNode() will create a new node
struct node* createNode(int data) {
    // Create a new node
    struct node *newNode = (struct node*)malloc(sizeof(struct node));
    // Assign data to newNode, set left and right children to NULL
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

// insert() will add a new node to the binary search tree
void insert(int data) {
    // Create a new node
    struct node *newNode = createNode(data);

    // Check whether the tree is empty
    if (root == NULL) {
        root = newNode;
        return;
    } else {
        // Current node points to the root of the tree
        struct node *current = root, *parent = NULL;

        while (true) {
            // Parent keeps track of the parent node of the current node
            parent = current;

            // If data is less than the current's data, the node will be inserted to the left of the tree
            if (data < current->data) {
                current = current->left;
                if (current == NULL) {
                    parent->left = newNode;
                    return;
                }
            }
            // If data is greater than the current's data, the node will be inserted to the right of the tree
            else {
                current = current->right;
                if (current == NULL) {
                    parent->right = newNode;
                    return;
                }
            }
        }
    }
}

// minNode() will find out the minimum node
struct node* minNode(struct node *root) {
    if (root->left != NULL)
        return minNode(root->left);
    else
        return root;
}

// deleteNode() will delete the given node from the binary search tree
struct node* deleteNode(struct node *node, int value) {
    if (node == NULL) {
        return NULL;
    } else {
        // Value is less than node's data then search the value in the left subtree
        if (value < node->data)
            node->left = deleteNode(node->left, value);
        // Value is greater than node's data then search the value in the right subtree
        else if (value > node->data)
            node->right = deleteNode(node->right, value);
        // If value is equal to node's data, we have found the node to be deleted
        else {
            // If the node to be deleted has no child, set the node to NULL
            if (node->left == NULL && node->right == NULL)
                node = NULL;
            // If the node to be deleted has only one right child
            else if (node->left == NULL) {
                struct node *temp = node;
                node = node->right;
                free(temp);
            }
            // If the node to be deleted has only one left child
            else if (node->right == NULL) {
                struct node *temp = node;
                node = node->left;
                free(temp);
            }
            // If the node to be deleted has two children nodes
            else {
                // Find the minimum node from the right subtree
                struct node *temp = minNode(node->right);
                // Exchange the data between node and temp
                node->data = temp->data;
                // Delete the duplicate node from the right subtree
                node->right = deleteNode(node->right, temp->data);
            }
        }
    }
    return node;
}

// inorderTraversal() will perform an inorder traversal on the binary search tree
void inorderTraversal(struct node *node) {
    // Check whether the tree is empty
    if (root == NULL) {
        printf("Tree is empty\n");
        return;
    } else {
        if (node->left != NULL)
            inorderTraversal(node->left);
        printf("%d ", node->data);
        if (node->right != NULL)
            inorderTraversal(node->right);
    }
}

int main() {
    // Add nodes to the binary tree
    insert(50);
    insert(30);
    insert(70);
    insert(60);
    insert(10);
    insert(90);

    printf("Binary search tree after insertion: \n");
    // Display the binary tree
    inorderTraversal(root);

    struct node *deletedNode = NULL;

    // Deletes node 90 which has no child
    root = deleteNode(root, 90);
    printf("\nBinary search tree after deleting node 90: \n");
    inorderTraversal(root);

    // Deletes node 30 which has one child
    root = deleteNode(root, 30);
    printf("\nBinary search tree after deleting node 30: \n");
    inorderTraversal(root);

    // Deletes node 50 which has two children
    root = deleteNode(root, 50);
    printf("\nBinary search tree after deleting node 50: \n");
    inorderTraversal(root);

    return 0;
}

// Output
// Binary search tree after insertion: 
// 10 30 50 60 70 90 
// Binary search tree after deleting node 90: 
// 10 30 50 60 70 
// Binary search tree after deleting node 30: 
// 10 50 60 70 
// Binary search tree after deleting node 50: 
// 10 60 70
