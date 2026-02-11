# 1. La Pipeline di Trasformazione: Panoramica

Un programma scritto in C non è altro che un file di testo. Affinché la CPU possa eseguirlo, questo testo deve subire una sequenza di trasformazioni, ognuna delle quali prende in input un file e produce in output un nuovo file con un livello di astrazione sempre più vicino all'hardware.

Il comando `gcc`, pur essendo chiamato "compilatore", si occupa in realtà di richiamare in sequenza i seguenti strumenti per completare i 4 step fondamentali:

1. **Pre-processing (Pre-processamento)**: Modifica sintatticamente il codice sorgente interpretando speciali direttive.
2. **Compiling (Compilazione)**: Traduce il codice C (ormai espanso) in codice Assembly.
3. **Assembling (Assemblaggio)**: Converte le istruzioni Assembly in codice macchina (o codice oggetto).
4. **Linking (Collegamento)**: Unisce i vari moduli oggetto e le librerie esterne per generare l'eseguibile finale.

Analizziamo ora ciascuna di queste fasi con il massimo rigore accademico.

---

## 2. Fase 1: Il Pre-processing (Pre-processamento)

Il pre-processore è il primo attore ad entrare in scena. Prende in input il file sorgente originale (il file `.c` scritto dal programmatore) e restituisce in output un altro file di testo, in cui tutte le direttive del pre-processore sono state sostituite o espanse .

Questa operazione è puramente *tipografica*: il pre-processore non comprende la sintassi del C, ma si limita a manipolare il testo secondo regole stringenti. Le "istruzioni" destinate a questo strumento si chiamano **direttive**, iniziano sempre con il simbolo cancelletto `#` e, per convenzione rigorosa, non devono mai essere indentate, ma posizionate come primo carattere della riga .

Le direttive principali sono `#define`, `#include`, `#if`, `#ifdef`.

### 2.1 La direttiva `#define`: Costanti e Macro

La direttiva `#define` viene utilizzata per definire costanti e macro all'interno del codice.

#### Costanti

Un classico esempio di definizione di costante è:

```c
#define VEC_LEN 80
int v[VEC_LEN], i;
for (i=0; i<VEC_LEN; i++) {
    v[i] = /* something */;
}

```

In questo modo, se la dimensione del vettore dovesse cambiare, basterà modificare il valore `80` in un solo punto del codice, senza dover cercare ogni occorrenza nel file. Per convenzione, i nomi delle macro che fungono da costanti sono scritti rigorosamente in MAIUSCOLO. È anche possibile definire costanti "vuote" (es. `#define EMPTY_CONST`), che vengono semplicemente rimosse dal file sorgente durante questa fase.

Le macro sono fondamentali per configurare il codice sorgente; ad esempio, questo meccanismo è alla base della configurazione dei sorgenti del kernel Linux tramite `make menuconfig`. Inoltre, possiamo definire una macro direttamente da riga di comando invocando `gcc` con l'opzione `-D`. Invocare `gcc -D PI=3.14` ha lo stesso identico effetto di inserire `#define PI 3.14` in testa al file sorgente.

#### Macro Parametriche (Le false funzioni)

Possiamo usare `#define` per creare macro con parametri, che **possono sembrare funzioni ma non lo sono in alcun modo**. La sostituzione rimane tipografica, il che nasconde insidie pericolosissime.

Consideriamo la macro:

```c
#define SQUARE(x) x * x

```

Un'espressione come `a = SQUARE(2)+SQUARE(3);` viene sostituita correttamente con `a = 2*2+3*3;`. Ma osservate cosa succede con una macro definita in modo ingenuo:

```c
#define SUM(x,y) x+y

```

Se eseguiamo `a=SUM(1,2)*SUM(1,2);`, il pre-processore espande il testo producendo esattamente:

```c
a = 1+2*1+2;
```

Il risultato matematico di questa espressione è 5, e non 9 come ci aspetteremmo se fossero state funzioni reali!

La regola d'oro in Sistemi Operativi per scrivere macro parametriche è: **usare sempre le parentesi tonde per racchiudere ogni parametro e l'intera macro**. La versione corretta è:

```c
#define SUM(x,y) ((x)+(y))
```

In questo modo `a=SUM(1,2)*SUM(1,2);` viene espanso in modo sicuro come `((1)+(2))*((1)+(2))`.

#### Macro su più righe e Stringificazione

