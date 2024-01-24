#include <stdio.h>
#include <stdlib.h>

// Node structure for Red-Black Tree
struct Node {
    int key;
    char color; // 'R' for red, 'B' for black
    struct Node* left;
    struct Node* right;
    struct Node* parent;
};

// Global variable for NIL node
struct Node* NIL;

// Function to create a new node
struct Node* createNode(int key) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->color = 'R'; // Newly inserted node is always red
    newNode->left = newNode->right = newNode->parent = NIL;
    return newNode;
}

// Function to perform left rotation
void leftRotate(struct Node** root, struct Node* x) {
    struct Node* y = x->right;
    x->right = y->left;

    if (y->left != NIL)
        y->left->parent = x;

    y->parent = x->parent;

    if (x->parent == NIL)
        *root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

// Function to perform right rotation
void rightRotate(struct Node** root, struct Node* y) {
    struct Node* x = y->left;
    y->left = x->right;

    if (x->right != NIL)
        x->right->parent = y;

    x->parent = y->parent;

    if (y->parent == NIL)
        *root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;

    x->right = y;
    y->parent = x;
}

// Function to fix the Red-Black Tree after insertion
void insertFixup(struct Node** root, struct Node* z) {
    while (z->parent->color == 'R') {
        if (z->parent == z->parent->parent->left) {
            struct Node* y = z->parent->parent->right;
            if (y->color == 'R') {
                z->parent->color = 'B';
                y->color = 'B';
                z->parent->parent->color = 'R';
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(root, z);
                }
                z->parent->color = 'B';
                z->parent->parent->color = 'R';
                rightRotate(root, z->parent->parent);
            }
        } else {
            struct Node* y = z->parent->parent->left;
            if (y->color == 'R') {
                z->parent->color = 'B';
                y->color = 'B';
                z->parent->parent->color = 'R';
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(root, z);
                }
                z->parent->color = 'B';
                z->parent->parent->color = 'R';
                leftRotate(root, z->parent->parent);
            }
        }
    }
    (*root)->color = 'B';
}

// Function to insert a key into the Red-Black Tree
void insert(struct Node** root, int key) {
    struct Node* z = createNode(key);
    struct Node* y = NIL;
    struct Node* x = *root;

    while (x != NIL) {
        y = x;
        if (z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;

    if (y == NIL)
        *root = z;
    else if (z->key < y->key)
        y->left = z;
    else
        y->right = z;

    insertFixup(root, z);
}

// Function to transplant a subtree
void transplant(struct Node** root, struct Node* u, struct Node* v) {
    if (u->parent == NIL)
        *root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;

    v->parent = u->parent;
}

// Function to find the minimum value node in a tree
struct Node* treeMinimum(struct Node* node) {
    while (node->left != NIL)
        node = node->left;
    return node;
}

// Function to fix the Red-Black Tree after deletion
void deleteFixup(struct Node** root, struct Node* x) {
    while (x != *root && x->color == 'B') {
        if (x == x->parent->left) {
            struct Node* w = x->parent->right;
            if (w->color == 'R') {
                w->color = 'B';
                x->parent->color = 'R';
                leftRotate(root, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == 'B' && w->right->color == 'B') {
                w->color = 'R';
                x = x->parent;
            } else {
                if (w->right->color == 'B') {
                    w->left->color = 'B';
                    w->color = 'R';
                    rightRotate(root, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = 'B';
                w->right->color = 'B';
                leftRotate(root, x->parent);
                x = *root;
            }
        } else {
            struct Node* w = x->parent->left;
            if (w->color == 'R') {
                w->color = 'B';
                x->parent->color = 'R';
                rightRotate(root, x->parent);
                w = x->parent->left;
            }
            if (w->right->color == 'B' && w->left->color == 'B') {
                w->color = 'R';
                x = x->parent;
            } else {
                if (w->left->color == 'B') {
                    w->right->color = 'B';
                    w->color = 'R';
                    leftRotate(root, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = 'B';
                w->left->color = 'B';
                rightRotate(root, x->parent);
                x = *root;
            }
        }
    }
    x->color = 'B';
}

// Function to delete a node from the Red-Black Tree
void deleteNode(struct Node** root, struct Node* z) {
    struct Node* y = z;
    struct Node* x;
    char yOriginalColor = y->color;

    if (z->left == NIL) {
        x = z->right;
        transplant(root, z, z->right);
    } else if (z->right == NIL) {
        x = z->left;
        transplant(root, z, z->left);
    } else {
        y = treeMinimum(z->right);
        yOriginalColor = y->color;
        x = y->right;
        if (y->parent == z)
            x->parent = y;
        else {
            transplant(root, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(root, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    free(z);

    if (yOriginalColor == 'B')
        deleteFixup(root, x);
}

// Function to perform an in-order traversal of the Red-Black Tree
void inorderTraversal(struct Node* root) {
    if (root != NIL) {
        inorderTraversal(root->left);
        printf("(%d, %c) ", root->key, root->color);
        inorderTraversal(root->right);
    }
}

// Main function for testing
int main() {
    NIL = (struct Node*)malloc(sizeof(struct Node));
    NIL->color = 'B';

    struct Node* root = NIL;

    // Insert keys into the Red-Black Tree
    insert(&root, 50);
    insert(&root, 30);
    insert(&root, 70);
    insert(&root, 20);
    insert(&root, 40);
    insert(&root, 60);
    insert(&root, 80);

    // Print the in-order traversal of the Red-Black Tree
    printf("In-order traversal: ");
    inorderTraversal(root);
    printf("\n");

    // Delete a key from the Red-Black Tree
    struct Node* nodeToDelete = root->left; // For example, delete the node with key 30
    if (nodeToDelete != NIL) {
        deleteNode(&root, nodeToDelete);
        printf("In-order traversal after deleting 30: ");
        inorderTraversal(root);
        printf("\n");
    }

    free(NIL);

    return 0;
}

//Output
// In-order traversal: (20, R) (30, B) (40, R) (50, B) (60, R) (70, B) (80, R) 
// In-order traversal after deleting 30: (20, R) (40, B) (50, B) (60, R) (70, B) (80, R) 
