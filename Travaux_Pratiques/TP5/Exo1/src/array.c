#include <stdlib.h>
#include <stdio.h>
#include "include/array.h"

/* 
 * Allocate memory for an array which can contain `size`
 * integers. The returned C array has memory for an extra last
 * integer labelling the end of the array. 
*/
int* allocate_integer_array(int size){
    int* new_tab;

    new_tab = (int*)malloc((size+1)*sizeof(int));
    if (new_tab == NULL){
        fprintf(stderr, "Memory allocation error\n");
        return NULL;
    }
    return new_tab;
}

/* Free an integer array */
void free_integer_array(int* tab){
    free(tab);
}

int array_size(int* array) {
    int i = 0;
    while (*(array+i) != -1){
        i++;
    }
    return i;
}

void print_array(int* array) {
    int i = 0;
    while (*(array+i) != -1){
        printf("%d ", *(array+i));
        i++;
    }
    printf("\n");
}

int are_arrays_equal(int* first, int* second) {
    int i = 0;
    int first_length, second_length;
    first_length = array_size(first);
    second_length = array_size(second);

    if (first_length != second_length) {
        return 0;
    }
    
    while (*(first + i) != -1) {
        if (*(first + i) != *(second + i)) {
            return 0;
        }
    }

    return 1;
}

int* copy_array(int* array) {
    int i = 0;
    int* new_array;
    new_array = allocate_integer_array(array_size(array));
    while (*(array+i) != -1){
        *(new_array+i) = *(array+i);
        i++;
    }
    return new_array;
}

int* fill_array() {
    int* array;
    int i = 0;
    int n;
    printf("Enter the size of the array: ");
    scanf("%d", &n);
    array = allocate_integer_array(n);
    printf("Enter the elements of the array: ");
    while (i < n) {
        scanf("%d", array+i);
        i++;
    }
    return array;
}

int* random_array(int size, int max_value) {
    int* array;
    int i = 0;
    array = allocate_integer_array(size);
    while (i < size) {
        *(array+i) = rand() % max_value;
        i++;
    }
    return array;
}

int* concatenate_arrays(int* first, int* second) {
    int* new_array;
    int i = 0;
    int j = 0;
    int first_length, second_length;
    first_length = array_size(first);
    second_length = array_size(second);
    new_array = allocate_integer_array(first_length + second_length);
    while (*(first+i) != -1) {
        *(new_array+i) = *(first+i);
        i++;
    }
    while (*(second+j) != -1) {
        *(new_array+i+j) = *(second+j);
        j++;
    }
    return new_array;
}

int* merge_sorted_arrays(int* first, int* second) {
    int* new_array;
    int i = 0;
    int j = 0;
    int first_length, second_length;
    first_length = array_size(first);
    second_length = array_size(second);
    new_array = allocate_integer_array(first_length + second_length);
    while (*(first+i) != -1 && *(second+j) != -1) {
        if (*(first+i) < *(second+j)) {
            *(new_array+i) = *(first+i);
            i++;
        } else {
            *(new_array+i) = *(second+j);
            j++;
        }
    }
    while (*(first+i) != -1) {
        *(new_array+i) = *(first+i);
        i++;
    }
    while (*(second+j) != -1) {
        *(new_array+i+j) = *(second+j);
        j++;
    }
    return new_array;
}

void split_arrays(int* array, int** first, int** second) {
    int i = 0;
    int j = 0;
    int array_length;
    array_length = array_size(array);
    *first = allocate_integer_array(array_length/2);
    *second = allocate_integer_array(array_length/2);
    while (*(array+i) != -1) {
        if (i < array_length/2) {
            *(*first+i) = *(array+i);
        } else {
            *(*second+j) = *(array+i);
            j++;
        }
        i++;
    }
}

int* merge_sort(int* array) {
    int* first;
    int* second;
    int* new_array;
    int array_length;

    array_length = array_size(array);
    if (array_length <= 1) {
        return array;
    }
    
    split_arrays(array, &first, &second);
    first = merge_sort(first);
    second = merge_sort(second);
    new_array = merge_sorted_arrays(first, second);
    free_integer_array(first);
    free_integer_array(second);
    return new_array;
}
