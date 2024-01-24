
// 6. To perform various operations i.e., insertion, deletion, searching using 
// linear probing .
#include <stdio.h>
#include <stdlib.h>

struct item {
    int key;
    int value;
};

struct hashtable_item {
    int flag;  // 0: data does not exist, 1: data exists, 2: data existed at least once
    struct item *data;
};

struct hashtable_item *array;
int size = 0;
int max = 10;

void init_array() {
    int i;
    array = (struct hashtable_item *)malloc(max * sizeof(struct hashtable_item));
    for (i = 0; i < max; i++) {
        array[i].flag = 0;
        array[i].data = NULL;
    }
}

int hashcode(int key) {
    return (key % max);
}

void insert(int key, int value) {
    int index = hashcode(key);
    int i = index;
    
    struct item *new_item = (struct item *)malloc(sizeof(struct item));
    new_item->key = key;
    new_item->value = value;

    while (array[i].flag == 1) {
        if (array[i].data->key == key) {
            printf("\n Key already exists, updating its value \n");
            array[i].data->value = value;
            return;
        }
        i = (i + 1) % max;
        if (i == index) {
            printf("\n Hash table is full, cannot insert any more items \n");
            return;
        }
    }

    array[i].flag = 1;
    array[i].data = new_item;
    size++;
    printf("\n Key (%d) has been inserted \n", key);
}

void remove_element(int key) {
    int index = hashcode(key);
    int i = index;
    
    while (array[i].flag != 0) {
        if (array[i].flag == 1 && array[i].data->key == key) {
            array[i].flag = 2;
            free(array[i].data);
            size--;
            printf("\n Key (%d) has been removed \n", key);
            return;
        }
        i = (i + 1) % max;
        if (i == index) {
            break;
        }
    }

    printf("\n This key does not exist \n");
}

void display() {
    int i;
    for (i = 0; i < max; i++) {
        struct item *current = array[i].data;
        if (current == NULL) {
            printf("\n Array[%d] has no elements \n", i);
        } else {
            printf("\n Array[%d] has elements - key: %d, value: %d \n", i, current->key, current->value);
        }
    }
}

int size_of_hashtable() {
    return size;
}

int main() {
    int choice, key, value, n, c;
    init_array();
    
    do {
        printf("Implementation of Hash Table in C with Linear Probing \n\n");
        printf("MENU-: \n1. Insert item in the Hashtable\n2. Remove item from the Hashtable\n3. Check the size of Hashtable\n4. Display Hashtable\n5. Exit\n");
        printf("\nPlease enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Inserting element in Hashtable\n");
                printf("Enter key and value: ");
                scanf("%d %d", &key, &value);
                insert(key, value);
                break;
            case 2:
                printf("Deleting in Hashtable \nEnter the key to delete: ");
                scanf("%d", &key);
                remove_element(key);
                break;
            case 3:
                n = size_of_hashtable();
                printf("Size of Hashtable is: %d\n", n);
                break;
            case 4:
                display();
                break;
            case 5:
                exit(0);
            default:
                printf("Wrong Input\n");
        }

        printf("\nDo you want to continue? (press 1 for yes): ");
        scanf("%d", &c);
    } while (c == 1);

    return 0;
}

// Output:
// Implementation of Hash Table in C with Linear Probing 

// MENU-: 
// 1. Insert item in the Hashtable
// 2. Remove item from the Hashtable
// 3. Check the size of Hashtable
// 4. Display Hashtable
// 5. Exit

// Please enter your choice: 1
// Inserting element in Hashtable
// Enter key and value: 10 100
// Key (10) has been inserted 

// Do you want to continue? (press 1 for yes): 1
// Implementation of Hash Table in C with Linear Probing 

// MENU-: 
// 1. Insert item in the Hashtable
// 2. Remove item from the Hashtable
// 3. Check the size of Hashtable
// 4. Display Hashtable
// 5. Exit

// Please enter your choice: 1
// Inserting element in Hashtable
// Enter key and value: 20 200
// Key (20) has been inserted 

// Do you want to continue? (press 1 for yes): 1
// Implementation of Hash Table in C with Linear Probing 

// MENU-: 
// 1. Insert item in the Hashtable
// 2. Remove item from the Hashtable
// 3. Check the size of Hashtable
// 4. Display Hashtable
// 5. Exit

// Please enter your choice: 1
// Inserting element in Hashtable
// Enter key and value: 15 150
// Key (15) has been inserted 

// Do you want to continue? (press 1 for yes): 1
// Implementation of Hash Table in C with Linear Probing 

// MENU-: 
// 1. Insert item in the Hashtable
// 2. Remove item from the Hashtable
// 3. Check the size of Hashtable
// 4. Display Hashtable
// 5. Exit

// Please enter your choice: 4
// Array[0] has elements - key: 10, value: 100 

//  Array[1] has elements - key: 20, value: 200 

//  Array[2] has no elements 

//  Array[3] has no elements 

//  Array[4] has no elements 

//  Array[5] has elements - key: 15, value: 150 

//  Array[6] has no elements 

//  Array[7] has no elements 

//  Array[8] has no elements 

//  Array[9] has no elements 

// Do you want to continue? (press 1 for yes): 1
// Implementation of Hash Table in C with Linear Probing 

// MENU-: 
// 1. Insert item in the Hashtable
// 2. Remove item from the Hashtable
// 3. Check the size of Hashtable
// 4. Display Hashtable
// 5. Exit

// Please enter your choice: 2
// Deleting in Hashtable 
// Enter the key to delete: 15
// Key (15) has been removed 
// 1

// Do you want to continue? (press 1 for yes): 1
// Implementation of Hash Table in C with Linear Probing 

// MENU-: 
// 1. Insert item in the Hashtable
// 2. Remove item from the Hashtable
// 3. Check the size of Hashtable
// 4. Display Hashtable
// 5. Exit

// Please enter your choice: 4
// Array[0] has elements - key: 10, value: 100 

//  Array[1] has elements - key: 20, value: 200 

//  Array[2] has no elements 

//  Array[3] has no elements 

//  Array[4] has no elements 

//  Array[5] has elements - key: 0, value: 0 

//  Array[6] has no elements 

//  Array[7] has no elements 

//  Array[8] has no elements 

//  Array[9] has no elements 

// Do you want to continue? (press 1 for yes): 
