#include <stdio.h>

int main() {
    int x = 42;
    int *p = NULL;
    p = &x;
    printf("Valore di x: %d\n", x);
    printf("Indirizzo di x: %p\n", &x);
    printf("Valore di p: %p\n", p);
    printf("Valore puntato da p: %d\n", *p);
    return 0;
}
