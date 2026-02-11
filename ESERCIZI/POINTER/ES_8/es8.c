#include <stdio.h>

int main() {
    
    // in questo caso viene solo inizializzata l'area di memoria che contiene l'indirizzo al puntore e non quella a cui punta il puntatore
    // int *p;
    // p = 10;
    
    int v;
    int *p = &v;
    *p = 10;

    int arr[5] = {1, 2, 3, 4, 5};
    int *q = arr;
    // si il fatto e che qui stiamo andando avanti di 10 posizioni ma l'array ne ha solo 5
    q = q + 4;
    printf("%d\n", *q);  
    
    int x = 100;
    int *r;
    // immagino che questo r = x renda l'indirizzo di r = 100 o qualcosa del genere in esadecimale
    r = &x; 
    printf("%d\n", *r);
    
    return 0;
}