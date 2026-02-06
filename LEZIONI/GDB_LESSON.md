# GBD LESSON

# Laboratorio di Sistemi Operativi: Debugging con GDB

**Università di Torino - Prof. Enrico Bini**

## Introduzione

Il debugging è una fase fondamentale dello sviluppo software, utile per individuare e risolvere problemi (bug) nei programmi. In ambiente Unix/Linux, il motore di debugging standard è **GDB** (GNU Debugger).

Come molti strumenti Unix, GDB è estremamente potente ma può apparire "criptico" ai nuovi utenti, poiché si utilizza interamente da riga di comando.

---

## 1. Preparazione alla compilazione

Per poter effettuare il debug di un programma (ad esempio un file chiamato `test-seg-fault.c` che genera un errore di segmentazione), non basta compilarlo normalmente. È necessario istruire il compilatore `gcc` affinché includa informazioni aggiuntive utili al debugger.

I flag fondamentali da usare sono:

- **`g`**: Aggiunge le informazioni di debug (simboli, nomi delle variabili, riferimenti alle righe di codice) al file oggetto.
- **`O0`** (oppure `O0`): Disabilita tutte le ottimizzazioni del codice. Questo è cruciale perché l'ottimizzazione potrebbe cambiare l'ordine delle istruzioni rendendo il debug passo-passo incomprensibile.

**Comando di compilazione:**

Bash

`gcc -g -O0 test-seg-fault.c -o nome_eseguibile`

---

## 2. Avviare GDB

Per avviare una sessione di debug, si lancia gdb passando il nome dell'eseguibile come argomento.

Bash

`gdb nome_eseguibile`

> **Nota:** Se il tuo programma richiede argomenti da riga di comando, **non** inserirli ora. Li inserirai successivamente con il comando `run`.
> 

Una volta avviato, vedrai il prompt di gdb: `(gdb)`. Da qui puoi inserire i comandi di debug.

---

## 3. Comandi Fondamentali

### Gestione del Codice e Breakpoint

Prima di avviare l'esecuzione, è spesso necessario guardare il codice e decidere dove fermarsi.

- `help`: Mostra l'aiuto sui comandi.
- `list`: Mostra le righe del codice sorgente.
- `list <n_riga>`: Mostra il codice a partire dalla riga specificata.
- `break <n_riga>`: Inserisce un **breakpoint** alla riga specificata. L'esecuzione si fermerà qui.
- `break <file>:<n_riga>`: Inserisce un breakpoint in una riga specifica di un file specifico (utile per progetti multi-file).
- `info b`: Mostra l'elenco dei breakpoint attivi (ognuno ha un ID numerico).
- `del <ID>`: Cancella il breakpoint con quell'ID.

### Esecuzione del Programma

- `run`: Avvia l'esecuzione del programma. Si fermerà al primo breakpoint incontrato o se il programma crasha.
- `run <argomenti>`: Avvia il programma passando gli argomenti da riga di comando specificati.

---

## 4. Analisi Passo-Passo (Stepping)

Una volta che il programma è fermo a un breakpoint, puoi muoverti nel codice istruzione per istruzione:

| Comando | Descrizione |
| --- | --- |
| **`next`** | Esegue la riga di codice successiva. Se c'è una chiamata a funzione, la esegue interamente e passa alla riga dopo (non entra nella funzione). |
| **`step`** | Esegue la riga di codice successiva. Se c'è una chiamata a funzione, **entra** dentro la funzione per debuggarla. |
| **`cont`** | (Continue) Riprende l'esecuzione normale fino al prossimo breakpoint o alla fine del programma. |

Esporta in Fogli

---

## 5. Ispezione dello Stato

Mentre il programma è in pausa, puoi controllare il valore delle variabili e lo stato della memoria.

- `print <espressione>`: Valuta e stampa il valore di un'espressione o variabile in quel momento.
- `display <espressione>`: Simile a print, ma valuta e stampa l'espressione **automaticamente ad ogni passo** (utile per monitorare come cambia una variabile).
- `bt` (**Backtrace**): Mostra lo stack delle chiamate. È utilissimo in caso di crash (*Segmentation Fault*) per capire quale sequenza di funzioni ha portato all'errore.

### Uscita

- `quit`: Esce dal debugger.