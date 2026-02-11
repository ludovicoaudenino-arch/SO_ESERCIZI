# ☠️ Esercizio Finale: Il "Memory Walker" ☠️

**Difficoltà**: ⭐⭐⭐⭐⭐ (Hardcore)
**Argomenti**: Puntatori, Casting, Aritmetica, Endianness, Puntatori a Puntatori (`void **`)

---

## 📜 Scenario

Sei un ingegnere che sta analizzando un **dump di memoria** grezzo proveniente da un dispositivo IoT corrotto.
Il dump è rappresentato da un array di `unsigned char` (byte).
Non hai una `struct` per interpretarlo perché i dati sono impacchettati in modo "strano" per risparmiare spazio.

Devi scrivere un parser che "cammina" dentro questo array usando solo puntatori, decodifica i messaggi nascosti e corregge alcuni valori corrotti.

---

## 🎯 Obiettivi

1.  Creare una funzione che "cammina" nel buffer aggiornando la posizione corrente tramite un puntatore a puntatore.
2.  Estrarre diversi tipi di dati (`int`, `float`, `string`) da indirizzi arbitrari (non allineati).
3.  Modificare i dati direttamente in memoria.

---

## ⚙️ Specifica del Formato Dati

Il "pacchetto" di dati inizia sempre con un **Header** e contiene una sequenza di comandi.

| Offset (byte) | Tipo | Descrizione |
| :--- | :--- | :--- |
| `0x00` | `char` | Magic Byte: deve essere `'#'` (0x23). Se non lo è, errore. |
| `0x01` | `int` | ID del Pacchetto (4 byte). |
| `0x05` | `float` | Temperatura sensore (4 byte). |
| `0x09` | `char` | Lunghezza messaggio (N byte). |
| `0x0A` | `char[]` | Messaggio stringa (N caratteri, NON terminato da `\0`). |
| `0x0A + N` | `int` | Checksum finale (4 byte). |

**TOTALE BYTE**: 1 (magic) + 4 (id) + 4 (temp) + 1 (len) + N (msg) + 4 (crc).

---

## 🛠️ Consegna

Scrivi un programma unico `memory_walker.c` che fa quanto segue:

### 1. Preparazione del "Dump" (già fornito)
Copia questo array nel tuo `main`. Rappresenta la memoria corrotta da analizzare.
```c
unsigned char memory_dump[] = {
    0x23,             // Magic Byte '#'
    0x0A, 0x00, 0x00, 0x00, // ID: 10 (Little Endian)
    0x00, 0x00, 0x48, 0x42, // Temp: 50.0 (float IEEE 754: 0x42480000) -> Little Endian? Attento!
    0x05,             // Len: 5
    'H', 'E', 'L', 'L', 'O', // Msg: "HELLO"
    0x00, 0x00, 0x00, 0x00  // Checksum (vuoto per ora)
};
```
> **Nota**: Il float `50.0` in hex è `0x42480000`. Nel dump è scritto byte per byte. Dovrai capire se la tua macchina lo legge correttamente o se devi invertire i byte!

### 2. Funzione `read_next`
Scrivi una funzione generica che legge un dato e **avanza** automaticamente il puntatore corrente.

```c
// cursore: puntatore al puntatore che indica dove siamo arrivati nell'array
// dest: dove copiare il dato letto
// size: quanti byte leggere
void read_next(unsigned char **cursore, void *dest, int size);
```
Questa funzione deve:
1.  Copiare `size` byte dall'indirizzo puntato da `*cursore` a `dest`.
2.  Incrementare `*cursore` di `size` byte.

### 3. Logica nel Main

1.  Dichiara un puntatore `unsigned char *ptr = memory_dump;`.
2.  Usa `read_next` per leggere il **Magic Byte**. Se non è `'#'`, stampa "Errore Formato" ed esci.
3.  Usa `read_next` per leggere l'**ID**. Stampalo.
4.  Usa `read_next` per leggere la **Temperatura**. Stampala come `float`.
    *   *Sfida*: Se stampi `0.00` o valori strani, è colpa dell'endianness o del casting. Risolvilo!
5.  Usa `read_next` per leggere la **Lunghezza (N)**.
6.  Leggi N byte e stampali come stringa (ricorda di aggiungere `\0` alla fine per stamparla con `printf`, ma NON scriverlo nel dump originale!).
7.  **Patch**: Modifica la temperatura nel `memory_dump` originale portandola a `100.0` usando un puntatore.
8.  **Patch**: Scrivi il valore `0xBADC0DE` nel campo Checksum finale.

---

## 💡 Interrogativi Guida

1.  Perché dobbiamo passare `&ptr` alla funzione `read_next` (quindi un `unsigned char **`)?
2.  Come fai a castare i 4 byte della temperatura in un `float`? Basta `(float)valore` o serve `*(float*)&buffer`?
3.  Se modifichi `memory_dump` tramite un puntatore, la modifica è permanente?

---

### Output Atteso (Esempio)

```text
[Magic] OK: #
[ID] Apparecchio: 10
[Temp] Rilevata: 50.00 gradi
[Msg] Messaggio (5 byte): HELLO
[Patch] Temperatura corretta a 100.00!
[Patch] Checksum scritto: 195936478 (0xBADC0DE)
```

Buona fortuna. Qui serve precisione chirurgica con i puntatori. 🔪
