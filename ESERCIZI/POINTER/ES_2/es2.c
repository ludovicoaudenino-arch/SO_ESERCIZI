#include <stdio.h>

int main() {
    int x = 100;
    int *p = &x;
    *p += 50;
    *p *= 2;
    printf("x = %d\n", x);
}