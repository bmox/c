// 8. To create ADT that implements the SET concept. 
// a. Add (new Element) -Place a value into the set 
// b. Remove (element) Remove the value 
// c. Contains (element) Return true if element is in collection 
// d. Size () Return number of values in collection Iterator () Return an iterator 
// used to loop over collection 
// e. Intersection of two sets,
// f. Union of two sets,
// g. Difference between two sets, 
// h. Subset

#include <stdio.h>
#include <stdlib.h>

// Node structure for a set
struct Node {
    int data;
    struct Node* next;
};

// Set structure
struct Set {
    struct Node* head;
};

// Function to initialize an empty set
void initializeSet(struct Set* set) {
    set->head = NULL;
}

// Function to check if the set is empty
int isEmpty(struct Set* set) {
    return set->head == NULL;
}

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to add a new element to the set
void addElement(struct Set* set, int element) {
    if (!contains(set, element)) {
        struct Node* newNode = createNode(element);
        newNode->next = set->head;
        set->head = newNode;
    }
}

// Function to remove an element from the set
void removeElement(struct Set* set, int element) {
    struct Node* current = set->head;
    struct Node* prev = NULL;

    while (current != NULL && current->data != element) {
        prev = current;
        current = current->next;
    }

    if (current != NULL) {
        if (prev == NULL) {
            set->head = current->next;
        } else {
            prev->next = current->next;
        }

        free(current);
    }
}

// Function to check if an element is in the set
int contains(struct Set* set, int element) {
    struct Node* current = set->head;
    while (current != NULL) {
        if (current->data == element) {
            return 1; // Element found
        }
        current = current->next;
    }
    return 0; // Element not found
}

// Function to get the size of the set
int size(struct Set* set) {
    int count = 0;
    struct Node* current = set->head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

// Function to create an iterator for the set
struct Node* createIterator(struct Set* set) {
    return set->head;
}

// Function to get the next element using the iterator
int getNext(struct Node** iterator) {
    int data = (*iterator)->data;
    *iterator = (*iterator)->next;
    return data;
}

// Function to perform intersection of two sets
struct Set intersection(struct Set* set1, struct Set* set2) {
    struct Set result;
    initializeSet(&result);

    struct Node* iterator = set1->head;
    while (iterator != NULL) {
        if (contains(set2, iterator->data)) {
            addElement(&result, iterator->data);
        }
        iterator = iterator->next;
    }

    return result;
}

// Function to perform union of two sets
struct Set unionSet(struct Set* set1, struct Set* set2) {
    struct Set result;
    initializeSet(&result);

    struct Node* iterator1 = set1->head;
    struct Node* iterator2 = set2->head;

    while (iterator1 != NULL) {
        addElement(&result, iterator1->data);
        iterator1 = iterator1->next;
    }

    while (iterator2 != NULL) {
        addElement(&result, iterator2->data);
        iterator2 = iterator2->next;
    }

    return result;
}

// Function to perform difference between two sets
struct Set difference(struct Set* set1, struct Set* set2) {
    struct Set result;
    initializeSet(&result);

    struct Node* iterator = set1->head;
    while (iterator != NULL) {
        if (!contains(set2, iterator->data)) {
            addElement(&result, iterator->data);
        }
        iterator = iterator->next;
    }

    return result;
}

// Function to check if set1 is a subset of set2
int isSubset(struct Set* set1, struct Set* set2) {
    struct Node* iterator = set1->head;
    while (iterator != NULL) {
        if (!contains(set2, iterator->data)) {
            return 0; // Not a subset
        }
        iterator = iterator->next;
    }
    return 1; // Subset
}

// Function to display the elements of a set
void displaySet(struct Set* set) {
    struct Node* current = set->head;
    printf("{ ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("}\n");
}

// Main function for testing
int main() {
    struct Set set1, set2, resultSet;
    initializeSet(&set1);
    initializeSet(&set2);

    // Adding elements to set1
    addElement(&set1, 1);
    addElement(&set1, 2);
    addElement(&set1, 3);
    addElement(&set1, 4);

    // Adding elements to set2
    addElement(&set2, 3);
    addElement(&set2, 4);
    addElement(&set2, 5);
    addElement(&set2, 6);

    // Displaying set1 and set2
    printf("Set1: ");
    displaySet(&set1);

    printf("Set2: ");
    displaySet(&set2);

    // Testing set operations
    resultSet = intersection(&set1, &set2);
    printf("Intersection of set1 and set2: ");
    displaySet(&resultSet);

    resultSet = unionSet(&set1, &set2);
    printf("Union of set1 and set2: ");
    displaySet(&resultSet);

    resultSet = difference(&set1, &set2);
    printf("Difference of set1 and set2: ");
    displaySet(&resultSet);

    // Testing subset
    if (isSubset(&set1, &set2)) {
        printf("Set1 is a subset of set2.\n");
    } else {
        printf("Set1 is not a subset of set2.\n");
    }

    return 0;
}


//Output:
// Set1: { 4 3 2 1 }
// Set2: { 6 5 4 3 }
// Intersection of set1 and set2: { 3 4 }
// Union of set1 and set2: { 5 6 1 2 3 4 }
// Difference of set1 and set2: { 1 2 }
// Set1 is not a subset of set2.
