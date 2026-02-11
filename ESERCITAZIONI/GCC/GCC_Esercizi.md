# Esercizi GCC - Pipeline di Compilazione

> **Argomento**: Fasi di compilazione GCC (Preprocessing, Compiling, Assembling, Linking)  
> **Difficoltà**: ⭐⭐ Intermedia  
> **Prerequisiti**: Conoscenza base del C, utilizzo del terminale

---

## 📋 Obiettivi Generali

Questi esercizi ti guideranno attraverso le 4 fasi della pipeline di compilazione GCC:

1. **Preprocessing** - Espansione macro e direttive
2. **Compiling** - Traduzione C → Assembly
3. **Assembling** - Assembly → Codice oggetto
4. **Linking** - Collegamento moduli e librerie

---

## Esercizio 1: Macro e Costanti

### 🎯 Obiettivo

Comprendere il funzionamento delle macro `#define` e ispezionare l'output del preprocessore.

### 📝 Requisiti

Crea un file `macro_test.c` con il seguente contenuto:

```c
#include <stdio.h>

#define PI 3.14159
#define AREA_CIRCLE(r) PI * r * r
#define MAX_SIZE 100

int main() {
    int radius = 5;
    double area = AREA_CIRCLE(radius);
    printf("Area del cerchio: %f\n", area);
    
    int buffer[MAX_SIZE];
    printf("Dimensione buffer: %d elementi\n", MAX_SIZE);
    
    return 0;
}
```

**Compiti:**

1. Compila il file fermandoti dopo la fase di preprocessing: `gcc -E macro_test.c > preprocessed.txt`
2. Apri `preprocessed.txt` e cerca dove sono state espanse le macro `PI`, `AREA_CIRCLE` e `MAX_SIZE`
3. Osserva quante righe di codice sono state aggiunte dall'inclusione di `stdio.h`
4. Definisci una nuova macro `DEBUG` da riga di comando usando `-D` e verifica l'espansione

### 💡 Hint

- Il file preprocessato sarà molto lungo (migliaia di righe) a causa di `stdio.h`
- Usa `grep` per cercare specifiche espansioni: `grep "AREA_CIRCLE" preprocessed.txt`
- La macro `AREA_CIRCLE` viene espansa testualmente, non come funzione

### 🎓 Cosa Impari

- Come funziona il preprocessore
- L'espansione testuale delle macro
- L'impatto delle inclusioni di header
- Definizione di macro da riga di comando con `-D`

---

## Esercizio 2: Macro Parametriche Pericolose

### 🎯 Obiettivo

Scoprire i pericoli delle macro parametriche mal scritte e imparare a scriverle correttamente.

### 📝 Requisiti

Crea un file `macro_danger.c`:

```c
#include <stdio.h>

#define SQUARE_WRONG(x) x * x
#define SQUARE_RIGHT(x) ((x) * (x))

#define SUM_WRONG(a,b) a + b
#define SUM_RIGHT(a,b) ((a) + (b))

int main() {
    int result1 = SQUARE_WRONG(2 + 3);
    int result2 = SQUARE_RIGHT(2 + 3);
    
    printf("SQUARE_WRONG(2+3) = %d\n", result1);
    printf("SQUARE_RIGHT(2+3) = %d\n", result2);
    
    int result3 = SUM_WRONG(1, 2) * SUM_WRONG(1, 2);
    int result4 = SUM_RIGHT(1, 2) * SUM_RIGHT(1, 2);
    
    printf("SUM_WRONG(1,2) * SUM_WRONG(1,2) = %d\n", result3);
    printf("SUM_RIGHT(1,2) * SUM_RIGHT(1,2) = %d\n", result4);
    
    return 0;
}
```

**Compiti:**

1. Prima di compilare, **predici** quali saranno i valori stampati
2. Usa `gcc -E macro_danger.c` per vedere come vengono espanse le macro
3. Compila ed esegui il programma
4. Confronta i risultati con le tue predizioni
5. Spiega perché le macro "WRONG" producono risultati inattesi

