#include <stdio.h>
int numeri [5] = {10, 20, 30, 40, 50};

void classicPrint(int arr[], int size) {
    printf("classicPrint:\n");
    for (int i = 0; i < size; i++) {
        printf("numeri[%d] = %d\n", i, numeri[i]);
    }    
}

void aritmeticPointerPrint(int arr[], int size) {
    printf("aritmeticPointerFunction:\n");
    for(int i = 0; i < size; i++) {
        printf("numeri[%d] = %d\n", i, *(arr+i));
    }
}

void auxiliarPointer(int arr[], int size) {
    int *temp = arr;
    printf("auxiliarPointerFunction\n");
    for(int i = 0; i < size; i++){
        printf("numeri[%d] = %d\n", i, *temp);
         temp ++;
    }

}

int main() {
    classicPrint(numeri, 5);
    aritmeticPointerPrint(numeri, 5);
    auxiliarPointer(numeri, 5);
}