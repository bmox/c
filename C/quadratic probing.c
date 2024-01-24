// 7. To perform various operations i.e., insertion, deletion, searching using 
// quadratic probing hash functions.
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

int hashcode(int key) {
    return (key % max);
}

void init_array() {
    int i;
    array = (struct hashtable_item *)malloc(max * sizeof(struct hashtable_item));
    for (i = 0; i < max; i++) {
        array[i].flag = 0;
        array[i].data = NULL;
    }
}

void insert(int key, int value) {
    int index = hashcode(key);
    int i = index;
    int h = 1;

    struct item *new_item = (struct item *)malloc(sizeof(struct item));
    new_item->key = key;
    new_item->value = value;

    while (array[i].flag == 1) {
        if (array[i].data->key == key) {
            printf("\nThis key is already present in the hash table, hence updating its value\n");
            array[i].data->value = value;
            return;
        }
        i = (i + (h * h)) % max;
        h++;
        if (i == index) {
            printf("\nHash table is full, cannot add more elements\n");
            return;
        }
    }

    array[i].flag = 1;
    array[i].data = new_item;
    printf("\nKey (%d) has been inserted\n", key);
    size++;
}

void remove_element(int key) {
    int index = hashcode(key);
    int i = index;
    int h = 1;

    while (array[i].flag != 0) {
        if (array[i].flag == 1 && array[i].data->key == key) {
            array[i].flag = 2;
            free(array[i].data);
            array[i].data = NULL;
            size--;
            printf("\nKey (%d) has been removed\n", key);
            return;
        }
        i = (i + (h * h)) % max;
        h++;
        if (i == index) {
            break;
        }
    }
    printf("\nKey does not exist\n");
}

void display() {
    int i;
    for (i = 0; i < max; i++) {
        if (array[i].flag != 1) {
            printf("\nArray[%d] has no elements\n", i);
        } else {
            printf("\nArray[%d] has elements:\n%d (key) and %d (value)\n", i, array[i].data->key, array[i].data->value);
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
        printf("Implementation of Hash Table in C with Quadratic Probing\n\n");
        printf("MENU:\n1. Inserting item in the Hash table\n2. Removing item from the Hash table\n3. Check the size of Hash table\n4. Display Hash table\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Inserting element in Hash table\n");
                printf("Enter key and value: ");
                scanf("%d %d", &key, &value);
                insert(key, value);
                break;
            case 2:
                printf("Deleting in Hash table\nEnter the key to delete: ");
                scanf("%d", &key);
                remove_element(key);
                break;
            case 3:
                n = size_of_hashtable();
                printf("Size of Hash table is: %d\n", n);
                break;
            case 4:
                display();
                break;
            default:
                printf("Wrong Input\n");
        }

        printf("Do you want to continue? (Press 1 for yes): ");
        scanf("%d", &c);
    } while (c == 1);

    free(array);  // Free allocated memory before exiting

    return 0;
}
//Output:
// Implementation of Hash Table in C with Quadratic Probing

// MENU:
// 1. Inserting item in the Hash table
// 2. Removing item from the Hash table
// 3. Check the size of Hash table
// 4. Display Hash table
// Enter your choice: 1
// Inserting element in Hash table
// Enter key and value: 5 100
// Key (5) has been inserted
// Do you want to continue? (Press 1 for yes): 1
// Implementation of Hash Table in C with Quadratic Probing

// MENU:
// 1. Inserting item in the Hash table
// 2. Removing item from the Hash table
// 3. Check the size of Hash table
// 4. Display Hash table
// Enter your choice: 1
// Inserting element in Hash table
// Enter key and value: 15 200
// Key (15) has been inserted
// Do you want to continue? (Press 1 for yes): 1
// Implementation of Hash Table in C with Quadratic Probing

// MENU:
// 1. Inserting item in the Hash table
// 2. Removing item from the Hash table
// 3. Check the size of Hash table
// 4. Display Hash table
// Enter your choice: 1
// Inserting element in Hash table
// Enter key and value: 25 300
// Key (25) has been inserted
// Do you want to continue? (Press 1 for yes): 1
// Implementation of Hash Table in C with Quadratic Probing

// MENU:
// 1. Inserting item in the Hash table
// 2. Removing item from the Hash table
// 3. Check the size of Hash table
// 4. Display Hash table
// Enter your choice: 4
// Array[0] has elements:
// 25 (key) and 300 (value)

// Array[1] has no elements

// Array[2] has no elements

// Array[3] has no elements

// Array[4] has no elements

// Array[5] has elements:
// 5 (key) and 100 (value)

// Array[6] has elements:
// 15 (key) and 200 (value)

// Array[7] has no elements

// Array[8] has no elements

// Array[9] has no elements
// Do you want to continue? (Press 1 for yes): 1
// Implementation of Hash Table in C with Quadratic Probing

// MENU:
// 1. Inserting item in the Hash table
// 2. Removing item from the Hash table
// 3. Check the size of Hash table
// 4. Display Hash table
// Enter your choice: 2
// Deleting in Hash table
// Enter the key to delete: 5
// Key (5) has been removed
// Do you want to continue? (Press 1 for yes): 1
// Implementation of Hash Table in C with Quadratic Probing

// MENU:
// 1. Inserting item in the Hash table
// 2. Removing item from the Hash table
// 3. Check the size of Hash table
// 4. Display Hash table
// Enter your choice: 4
// Array[0] has elements:
// 25 (key) and 300 (value)

// Array[1] has no elements

// Array[2] has no elements

// Array[3] has no elements

// Array[4] has no elements

// Array[5] has no elements

// Array[6] has elements:
// 15 (key) and 200 (value)

// Array[7] has no elements

// Array[8] has no elements

// Array[9] has no elements
// Do you want to continue? (Press 1 for yes): 