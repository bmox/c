// Program to construct a Binary Search Tree and perform insertion and 
// searching algorithm.

#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *leftChild, *rightChild;
};

struct node *root = NULL;

struct node *newNode(int item) {
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->data = item;
    temp->leftChild = temp->rightChild = NULL;
    return temp;
}

void insert(int data) {
    struct node *tempNode = newNode(data);
    struct node *current;
    struct node *parent;

    // If tree is empty
    if (root == NULL) {
        root = tempNode;
    } else {
        current = root;
        parent = NULL;
        while (1) {
            parent = current;

            // Go to left of the tree
            if (data < parent->data) {
                current = current->leftChild;

                // Insert to the left
                if (current == NULL) {
                    parent->leftChild = tempNode;
                    return;
                }
            } else {  // Go to right of the tree
                current = current->rightChild;

                // Insert to the right
                if (current == NULL) {
                    parent->rightChild = tempNode;
                    return;
                }
            }
        }
    }
}

struct node *search(int data) {
    struct node *current = root;
    printf("\nVisiting elements: ");
    while (current != NULL && current->data != data) {
        printf("%d ", current->data);

        // Go to left tree
        if (current->data > data) {
            current = current->leftChild;
        } else {  // Else go to right tree
            current = current->rightChild;
        }
    }

    if (current == NULL) {
        return NULL;  // Not found
    }

    return current;
}

void printTree(struct node *Node) {
    if (Node == NULL)
        return;
    printTree(Node->leftChild);
    printf(" --%d", Node->data);
    printTree(Node->rightChild);
}

int main() {
    insert(55);
    insert(20);
    insert(90);
    insert(50);
    insert(35);
    insert(15);
    insert(65);
    printf("Insertion done\n");
    printTree(root);
    struct node *k;
    k = search(35);
    if (k != NULL)
        printf("\nElement %d found", k->data);
    else
        printf("\nElement not found");
    return 0;
}

// Output:
// Insertion done
//  --15 --20 --35 --50 --55 --65 --90
// Visiting elements: 55 20 50 
// Element 35 found
