#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void read_next(unsigned char **cursore, void *dest, int size) {
  memcpy(dest, *cursore, size);
  *cursore += size;
}

int main(int argc, char *argv[]) {

  unsigned char memory_dump[] = {
      0x23,                    // Magic Byte '#'
      0x0A, 0x00, 0x00, 0x00,  // ID: 10 (Little Endian)
      0x00, 0x00, 0x48, 0x42,  // Temp: 50.0 (float IEEE 754: 0x42480000) ->
                               // Little Endian? Attento!
      0x05,                    // Len: 5
      'H', 'E', 'L', 'L', 'O', // Msg: "HELLO"
      0x00, 0x00, 0x00, 0x00   // Checksum (vuoto per ora)
  };

  unsigned char *ptr = memory_dump;

  char magic_byte;
  read_next(&ptr, &magic_byte, sizeof(magic_byte));
  if (magic_byte != '#') {
    fprintf(stderr, "ERRORE FORMATO");
    exit(EXIT_FAILURE);
  }
  printf("[MAGIC] OK: %c\n", magic_byte);

  int id;
  read_next(&ptr, &id, sizeof(id));
  printf("[ID] APPARECCHIO: %d\n", id);

  float temp;
  read_next(&ptr, &temp, sizeof(temp));
  printf("[TEMP] RILEVATA: %f\n", temp);

  unsigned char msg_len;
  read_next(&ptr, &msg_len, sizeof(msg_len));

  char str[256]; // VLA (Variable Length Arrays) molto pericolosi, vulnerabilità
                 // molto alta
  read_next(&ptr, str, msg_len);
  str[msg_len] = '\0';
  printf("[MSG] MESSAGGIO (%d byte): %s\n", msg_len, str);

  float temp_patch = 100;
  memcpy(memory_dump + 5, &temp_patch, sizeof(temp_patch));
  printf("[PATCH] TEMPERATURA CORRETTA: %f\n", temp_patch);

  int check_sum = 0xBADC0DE;
  // CORREZIONE: Scriviamo DOVE PUNTA ptr, non SOPRA la variabile ptr!
  memcpy(ptr, &check_sum, sizeof(check_sum));
  printf("[PATCH] CHECK_SUM SCRITTO: %d\n", check_sum);
}