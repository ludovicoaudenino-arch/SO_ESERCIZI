#include <stdio.h>
#include <string.h>

void read_next(unsigned char **cursore, void *dest, int size){
    memcpy(dest, *cursore, size);
    *cursore+=size;
}

int main(int argc, char *argv[]) {

    unsigned char memory_dump[] = {
    0x23,             // Magic Byte '#'
    0x0A, 0x00, 0x00, 0x00, // ID: 10 (Little Endian)
    0x00, 0x00, 0x48, 0x42, // Temp: 50.0 (float IEEE 754: 0x42480000) -> Little Endian? Attento!
    0x05,             // Len: 5
    'H', 'E', 'L', 'L', 'O', // Msg: "HELLO"
    0x00, 0x00, 0x00, 0x00  // Checksum (vuoto per ora)
};

    unsigned char *ptr = memory_dump;
    read_next(unsigned char **cursore, void *dest, int size)



}