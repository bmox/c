#include <stdio.h>
#include <stdlib.h>

// Define the structure for a AVL tree node
struct AVLNode {
    int key;
    struct AVLNode* left;
    struct AVLNode* right;
    int height;
};

// Function to get the height of a node
int getHeight(struct AVLNode* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

// Function to calculate the balance factor of a node
int getBalanceFactor(struct AVLNode* node) {
    if (node == NULL)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

// Function to create a new node
struct AVLNode* createNode(int key) {
    struct AVLNode* newNode = (struct AVLNode*)malloc(sizeof(struct AVLNode));
    newNode->key = key;
    newNode->left = newNode->right = NULL;
    newNode->height = 1;
    return newNode;
}

// Function to perform a right rotation
struct AVLNode* rightRotate(struct AVLNode* y) {
    struct AVLNode* x = y->left;
    struct AVLNode* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = 1 + fmax(getHeight(y->left), getHeight(y->right));
    x->height = 1 + fmax(getHeight(x->left), getHeight(x->right));

    return x;
}

// Function to perform a left rotation
struct AVLNode* leftRotate(struct AVLNode* x) {
    struct AVLNode* y = x->right;
    struct AVLNode* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = 1 + fmax(getHeight(x->left), getHeight(x->right));
    y->height = 1 + fmax(getHeight(y->left), getHeight(y->right));

    return y;
}

// Function to insert a key into the AVL tree
struct AVLNode* insert(struct AVLNode* root, int key) {
    // Perform standard BST insertion
    if (root == NULL)
        return createNode(key);

    if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);
    else // Duplicate keys are not allowed
        return root;

    // Update height of the current node
    root->height = 1 + fmax(getHeight(root->left), getHeight(root->right));

    // Get the balance factor and perform rotations if needed
    int balance = getBalanceFactor(root);

    // Left Left Case
    if (balance > 1 && key < root->left->key)
        return rightRotate(root);

    // Right Right Case
    if (balance < -1 && key > root->right->key)
        return leftRotate(root);

    // Left Right Case
    if (balance > 1 && key > root->left->key) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Left Case
    if (balance < -1 && key < root->right->key) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Function to find the node with the minimum value in a tree
struct AVLNode* minValueNode(struct AVLNode* node) {
    struct AVLNode* current = node;

    // Find the leftmost leaf node
    while (current->left != NULL)
        current = current->left;

    return current;
}

// Function to delete a key from the AVL tree
struct AVLNode* deleteNode(struct AVLNode* root, int key) {
    if (root == NULL)
        return root;

    // Perform standard BST delete
    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        // Node with only one child or no child
        if (root->left == NULL || root->right == NULL) {
            struct AVLNode* temp = root->left ? root->left : root->right;

            // No child case
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else // One child case
                *root = *temp; // Copy the contents of the non-empty child

            free(temp);
        } else {
            // Node with two children, get the inorder successor (smallest in the right subtree)
            struct AVLNode* temp = minValueNode(root->right);

            // Copy the inorder successor's key to this node
            root->key = temp->key;

            // Delete the inorder successor
            root->right = deleteNode(root->right, temp->key);
        }
    }

    // If the tree had only one node then return
    if (root == NULL)
        return root;

    // Update height of the current node
    root->height = 1 + fmax(getHeight(root->left), getHeight(root->right));

    // Get the balance factor and perform rotations if needed
    int balance = getBalanceFactor(root);

    // Left Left Case
    if (balance > 1 && getBalanceFactor(root->left) >= 0)
        return rightRotate(root);

    // Left Right Case
    if (balance > 1 && getBalanceFactor(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && getBalanceFactor(root->right) <= 0)
        return leftRotate(root);

    // Right Left Case
    if (balance < -1 && getBalanceFactor(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Function to perform an in-order traversal of the AVL tree
void inorderTraversal(struct AVLNode* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->key);
        inorderTraversal(root->right);
    }
}

// Main function for testing
int main() {
    struct AVLNode* root = NULL;

    // Insert keys into the AVL tree
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 70);
    root = insert(root, 60);
    root = insert(root, 80);

    // Print the in-order traversal of the AVL tree
    printf("In-order traversal: ");
    inorderTraversal(root);
    printf("\n");

    // Delete a key from the AVL tree
    int deleteKey = 30;
    printf("Deleting %d \n",deleteKey);
    root = deleteNode(root, deleteKey);
    printf("After Delete : ");
    inorderTraversal(root);
    printf("\n");
}
// Output:
// In-order traversal: 20 30 40 50 60 70 80 
// Deleting 30 
// After Delete : 20 40 50 60 70 80 