Le macro `#define` dovrebbero idealmente occupare una singola riga. Tuttavia, per macro complesse, è possibile estenderle su più righe utilizzando il carattere di *backslash* `\` alla fine di ogni riga.
Ecco un esempio di una macro per scambiare due variabili (swap) :

```c
#define EXCHANGE(type,a,b) { \
    type aux; \
    aux = a; \
    a = b; \
    b = aux; \
}

```

Questa macro verrà invocata nel codice come `EXCHANGE(int, a, b);`.

Infine, esiste l'operatore di "stringificazione" `#`. Se `v` è un parametro di una macro, `#v` restituisce la stringa del nome della variabile `v`. Questo è estremamente utile per funzioni di debugging:

```c
#define PRINT_INTV(v) printf("%s=%i\n", #v, v);
PRINT_INTV(var1); /* Verrà espanso in: printf("%s=%i\n", "var1", var1); */
```

### 2.2 La direttiva `#include` e le inclusioni multiple

La direttiva `#include` serve a inserire il contenuto di un file esterno, tipicamente un *header file*, direttamente nel punto in cui si trova la direttiva.
La sintassi determina il percorso di ricerca:

- `#include <stdio.h>`: Le parentesi angolari indicano al pre-processore di cercare il file nei percorsi standard di sistema (solitamente `/usr/include/`).
- `#include "my_header.h"`: I doppi apici forzano la ricerca partendo prima dalla directory corrente. Questo si usa per includere gli header definiti dall'utente per il progetto specifico. Se necessario, l'opzione `gcc -I <dir>` istruisce il compilatore a cercare gli header prima nella directory `<dir>` specificata.

Un *header file* espone e dichiara le funzioni di una libreria. Nel mondo Unix/Linux, la libreria standard C, spesso chiamata `libc` (la variante GNU è la `glibc`), mette a disposizione funzioni essenziali. Tra gli header più usati troviamo:

- `stdio.h`: per input/output e gestione file.
- `string.h`: per la manipolazione di stringhe e copie di blocchi di memoria.
- `math.h`: per le funzioni matematiche come seno, coseno, potenze (`sin`, `cos`, `pow`).
- `errno.h`: per testare i codici d'errore impostati dalle chiamate di sistema o funzioni di libreria.
- `limits.h`: contiene i valori minimi e massimi dipendenti dall'architettura (min/max) per i vari tipi di dato.
- `stdlib.h`: per numeri casuali, allocazione di memoria dinamica e controllo dei processi.
- `ctype.h`: per testare il tipo di caratteri (es. maiuscolo, minuscolo).

#### Prevenzione delle inclusioni multiple

In progetti complessi, è comune che più file includano gli stessi header. Immaginate che il vostro file `.c` includa sia `stdlib.h` che `stdio.h` . Se entrambi questi file di sistema includessero al loro interno `features.h`, il pre-processore copierebbe il contenuto di `features.h` due volte. Questo porterebbe ad un errore (o warning) di "doppia definizione" per variabili e funzioni.
Per evitare questo disastro, tutti gli header file implementano la tecnica dell'**Header Guard**. Il file inizia e finisce con una guardia condizionale (potete verificarlo aprendo `/usr/include/stdio.h` con un editor come gedit):

```c
#ifndef _STDIO_H
#define _STDIO_H
/* contenuto dell'header file qui */
#endif /* _STDIO_H */
```

Alla prima inclusione, la macro `_STDIO_H` non è definita, quindi il contenuto viene letto e la macro viene creata. Alle successive inclusioni, la condizione `#ifndef` fallisce, scartando tutto il contenuto per evitare duplicazioni.

### 2.3 Compilazione Condizionale e Macro di Debug

Porzioni di codice possono essere inserite o rimosse dall'eseguibile finale utilizzando le direttive `#if`, `#else`, `#endif`, e le varianti `#ifdef` (se definito) e `#ifndef` (se non definito).

```c
#if integer-const
    /* code inserted if non-zero */
#else
    /* code inserted otherwise */
#endif
```

È cruciale ricordare che **le condizioni della direttiva `#if` non possono basarsi su variabili C**! Esse devono essere risolte al momento del pre-processamento, prima ancora che il programma esista in fase di run-time.

