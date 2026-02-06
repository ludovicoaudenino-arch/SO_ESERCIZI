#include <stdio.h>
#include <stdlib.h>

void stampa_valore(void *ptr, char tipo){
    switch (tipo) {
        case 'i':
            int *p_int = (int*)ptr;
            printf("Valore (int) : %d\n", *p_int);
            break;
        case 'f':
            float *p_float = (float*)ptr;
            printf("Valore (float) : %f\n", *p_float);
            break;
        case 'c':
            char *p_char = (char*)ptr;
            printf("Valore (char) : %c\n", *p_char);
            break;
    }
}

int main(int argc, char *argv[]) {
    int a = 42;
    float b = 3.14;
    char c = 'X';

    stampa_valore(&a, 'i');
    stampa_valore(&b, 'f');
    stampa_valore(&c, 'c');
    return 0;
}
