#include <stdio.h>
#include <stdlib.h>

void printAddress(int arr[], int size){
    int *p = arr;
    for(int i = 0; i < size; i++){
        printf("indirizzo arr[%d] = %p\n", i, p);
        p++;
    }
}

int main(int argc, char *argv[]) {
    int arr[5];
    printAddress(arr, 5);
}