Questo meccanismo è utilissimo per rimuovere temporaneamente blocchi di codice per finalità di test (debugging) usando la direttiva `#if 0` (che scarta il blocco) o `#if 1` (che lo reinserisce), aggirando i limiti dei normali commenti su più righe che non possono essere innestati.

Per supportare ulteriormente il debugging strutturato, il pre-processore ci regala alcune macro predefinite utilissime:

- `__FILE__`: Si espande in una stringa contenente il nome del file in cui appare. Indispensabile in programmi composti da decine di file.
- `__LINE__`: Fornisce l'intero del numero di riga corrente in cui appare la macro.
- `__DATE__` e `__TIME__`: Stringhe contenenti la data e l'ora in cui è avvenuta la compilazione.

Un esempio magistrale di codice per la diagnostica è la creazione di una macro di log personalizzata:

```c
#ifdef DEBUG
    #define MY_DBG printf("File %s, line %i\n", __FILE__, __LINE__)
#else
    #define MY_DBG
#endif
```

### 2.4 La macro del puntatore NULL

Un'ultima nota essenziale su `#define` riguarda la gestione della memoria. Nei sistemi operativi, il concetto di "puntatore non valido" è rappresentato dalla macro `NULL`.
Essa è definita nel seguente modo:

```c
#define NULL (void *)0
```

Il valore associato a `NULL` è zero; se scriviamo `int *p = NULL;`, tutti i bit della variabile puntatore `p` vengono azzerati in memoria. Un puntatore `NULL` non punta ad alcuna locazione di memoria utile (spesso mappa la pagina zero che il Sistema Operativo protegge da lettura/scrittura in user-space), e tentare di dereferenziarlo provocherà un accesso illegale.

### 2.5 Invocare solo il Pre-processore

Per ispezionare il risultato esatto delle macro espanse, è possibile interrompere `gcc` chiedendogli di eseguire *solo* la fase di pre-processamento. Questo si ottiene con il flag `-E`:

```bash
gcc -E filename.c
```

L'output verrà stampato direttamente sul terminale (stdout). Poiché questo output è solitamente lunghissimo e complesso, è consigliabile reindirizzarlo in un file di testo tramite l'operatore della shell `>`:

```bash
gcc -E filename.c > after-pre-proc.txt
```

In sintesi, per questa fase, ricordate le tre opzioni principali di `gcc`: `-E` (fermati dopo il pre-processing), `-D` (definisci una macro da terminale) e `-I <dir>` (cerca header nella directory custom ignorando prima i percorsi standard, utilissimo se volete sovrascrivere dichiarazioni di funzioni di sistema).

---

## 3. Fase 2: Il Compiling (Compilazione verso Assembly)

Dopo il pre-processamento, il programma C originario (che è ancora un file di testo) viene tradotto dal vero e proprio compilatore in una sequenza di istruzioni in linguaggio Assembly (sempre in formato testo).

Possiamo istruire `gcc` a fermarsi subito dopo questa fase di traduzione C → Assembly utilizzando l'opzione `-S`:

```bash
gcc -S filename.c
```

Di default, questo comando salva le istruzioni Assembly all'interno di un file rinominato in `<filename>.s`.

### Opzioni di Compilazione

Il comando `gcc` possiede migliaia di opzioni per controllare meticolosamente questa fase (esattamente 2519 opzioni menzionate scherzosamente, ma visibili tramite `man gcc`). Le categorie principali riguardano:

**Avvisi ed Errori (Warnings/Errors)**:

- `-Wextra`: Abilita avvisi aggiuntivi rispetto allo standard.
- `-Wvla`: Vieta l'uso dei Variable Length Arrays (Array a lunghezza variabile), spesso considerati una cattiva pratica in C standard.
- `-Werror`: Trasforma qualsiasi avviso (warning) in un errore fatale, bloccando la compilazione.

**Cross-compilazione (Architetture)**: Permette di generare codice Assembly per architetture hardware diverse dalla macchina su cui si sta compilando.

- `-m32`: Genera codice per architetture a 32-bit.
- `-marm`: Produce eseguibili per processori ARM.
- `-march=rv64im`: Targettizza l'architettura RISC-V (potete approfondire nella sezione "RISC-V Options" delle pagine `man` di `gcc`).

**Ottimizzazione del Codice**: Il compilatore può riscrivere parti del vostro codice per renderlo più performante, dipendentemente dall'architettura hardware sottostante.

