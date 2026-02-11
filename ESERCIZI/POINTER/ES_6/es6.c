#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int num = 0x12345678;
    char *p = (char*)&num;
    for(int i = 0; i < sizeof(num); i++){
        printf("byte[%d] di num : %x\n", i, (int)*p);
        p++;
    }
    
}


