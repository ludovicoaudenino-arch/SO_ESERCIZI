# 🔍 Esercitazione GDB - Debugging con GNU Debugger

**Argomento**: Debugging in ambiente Unix/Linux  
**Prerequisiti**: Conoscenza base di C, compilazione con gcc, nozioni di puntatori

---

## Esercizio 1: Compilazione per il Debug

### Obiettivo
Comprendere l'importanza delle opzioni di compilazione per il debugging.

### Consegna
Hai il seguente programma `somma.c`:

```c
#include <stdio.h>

int somma(int a, int b) {
    int risultato = a + b;
    return risultato;
}

int main() {
    int x = 5;
    int y = 10;
    int tot = somma(x, y);
    printf("La somma è: %d\n", tot);
    return 0;
}
```

**Compiti:**
1. Compila il programma in modo che sia **pronto per il debug** con GDB
2. Spiega cosa fanno i flag che hai usato e perché sono necessari
3. Verifica che il programma venga eseguito correttamente

### Hint
- I flag di compilazione per il debug sono due
- Uno riguarda i simboli, l'altro le ottimizzazioni

---

## Esercizio 2: Primi Passi con GDB

### Obiettivo
Familiarizzare con i comandi base di GDB: avvio, breakpoint e ispezione.

### Consegna
Usando il programma compilato nell'esercizio 1:

1. Avvia GDB con l'eseguibile
2. Visualizza il codice sorgente
3. Inserisci un breakpoint alla riga della chiamata a `somma()`
4. Esegui il programma fino al breakpoint
5. Stampa il valore delle variabili `x` e `y`
6. Prosegui l'esecuzione e verifica l'output

**Domanda**: Quali comandi hai usato per ogni passaggio?

---

## Esercizio 3: Stepping nel Codice

### Obiettivo
Capire la differenza tra `next` e `step` durante il debugging.

### Consegna
Sempre con `somma.c`:

1. Metti un breakpoint sulla riga `int tot = somma(x, y);`
2. Usa il comando `step` per entrare dentro la funzione `somma()`
3. Ispeziona i parametri `a` e `b` 
4. Usa `next` per avanzare riga per riga dentro la funzione
5. Ispeziona la variabile `risultato` dopo l'assegnazione

**Domanda**: Cosa sarebbe successo se avessi usato `next` invece di `step` al punto 2?

---

## Esercizio 4: Trovare un Segmentation Fault 🔴

### Obiettivo
Usare GDB per individuare la causa di un crash.

### Consegna
Scrivi, compila ed esegui questo programma `crash.c`:

```c
#include <stdio.h>

void funzione_pericolosa(int *p) {
    *p = 42;
}

int main() {
    int *ptr = NULL;
    funzione_pericolosa(ptr);
    printf("Valore: %d\n", *ptr);
    return 0;
}
```

**Compiti:**
1. Compila con i flag di debug ed esegui. Cosa succede?
2. Avvia il programma con GDB e usa `run`
3. Quando il programma crasha, usa il comando appropriato per vedere lo **stack delle chiamate**
4. Identifica la riga esatta che ha causato il crash
5. Spiega perché è avvenuto il crash

### Hint
- Il comando per vedere lo stack è molto breve (2 lettere)

---

## Esercizio 5: Monitoraggio Variabili

### Obiettivo
Usare `print` e `display` per monitorare i valori durante l'esecuzione.

### Consegna
Scrivi il programma `contatore.c`:

```c
#include <stdio.h>

int main() {
    int contatore = 0;
    for (int i = 0; i < 5; i++) {
        contatore += i;
        printf("Iterazione %d\n", i);
    }
    printf("Totale: %d\n", contatore);
    return 0;
}
```

**Compiti:**
1. Compila con flag di debug
2. Metti un breakpoint dentro il ciclo `for`
3. Imposta `display` su entrambe le variabili `i` e `contatore`
4. Usa `cont` ripetutamente per osservare come cambiano i valori ad ogni iterazione
5. Scrivi una tabella con i valori di `i` e `contatore` ad ogni passaggio

**Domanda**: Qual è la differenza tra `print` e `display`?

---

## Esercizio 6: Debug Multi-File 🔵

### Obiettivo  
Gestire breakpoint in progetti con più file sorgente.

### Consegna
Crea due file:

**matematica.h:**
```c
#ifndef MATEMATICA_H
#define MATEMATICA_H
int moltiplica(int a, int b);
#endif
```

**matematica.c:**
```c
#include "matematica.h"

int moltiplica(int a, int b) {
    int risultato = 0;
    for (int i = 0; i < b; i++) {
        risultato += a;
    }
    return risultato;
}
```

**main.c:**
```c
#include <stdio.h>
#include "matematica.h"

int main() {
    int x = 7;
    int y = 3;
    int prodotto = moltiplica(x, y);
    printf("%d x %d = %d\n", x, y, prodotto);
    return 0;
}
```

**Compiti:**
1. Compila tutti i file insieme con flag di debug
2. Metti un breakpoint sulla riga `int prodotto = moltiplica(x, y);` in `main.c`
3. Esegui e fermati al breakpoint
4. Usa `step` per **entrare** dentro `moltiplica` e osserva come cambia `risultato` ad ogni iterazione del ciclo
5. Ripeti l'esercizio usando `next` invece di `step` — cosa cambia?

### Hint
- Per breakpoint in file specifici: `break file.c:numero_riga`

---

## 📊 Riepilogo Comandi GDB

| Comando | Funzione |
|---------|----------|
| `gcc -g -O0` | Compila per debug |
| `gdb eseguibile` | Avvia GDB |
| `list` | Mostra codice |
| `break N` | Breakpoint riga N |
| `run` | Esegue programma |
| `next` | Passo avanti (no funzioni) |
| `step` | Passo avanti (entra in funzioni) |
| `cont` | Continua esecuzione |
| `print var` | Stampa variabile |
| `display var` | Monitora variabile |
| `bt` | Backtrace (stack) |
| `info b` | Lista breakpoint |
| `del N` | Elimina breakpoint N |
| `quit` | Esci |

---

*Esercizi preparati in base alla lezione GDB del corso di Sistemi Operativi*