- `-O2`: Applica un set standard di ottimizzazioni avanzate, come ad esempio il *loop unrolling* (srotolamento dei cicli).
- `-Os`: Tenta di ottimizzare primariamente la *dimensione* del file oggetto finale, sacrificando a volte una frazione di velocità per risparmiare spazio su disco/memoria.
- `-O0`: Nessuna ottimizzazione.

**Debugging**:

- `-g`: Aggiunge all'output i simboli di debugging. Questi metadati permettono a debugger esterni come `gdb` di mappare le istruzioni macchina alle righe originarie del vostro file C.

Da notare che un codice pesantemente ottimizzato (es. `-O2` o `-O3`) altera la struttura sequenziale delle istruzioni rendendo estremamente arduo il debugging passo-passo. Pertanto, per analizzare un programma in `gdb`, la combinazione raccomandata è:

```bash
gcc -S -g -O0 test-print-char.c
```

---

## 4. Fase 3: L'Assembling (Assemblaggio)

L'assemblaggio è la fase in cui il file di testo contenente le istruzioni Assembly (`.s`) viene definitivamente tradotto in **codice macchina** puro. A questo punto, abbandoniamo l'insieme dei caratteri leggibili ASCII: l'output prodotto è un file binario, denominato **codice oggetto** (object code).

L'estensione di default assegnata dal sistema a questi file oggetto è `<filename>.o`.

Se volete bloccare la pipeline di `gcc` subito dopo l'assemblaggio, preservando il file oggetto ma senza creare ancora un eseguibile finale funzionante, dovete utilizzare il flag `-c` (minuscolo):

```bash
gcc -c test-print-char.c
```

Poiché l'output `.o` è binario e incomprensibile ad occhio nudo tramite i normali editor di testo, per ispezionarne il contenuto a basso livello è necessario utilizzare utility come l'hexdump:

```bash
hexdump -C test-print-char.o
```

---

## 5. Fase 4: Il Linking (Collegamento)

Siamo giunti all'ultima, cruciale fase: il collegamento o *Linking*.
Un file oggetto solitamente non è in grado di funzionare da solo. Mancano al suo interno i riferimenti assoluti per le funzioni di libreria di sistema (come la funzione `printf` richiamata nel vostro sorgente) e per altre dipendenze.

Il Linker prende in ingresso uno o più moduli oggetto (`.o`) e librerie (`.a` per quelle statiche, `.so` o `.o` per quelle condivise) e li collega assieme per creare un unico **eseguibile**.
Perché l'operazione vada a buon fine, il linker impone una regola tassativa: nell'insieme dei file oggetto forniti, **deve essere definita una (e una sola) funzione `main(...)**`. Essa rappresenta l'entry point (il punto d'ingresso) in cui il sistema operativo inizierà l'esecuzione del processo.

La Libreria C Standard GNU (`glibc`) è sempre implicitamente collegata in modo automatico ad ogni invocazione di `gcc`. Tuttavia, altre librerie di sistema non lo sono, e richiedono un collegamento esplicito. Il caso più emblematico è la libreria matematica. Se provate a utilizzare la funzione `sin()` (seno) inclusa in `math.h` e provate a compilare senza avvisare il linker, riceverete un errore di "undefined reference".

### Opzioni del Linker

Per istruire il linker sulle librerie esterne da aggiungere, si usano due opzioni fondamentali:

- `-l<lib-name>` (L minuscola): Comunica al linker di collegare la libreria specificata. Ad esempio, `-lm` forza il collegamento della libreria matematica (che risiede nel file `libm.so` o `libm.a`).
- `-L<library-path>` (L maiuscola): Se avete scaricato o compilato una libreria personale in una cartella non standard, `-L` permette di specificare la directory dove cercare i file della libreria prima di ispezionare le path predefinite di sistema come `/usr/lib`.

Come esercizio pratico di chiusura per dimostrare l'importanza di questa fase isolata rispetto alle precedenti, verificate la differenza di comportamento tra i due comandi seguenti su un file C privo di funzioni main o con chiamate di libreria non risolte:

```bash
gcc -c test-no-link.c  # Assembla con successo in un file .o
gcc test-no-link.c     # Fallirà brutalmente durante il linking!
```

---

Spero che questa disamina dettagliata abbia chiarito il funzionamento intimo di `gcc`. C'è qualche concetto della fase di pre-processing o sui parametri del linker che desiderate io approfondisca con ulteriori esempi?
