# 📊 SO Tracker - Sistemi Operativi

> **Ultimo aggiornamento**: 2026-02-11

---

## 📚 Argomenti Chiave

### Concetti Fondamentali

<!-- Aggiungi qui i concetti man mano che vengono trattati nelle lezioni -->
- [ ] Processi e stati dei processi
- [ ] Thread e concorrenza
- [x] Gestione della memoria (Puntatori, Aritmetica, Casting)
- [ ] Filesystem
- [ ] IPC (Inter-Process Communication)
- [ ] Memoria dinamica (malloc/free)
- [x] Pipeline di compilazione GCC (Preprocessing, Compiling, Assembling, Linking)
- [x] Macro e direttive del preprocessore (#define, #include, #ifdef)
- [x] Header guards e prevenzione inclusioni multiple
- [x] Ottimizzazione del codice (-O0, -O2, -O3)
- [x] File oggetto e simboli (globali vs statici)

### Debug e Strumenti di Sviluppo

- [x] GDB (GNU Debugger) - breakpoint, stepping, backtrace
- [x] GCC flags e opzioni di compilazione (-E, -S, -c, -g, -D, -I, -l, -L)
- [x] Analisi Assembly e disassembly
- [x] Strumenti di ispezione binari (nm, objdump, hexdump)

### System Calls Critiche

<!-- System calls importanti per C/UNIX -->
| System Call | Descrizione                  | Priorità   |
| ----------- | ---------------------------- | ---------- |
| `fork()`    | Creazione processi           | 🔴 Alta    |
| `exec()`    | Esecuzione programmi         | 🔴 Alta    |
| `wait()`    | Sincronizzazione             | 🔴 Alta    |
| `pipe()`    | Comunicazione                | 🟡 Media   |
| `signal()`  | Gestione segnali             | 🟡 Media   |
| `scanf()`   | Input formattato (puntatori) | 🟡 Media   |
| `memcpy()`  | Copia memoria                | 🟢 Bassa   |
| `memset()`  | Inizializzazione memoria     | 🟢 Bassa   |

### Pattern di Programmazione

<!-- Pattern ricorrenti nella programmazione di sistema -->
- Producer-Consumer
- Fork-Exec
- Signal handling

---

## ⚠️ Errori Comuni dello Studente

> **Nota interna**: Questa sezione serve per tracciare gli errori ricorrenti.
> NON comunicare allo studente cosa sbaglia nello specifico.

### Errori di Sintassi

<!-- Registra qui errori sintattici ricorrenti -->
- Sintassi comandi GDB (print multipli)
- Dichiarazione puntatori (confusione int* p1, p2)
- Dereferenziazione in dichiarazione vs utilizzo
- **Mancanza punto e virgola** (errore frequente)
- **Assegnazione di intero a puntatore** (senza cast)
- **Casting errato** (es. `(*char)` invece di `(char*)`)
- **Dereferencing di `void*` senza cast** (es. `*ptr` dove ptr è void*)
- **Confusione return vs buffer** (tentativo di ritornare valore per funzioni generiche)
- **Dereferencing di puntatore NULL o non inizializzato** (tentativo di scrivere in memoria non allocata)
- **Dimenticanza punto e virgola** (anche dopo correzioni)
- **Return con valore in funzione `void`**
- **Typos in keyword** (es. `swtich` invece di `switch`)
- **Mismatch formato printf** (es. %d per int*)
- **Mismatch formato printf** (es. %d per int*)

### Errori Logici

<!-- Registra qui errori logici frequenti -->
- Tracciamento valori variabili durante iterazioni (off-by-one/timing)
- Accesso a puntatori non inizializzati (SegFault)
- Confusione tra indirizzo di p (&p) e valore puntato (*p)
- **Scrittura su &ptr invece che ptr** (corruzione del puntatore locale invece della memoria)
- **Uso di `sizeof` su parametri array** (ottenendo la dimensione del puntatore)
- **Incremento cumulativo di puntatori in un loop** (es. `p += i`)
- **Errore off-by-one nell'incremento di puntatori** (incremento prima dell'utilizzo)
- **Accesso fuori dai limiti dell'array** (buffer overflow)
- **Mancanza di `break` nello switch** (fall-through involontario)

