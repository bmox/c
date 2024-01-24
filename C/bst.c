#include <stdio.h>
#include <stdlib.h>

// Define the structure for a BST node
struct TreeNode {
    int key;
    struct TreeNode* left;
    struct TreeNode* right;
};

// Function to create a new node
struct TreeNode* createNode(int key) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->key = key;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to insert a key into the BST
struct TreeNode* insert(struct TreeNode* root, int key) {
    if (root == NULL) {
        return createNode(key);
    }

    if (key < root->key) {
        root->left = insert(root->left, key);
    } else if (key > root->key) {
        root->right = insert(root->right, key);
    }

    return root;
}

// Function to search for a key in the BST
struct TreeNode* search(struct TreeNode* root, int key) {
    if (root == NULL || root->key == key) {
        return root;
    }

    if (key < root->key) {
        return search(root->left, key);
    } else {
        return search(root->right, key);
    }
}

// Function to find the minimum value node in a BST
struct TreeNode* minValueNode(struct TreeNode* node) {
    struct TreeNode* current = node;

    // Find the leftmost leaf node
    while (current->left != NULL) {
        current = current->left;
    }

    return current;
}

// Function to delete a key from the BST
struct TreeNode* deleteNode(struct TreeNode* root, int key) {
    if (root == NULL) {
        return root;
    }

    if (key < root->key) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->key) {
        root->right = deleteNode(root->right, key);
    } else {
        // Node with only one child or no child
        if (root->left == NULL) {
            struct TreeNode* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct TreeNode* temp = root->left;
            free(root);
            return temp;
        }

        // Node with two children, get the inorder successor (smallest in the right subtree)
        struct TreeNode* temp = minValueNode(root->right);

        // Copy the inorder successor's key to this node
        root->key = temp->key;

        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->key);
    }

    return root;
}

// Function to perform an in-order traversal of the BST
void inorderTraversal(struct TreeNode* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->key);
        inorderTraversal(root->right);
    }
}

// Main function for testing
int main() {
    struct TreeNode* root = NULL;

    // Insert keys into the BST
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 20);
    insert(root, 40);
    insert(root, 70);
    insert(root, 60);
    insert(root, 80);

    // Print the in-order traversal of the BST
    printf("In-order traversal: ");
    inorderTraversal(root);
    printf("\n");

    // Search for a key in the BST
    int searchKey = 40;
    struct TreeNode* searchResult = search(root, searchKey);
    if (searchResult != NULL) {
        printf("%d found in the BST.\n", searchKey);
    } else {
        printf("%d not found in the BST.\n", searchKey);
    }

    // Delete a key from the BST
    int deleteKey = 30;
    root = deleteNode(root, deleteKey);
    printf("In-order traversal after deleting %d: ", deleteKey);
    inorderTraversal(root);
    printf("\n");

    return 0;
}
// Output:
// In-order traversal: 20 30 40 50 60 70 80 
// 40 found in the BST.
// In-order traversal after deleting 30: 20 40 50 60 70 80 

