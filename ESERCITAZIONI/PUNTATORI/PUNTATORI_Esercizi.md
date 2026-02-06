# 🎯 Esercizi: Puntatori e Gestione della Memoria

**Riferimento**: `LEZIONI/POINTER_LESSON.md`  
**Difficoltà**: ⭐ (facile) → ⭐⭐⭐ (avanzato)

---

## 📋 Istruzioni Generali

- Compila sempre con: `gcc -g -O0 -Wall file.c -o output`
- Usa GDB per debuggare se incontri errori
- Ogni esercizio ha un obiettivo specifico: leggilo attentamente prima di iniziare

---

## Esercizio 1 - Dichiarazione e Assegnazione Base ⭐

### Obiettivo 1

Comprendere la differenza tra dichiarare un puntatore e dichiarare una variabile normale.

### Consegna 1

Scrivi un programma che:

1. Dichiara una variabile intera `x` e la inizializza a `42`
2. Dichiara un puntatore a intero `ptr`
3. Assegna a `ptr` l'indirizzo di `x`
4. Stampa:
   - Il valore di `x`
   - L'indirizzo di `x` (usando `%p`)
   - Il valore contenuto in `ptr` (l'indirizzo)
   - Il valore puntato da `ptr` (dereferenziazione)

### Output Atteso 1 (esempio)

```text
Valore di x: 42
Indirizzo di x: 0x7ffd12345678
Valore di ptr: 0x7ffd12345678
Valore puntato da ptr: 42
```

### Hint 1

> Ricorda la differenza tra `ptr` (l'indirizzo memorizzato) e `*ptr` (il valore a quell'indirizzo).

---

## Esercizio 2 - Modifica Tramite Puntatore ⭐

### Obiettivo 2

Capire come modificare una variabile attraverso un puntatore.

### Consegna 2

Scrivi un programma che:

1. Dichiara una variabile `valore` inizializzata a `100`
2. Dichiara un puntatore che punta a `valore`
3. **Senza toccare direttamente `valore`**, usa il puntatore per:
   - Aggiungere `50` al valore
   - Moltiplicare il risultato per `2`
4. Stampa il valore finale di `valore`

### Output Atteso 2

```text
Valore finale: 300
```

### Hint 2

> Usa l'operatore di dereferenziazione `*` sul lato sinistro dell'assegnamento.

---

## Esercizio 3 - Puntatori e Funzioni: Swap ⭐⭐

### Obiettivo 3

Implementare una funzione che scambia due valori usando i puntatori.

### Consegna 3

1. Scrivi una funzione `void scambia(int *a, int *b)` che scambia i valori delle due variabili puntate
2. Nel `main`:
   - Dichiara due variabili `x = 10` e `y = 20`
   - Stampa i valori prima dello scambio
   - Chiama `scambia(&x, &y)`
   - Stampa i valori dopo lo scambio

### Output Atteso 3

```text
Prima: x = 10, y = 20
Dopo:  x = 20, y = 10
```

### Hint 3

> Avrai bisogno di una variabile temporanea all'interno della funzione.

---

## Esercizio 4 - Array e Puntatori: Equivalenza ⭐⭐

### Obiettivo 4

Dimostrare la relazione tra array e puntatori.

### Consegna 4

Dato l'array:

```c
int numeri[5] = {10, 20, 30, 40, 50};
```

Scrivi un programma che stampa **tutti gli elementi** dell'array usando **tre metodi diversi**:

1. Notazione classica con indice: `numeri[i]`
2. Aritmetica dei puntatori con dereferenziazione: `*(numeri + i)`
3. Un puntatore ausiliario che scorre l'array

### Output Atteso 4

```text
Metodo 1 (indice):     10 20 30 40 50
Metodo 2 (aritmetica): 10 20 30 40 50
Metodo 3 (puntatore):  10 20 30 40 50
```

### Hint 4

> Per il metodo 3, inizializza un puntatore `int *p = numeri` e usa `p++` nel loop.

---

## Esercizio 5 - Aritmetica dei Puntatori: Calcolo Indirizzi ⭐⭐

### Obiettivo 5

Comprendere come l'aritmetica dei puntatori scala automaticamente in base al tipo.

### Consegna 5

Scrivi un programma che:

1. Dichiara un array `int arr[5]`
2. Dichiara un puntatore `int *p = arr`
3. Stampa l'indirizzo di `p`, `p+1`, `p+2`, `p+3`, `p+4`
4. Calcola e stampa la differenza in byte tra indirizzi consecutivi

### Domanda 5

Perché la differenza tra `p` e `p+1` non è 1, ma 4 (su sistemi a 32-bit per int)?

### Output Atteso 5 (esempio)

```text
p+0: 0x7ffd00001000
p+1: 0x7ffd00001004
p+2: 0x7ffd00001008
p+3: 0x7ffd0000100c
p+4: 0x7ffd00001010
Differenza tra indirizzi consecutivi: 4 byte
```

### Hint 5

> Per calcolare la differenza in byte, puoi castare a `char*` oppure usare la formula della lezione.

---

## Esercizio 6 - Casting di Puntatori: Esplorazione Byte ⭐⭐⭐

### Obiettivo 6

Visualizzare la rappresentazione interna di un intero byte per byte.

### Consegna 6

Scrivi un programma che:

1. Dichiara una variabile `int num = 0x12345678`
2. Usa un puntatore a `char` per accedere ai singoli byte
3. Stampa ogni byte in esadecimale

### Domanda Bonus 6

L'output del tuo sistema è `12 34 56 78` o `78 56 34 12`? Cosa indica questo sul **byte order** (endianness) della tua macchina?

### Output Atteso 6 (dipende dall'architettura)

```text
Byte 0: 0x78
Byte 1: 0x56
Byte 2: 0x34
Byte 3: 0x12
(Sistema Little-Endian)
```

### Hint 6

> Ricorda che `char *` legge un byte alla volta. Usa un loop per scorrere i byte.

---

## Esercizio 7 - Puntatori Generici (void *) ⭐⭐⭐

### Obiettivo 7

Comprendere l'uso di `void *` e la necessità del casting.

### Consegna 7

Scrivi una funzione `void stampa_valore(void *ptr, char tipo)` che:

- Riceve un puntatore generico e un carattere che indica il tipo (`'i'` per int, `'f'` per float, `'c'` per char)
- Casta il puntatore al tipo appropriato e stampa il valore

Nel main, testa la funzione con:

```c
int a = 42;
float b = 3.14;
char c = 'X';

stampa_valore(&a, 'i');
stampa_valore(&b, 'f');
stampa_valore(&c, 'c');
```

### Output Atteso 7

```text
Valore (int): 42
Valore (float): 3.14
Valore (char): X
```

### Hint 7

> All'interno della funzione, usa uno `switch` sul parametro `tipo` e casta `ptr` di conseguenza.

---

## Esercizio 8 - Debug: Trova il Segmentation Fault ⭐⭐⭐

### Obiettivo 8

Identificare e correggere errori comuni con i puntatori.

### Consegna 8

Il seguente codice contiene **3 errori** che possono causare Segmentation Fault o comportamento indefinito. Trovili e correggi:

```c
#include <stdio.h>

int main() {
    int *p;
    *p = 10;  // Linea 5
    
    int arr[5] = {1, 2, 3, 4, 5};
    int *q = arr;
    q = q + 10;
    printf("%d\n", *q);  // Linea 10
    
    int x = 100;
    int *r;
    r = x;  // Linea 14
    printf("%d\n", *r);
    
    return 0;
}
```

### Compito 8

1. Compila con `-Wall` e osserva i warning
2. Esegui con GDB e identifica dove crashi
3. Descrivi ogni errore e la correzione

### Hint 8

> Pensa a: puntatori non inizializzati, accessi fuori limite, e tipi incompatibili.

---

## 📊 Riepilogo Argomenti

| Esercizio | Argomenti Coperti                         |
| --------- | ----------------------------------------- |
| 1         | Dichiarazione, `&`, `*`, stampa indirizzi |
| 2         | Modifica tramite dereferenziazione        |
| 3         | Passaggio per riferimento alle funzioni   |
| 4         | Equivalenza array/puntatori               |
| 5         | Aritmetica dei puntatori                  |
| 6         | Casting, endianness                       |
| 7         | `void *`, casting tipi                    |
| 8         | Debug errori comuni                       |

---

## Buono Studio

Ricorda: i puntatori vanno praticati, non solo letti! 🚀