### 💡 Hint

- Ricorda: le macro sono sostituzioni **testuali**, non chiamate a funzione
- L'ordine delle operazioni matematiche (precedenza) è cruciale
- `2 + 3 * 2 + 3` è diverso da `(2 + 3) * (2 + 3)`

### 🎓 Cosa Impari

- I pericoli delle macro parametriche
- L'importanza delle parentesi nelle macro
- La differenza tra macro e funzioni
- Come debuggare problemi con le macro

---

## Esercizio 3: Compilazione Condizionale e Debug

### 🎯 Obiettivo

Utilizzare le direttive `#ifdef`, `#if` e le macro predefinite per creare codice di debug configurabile.

### 📝 Requisiti

Crea un file `conditional_debug.c`:

```c
#include <stdio.h>

#ifdef DEBUG
    #define LOG(msg) printf("[DEBUG] File: %s, Line: %d - %s\n", __FILE__, __LINE__, msg)
#else
    #define LOG(msg)
#endif

#define VERSION_MAJOR 2
#define VERSION_MINOR 5

#if VERSION_MAJOR >= 2
    #define FEATURE_ADVANCED 1
#else
    #define FEATURE_ADVANCED 0
#endif

int main() {
    LOG("Programma avviato");
    
    printf("Versione: %d.%d\n", VERSION_MAJOR, VERSION_MINOR);
    
    #if FEATURE_ADVANCED
        printf("Funzionalità avanzate abilitate\n");
    #else
        printf("Funzionalità base\n");
    #endif
    
    LOG("Programma terminato");
    
    return 0;
}
```

**Compiti:**

1. Compila **senza** definire `DEBUG`: `gcc conditional_debug.c -o debug_off`
2. Esegui `./debug_off` e osserva l'output
3. Compila **con** `DEBUG` definito: `gcc -DDEBUG conditional_debug.c -o debug_on`
4. Esegui `./debug_on` e confronta l'output
5. Usa `gcc -E -DDEBUG conditional_debug.c` per vedere come cambia il codice preprocessato
6. Modifica `VERSION_MAJOR` a `1` e ricompila per vedere come cambia il comportamento

### 💡 Hint

- Le macro `__FILE__` e `__LINE__` sono predefinite dal preprocessore
- `#ifdef` verifica se una macro è definita (non importa il valore)
- `#if` valuta espressioni costanti al momento della compilazione

### 🎓 Cosa Impari

- Compilazione condizionale
- Macro di debug configurabili
- Macro predefinite del preprocessore
- Gestione di versioni e feature flags

---

## Esercizio 4: Header Guards e Inclusioni Multiple

### 🎯 Obiettivo

Comprendere il problema delle inclusioni multiple e implementare header guards.

### 📝 Requisiti

Crea tre file:

**`math_utils.h`** (senza header guard):

```c
#define SQUARE(x) ((x) * (x))

int add(int a, int b);
```

**`geometry.h`**:

```c
#include "math_utils.h"

double circle_area(double radius);
```

**`main_multiple.c`**:

```c
#include <stdio.h>
#include "math_utils.h"
#include "geometry.h"

int main() {
    int x = 5;
    printf("Square: %d\n", SQUARE(x));
    return 0;
}
```

**Compiti:**

1. Prova a compilare: `gcc main_multiple.c`
2. Osserva l'errore di "ridefinizione" della macro `SQUARE`
3. Modifica `math_utils.h` aggiungendo header guards:

   ```c
   #ifndef MATH_UTILS_H
   #define MATH_UTILS_H
   
   // contenuto originale qui
   
   #endif
   ```

4. Ricompila e verifica che l'errore sia scomparso
5. Usa `gcc -E main_multiple.c` per vedere quante volte `math_utils.h` viene incluso

### 💡 Hint

- Senza header guards, `math_utils.h` viene incluso due volte (direttamente e tramite `geometry.h`)
- Il nome della macro guard dovrebbe essere unico (convenzionalmente: `NOMEFILE_H`)
- Tutti gli header file professionali usano header guards