### Cattive Pratiche

<!-- Registra qui pattern negativi ricorrenti -->
- Riassegnazione nome array (puntere a array come costante)
- Uso di scanf %s senza limiti (buffer overflow)
- **Uso di VLA (Variable Length Array) senza controlli** (rischio Stack Overflow)

---

## 📝 Storico Lavoro Svolto

### Sessioni Completate

| Data       | Tipo     | Descrizione                               | Esito  |
| ---------- | -------- | ----------------------------------------- | ------ |
| 2026-02-05 | Setup    | Creazione workflow e tracker              | ✅     |
| 2026-02-05 | Esercizi | Creazione esercizi GDB (6 esercizi)       | ✅     |
| 2026-02-06 | Lezione  | Trasformazione lezione Puntatori in MD    | ✅     |
| 2026-02-06 | Esercizi | Creazione esercizi Puntatori (8 esercizi) | ✅     |
| 2026-02-11 | Lezione  | Formattazione e linting GCC_LESSON.md     | ✅     |
| 2026-02-11 | Esercizi | Creazione esercizi GCC (8 esercizi)       | ✅     |

### Esercizi Creati

<!-- Lista degli esercizi creati con riferimento ai file -->
1. **GDB_Esercizi.md** - 6 esercizi su debugging con GDB
   - Compilazione per debug (-g -O0)
   - Comandi base (list, break, run)
   - Stepping (next vs step)
   - Analisi Segmentation Fault (backtrace)
   - Monitoraggio variabili (print/display)
   - Debug multi-file

2. **PUNTATORI_Esercizi.md** - 8 esercizi sui puntatori
   - Dichiarazione e assegnazione base
   - Modifica tramite puntatore
   - Swap con funzioni (passaggio per riferimento)
   - Equivalenza array/puntatori
   - Aritmetica puntatori e calcolo indirizzi
   - Casting e esplorazione byte (endianness)
   - Puntatori generici (void *)
   - Debug Segmentation Fault
   - **Challenge Finale**: Memory Walker (buffer parsing, void**, aritmetica avanzata)

3. **GCC_Esercizi.md** - 8 esercizi sulla pipeline GCC
   - Macro e costanti (#define, espansione)
   - Macro parametriche pericolose (precedenza operatori)
   - Compilazione condizionale e debug (#ifdef, macro predefinite)
   - Header guards e inclusioni multiple
   - Analisi Assembly e ottimizzazione (-O0 vs -O2)
   - File oggetto e simboli (nm, objdump)
   - Linking multi-file e librerie (-lm)
   - **Progetto Completo**: Sistema gestione studenti multi-file

### Valutazioni Effettuate

| Data       | Esercizio                               | Esito  |
| ---------- | --------------------------------------- | ------ |
| 2026-02-05 | GDB Ex.1 - Compilazione per debug       | ✅     |
| 2026-02-05 | GDB Ex.2 - Breakpoint e ispezione       | ⚠️     |
| 2026-02-05 | GDB Ex.5 - Monitoraggio variabili       | ✅     |
| 2026-02-06 | PTR Ex.1 - Dichiarazione e assegnazione | ✅     |
| 2026-02-06 | PTR Ex.2 - Modifica tramite puntatore     | ✅     |
| 2026-02-06 | PTR Ex.4 - Array e Puntatori (Completato) | ✅     |
| 2026-02-06 | PTR Ex.5 - Aritmetica dei Puntatori         | ✅     |
| 2026-02-06 | PTR Ex.6 - Casting e Endianness (Completato)  | ✅     |
| 2026-02-06 | PTR Ex.7 - Puntatori Generici (Completato)    | ✅     |
| 2026-02-07 | PTR Ex.8 - Debug Segmentation Fault         | ✅     |
| 2026-02-11 | PTR Ex.9 - Memory Walker Challenge          | ⚠️     |

---

## 📈 Progresso Generale

- **Lezioni analizzate**: 3
- **Esercizi creati**: 23
- **Codici valutati**: 10
- **Argomenti padroneggiati**: 3 (GDB, Puntatori, GCC Pipeline)

---

### Info di Sistema

File generato automaticamente dal workflow esercizi-so.