### 🎓 Cosa Impari

- Il problema delle inclusioni multiple
- Come funzionano gli header guards
- Best practices per scrivere header file
- L'ordine di espansione delle direttive `#include`

---

## Esercizio 5: Analisi Assembly e Ottimizzazione

### 🎯 Obiettivo

Ispezionare il codice Assembly generato e comprendere l'impatto dei livelli di ottimizzazione.

### 📝 Requisiti

Crea un file `optimization_test.c`:

```c
int sum_array(int *arr, int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum;
}

int main() {
    int numbers[] = {1, 2, 3, 4, 5};
    int result = sum_array(numbers, 5);
    return result;
}
```

**Compiti:**

1. Genera Assembly **senza ottimizzazione**: `gcc -S -O0 optimization_test.c -o asm_O0.s`
2. Genera Assembly **con ottimizzazione**: `gcc -S -O2 optimization_test.c -o asm_O2.s`
3. Confronta i due file `.s` (puoi usare `diff asm_O0.s asm_O2.s` o aprirli affiancati)
4. Conta il numero di istruzioni Assembly in ciascun file
5. Genera Assembly con simboli di debug: `gcc -S -g -O0 optimization_test.c -o asm_debug.s`
6. Osserva le differenze tra architetture: `gcc -S -m32 optimization_test.c -o asm_32bit.s` (se disponibile)

### 💡 Hint

- Il file con `-O2` sarà significativamente più corto
- Cerca il loop nella funzione `sum_array` - con `-O2` potrebbe essere "srotolato" (loop unrolling)
- I commenti con `.loc` e `.file` sono metadati di debug
- L'Assembly è specifico per l'architettura del tuo processore

### 🎓 Cosa Impari

- Come leggere Assembly di base
- L'impatto delle ottimizzazioni sul codice generato
- La relazione tra C e Assembly
- Simboli di debug e loro utilizzo

---

## Esercizio 6: File Oggetto e Simboli

### 🎯 Obiettivo

Creare file oggetto, ispezionarli e comprendere i simboli esportati.

### 📝 Requisiti

Crea due file:

**`calculator.c`**:

```c
int add(int a, int b) {
    return a + b;
}

int multiply(int a, int b) {
    return a * b;
}

static int internal_helper(int x) {
    return x * 2;
}
```

**`main_calc.c`**:

```c
#include <stdio.h>

int add(int a, int b);
int multiply(int a, int b);

int main() {
    printf("5 + 3 = %d\n", add(5, 3));
    printf("5 * 3 = %d\n", multiply(5, 3));
    return 0;
}
```

**Compiti:**

1. Compila solo `calculator.c` in un file oggetto: `gcc -c calculator.c`
2. Verifica che sia stato creato `calculator.o`
3. Ispeziona i simboli con `nm calculator.o`
4. Osserva quali funzioni sono esportate (simboli `T`) e quali sono interne (simboli `t`)
5. Compila `main_calc.c` in oggetto: `gcc -c main_calc.c`
6. Ispeziona `main_calc.o` con `nm` - nota i simboli "undefined" (`U`)
7. Usa `objdump -d calculator.o` per vedere il disassembly del codice oggetto

### 💡 Hint

- `nm` mostra i simboli: `T` = funzione globale, `t` = funzione statica, `U` = undefined
- Le funzioni `static` non sono visibili all'esterno del file
- I simboli `U` in `main_calc.o` saranno risolti durante il linking
- `objdump -d` mostra il codice macchina disassemblato

### 🎓 Cosa Impari

- Creazione di file oggetto con `-c`
- Simboli globali vs statici
- Uso di `nm` e `objdump`
- Cosa significa "undefined reference"

---

## Esercizio 7: Linking e Librerie

### 🎯 Obiettivo

Collegare file oggetto multipli e risolvere dipendenze da librerie esterne.

### 📝 Requisiti

**Parte A: Linking Multi-File**

Usa i file `calculator.c` e `main_calc.c` dell'esercizio precedente.

**Compiti:**

1. Compila entrambi i file in oggetti (se non l'hai già fatto):

   ```bash
   gcc -c calculator.c
   gcc -c main_calc.c
   ```

2. Collega i file oggetto per creare l'eseguibile:

   ```bash
   gcc calculator.o main_calc.o -o calc_program
   ```

3. Esegui `./calc_program` e verifica il funzionamento
4. Prova a compilare solo `main_calc.c` senza `calculator.o`:

   ```bash
   gcc main_calc.o -o calc_fail
   ```

5. Osserva l'errore di "undefined reference"

**Parte B: Linking con Librerie Esterne**

Crea un file `math_test.c`:

```c
#include <stdio.h>
#include <math.h>

int main() {
    double angle = 3.14159 / 4;  // 45 gradi in radianti
    double sine = sin(angle);
    double cosine = cos(angle);
    double power = pow(2.0, 10.0);
    
    printf("sin(45°) = %f\n", sine);
    printf("cos(45°) = %f\n", cosine);
    printf("2^10 = %f\n", power);
    
    return 0;
}
```

**Compiti:**

1. Prova a compilare **senza** linkare la libreria matematica:

   ```bash
   gcc math_test.c -o math_fail
   ```

2. Osserva gli errori di "undefined reference to sin/cos/pow"
3. Compila **con** la libreria matematica:

   ```bash
   gcc math_test.c -lm -o math_program
   ```

4. Esegui `./math_program` e verifica i risultati

### 💡 Hint

- Il linker cerca i simboli in tutti i file oggetto forniti
- `-lm` dice al linker di collegare `libm.so` (la libreria matematica)
- La libreria C standard (`libc`) è sempre collegata automaticamente
- L'ordine dei file oggetto può essere importante in casi complessi

### 🎓 Cosa Impari

- Linking di file oggetto multipli
- Risoluzione di simboli undefined
- Collegamento di librerie esterne con `-l`
- La differenza tra errori di compilazione e linking

---

## Esercizio 8: Progetto Multi-File Completo 🏆

### 🎯 Obiettivo

Creare un progetto completo con header personalizzati, file sorgente multipli e linking di librerie, dimostrando padronanza dell'intera pipeline GCC.

### 📝 Requisiti

Crea un progetto di gestione studenti con la seguente struttura:

**`student.h`**:

```c
#ifndef STUDENT_H
#define STUDENT_H

typedef struct {
    char name[50];
    int id;
    float grades[3];
} Student;

void init_student(Student *s, const char *name, int id);
void set_grade(Student *s, int index, float grade);
float calculate_average(Student *s);
void print_student(Student *s);

#endif
```

**`student.c`**:

```c
#include "student.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

void init_student(Student *s, const char *name, int id) {
    strncpy(s->name, name, 49);
    s->name[49] = '\0';
    s->id = id;
    for (int i = 0; i < 3; i++) {
        s->grades[i] = 0.0;
    }
}

void set_grade(Student *s, int index, float grade) {
    if (index >= 0 && index < 3) {
        s->grades[i] = grade;
    }
}

float calculate_average(Student *s) {
    float sum = 0.0;
    for (int i = 0; i < 3; i++) {
        sum += s->grades[i];
    }
    return sum / 3.0;
}

void print_student(Student *s) {
    printf("Studente: %s (ID: %d)\n", s->name, s->id);
    printf("Voti: %.2f, %.2f, %.2f\n", 
           s->grades[0], s->grades[1], s->grades[2]);
    printf("Media: %.2f\n", calculate_average(s));
    
    // Calcola deviazione standard (usa sqrt dalla libreria math)
    float avg = calculate_average(s);
    float variance = 0.0;
    for (int i = 0; i < 3; i++) {
        variance += pow(s->grades[i] - avg, 2);
    }
    float std_dev = sqrt(variance / 3.0);
    printf("Deviazione standard: %.2f\n", std_dev);
}
```

**`main_student.c`**:

```c
#include <stdio.h>
#include "student.h"

#define NUM_STUDENTS 2

int main() {
    Student students[NUM_STUDENTS];
    
    init_student(&students[0], "Mario Rossi", 1001);
    set_grade(&students[0], 0, 28.0);
    set_grade(&students[0], 1, 30.0);
    set_grade(&students[0], 2, 27.5);
    
    init_student(&students[1], "Laura Bianchi", 1002);
    set_grade(&students[1], 0, 25.0);
    set_grade(&students[1], 1, 26.5);
    set_grade(&students[1], 2, 24.0);
    
    for (int i = 0; i < NUM_STUDENTS; i++) {
        print_student(&students[i]);
        printf("\n");
    }
    
    return 0;
}
```

**Compiti:**

1. **Preprocessing**: Verifica l'espansione delle macro e inclusioni

   ```bash
   gcc -E main_student.c > preprocessed_student.txt
   ```

2. **Compiling**: Genera Assembly per ciascun file

   ```bash
   gcc -S -O0 student.c
   gcc -S -O0 main_student.c
   ```

3. **Assembling**: Crea i file oggetto

   ```bash
   gcc -c student.c
   gcc -c main_student.c
   ```

4. **Linking**: Collega tutto insieme (ricorda la libreria matematica!)

   ```bash
   gcc student.o main_student.o -lm -o student_manager
   ```

5. **Esecuzione**: Testa il programma

   ```bash
   ./student_manager
   ```

6. **Debug**: Compila con simboli di debug e senza ottimizzazione

   ```bash
   gcc -g -O0 student.c main_student.c -lm -o student_debug
   ```

7. **Analisi**: Usa `nm` per ispezionare i simboli in `student.o`

8. **Challenge**: Prova a compilare tutto in un solo comando

   ```bash
   gcc student.c main_student.c -lm -o student_onestep
   ```

### 💡 Hint

- C'è un bug intenzionale in `student.c` - trovalo e correggilo!
- L'header guard in `student.h` previene inclusioni multiple
- La libreria `math.h` richiede il linking con `-lm`
- Puoi compilare tutto in un passo, ma i file oggetto permettono ricompilazioni parziali

### 🎓 Cosa Impari

- Gestione di progetti multi-file
- Creazione e uso di header personalizzati
- Pipeline completa: preprocessing → compiling → assembling → linking
- Best practices per organizzare codice C
- Debugging di progetti complessi

---

## 🎯 Riepilogo Comandi GCC

| Fase | Flag | Output | Descrizione |
|------|------|--------|-------------|
| **Preprocessing** | `-E` | `.txt` o stdout | Espande macro e include |
| **Compiling** | `-S` | `.s` | Genera Assembly |
| **Assembling** | `-c` | `.o` | Crea file oggetto |
| **Linking** | (default) | eseguibile | Collega e crea eseguibile |

### Opzioni Utili

- `-D MACRO=value` - Definisce macro da riga di comando
- `-I <dir>` - Aggiunge directory per cercare header
- `-l<lib>` - Collega libreria (es. `-lm` per math)
- `-L <dir>` - Aggiunge directory per cercare librerie
- `-O0`, `-O2`, `-O3` - Livelli di ottimizzazione
- `-g` - Aggiunge simboli di debug
- `-Wall` - Abilita tutti i warning
- `-Werror` - Trasforma warning in errori

---

## ✅ Checklist Completamento

- [ ] Esercizio 1: Macro e Costanti
- [ ] Esercizio 2: Macro Parametriche Pericolose
- [ ] Esercizio 3: Compilazione Condizionale e Debug
- [ ] Esercizio 4: Header Guards e Inclusioni Multiple
- [ ] Esercizio 5: Analisi Assembly e Ottimizzazione
- [ ] Esercizio 6: File Oggetto e Simboli
- [ ] Esercizio 7: Linking e Librerie
- [ ] Esercizio 8: Progetto Multi-File Completo

**Buon lavoro! 🚀**
