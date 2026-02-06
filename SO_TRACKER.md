# 📊 SO Tracker - Sistemi Operativi

> **Ultimo aggiornamento**: 2026-02-06

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

### Debug e Strumenti di Sviluppo

- [x] GDB (GNU Debugger) - breakpoint, stepping, backtrace

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
- **Mismatch formato printf** (es. %d per int*)

### Errori Logici

<!-- Registra qui errori logici frequenti -->
- Tracciamento valori variabili durante iterazioni (off-by-one/timing)
- Accesso a puntatori non inizializzati (SegFault)
- Confusione tra indirizzo di p (&p) e valore puntato (*p)
- **Uso di `sizeof` su parametri array** (ottenendo la dimensione del puntatore)
- **Incremento cumulativo di puntatori in un loop** (es. `p += i`)
- **Errore off-by-one nell'incremento di puntatori** (incremento prima dell'utilizzo)

### Cattive Pratiche

<!-- Registra qui pattern negativi ricorrenti -->
- Riassegnazione nome array (puntere a array come costante)
- Uso di scanf %s senza limiti (buffer overflow)

---

## 📝 Storico Lavoro Svolto

### Sessioni Completate

| Data       | Tipo     | Descrizione                               | Esito  |
| ---------- | -------- | ----------------------------------------- | ------ |
| 2026-02-05 | Setup    | Creazione workflow e tracker              | ✅     |
| 2026-02-05 | Esercizi | Creazione esercizi GDB (6 esercizi)       | ✅     |
| 2026-02-06 | Lezione  | Trasformazione lezione Puntatori in MD    | ✅     |
| 2026-02-06 | Esercizi | Creazione esercizi Puntatori (8 esercizi) | ✅     |

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

### Valutazioni Effettuate

| Data       | Esercizio                               | Esito  |
| ---------- | --------------------------------------- | ------ |
| 2026-02-05 | GDB Ex.1 - Compilazione per debug       | ✅     |
| 2026-02-05 | GDB Ex.2 - Breakpoint e ispezione       | ⚠️     |
| 2026-02-05 | GDB Ex.5 - Monitoraggio variabili       | ✅     |
| 2026-02-06 | PTR Ex.1 - Dichiarazione e assegnazione | ✅     |
| 2026-02-06 | PTR Ex.2 - Modifica tramite puntatore     | ✅     |
| 2026-02-06 | PTR Ex.4 - Array e Puntatori (Completato) | ✅     |

---

## 📈 Progresso Generale

- **Lezioni analizzate**: 2
- **Esercizi creati**: 14
- **Codici valutati**: 4
- **Argomenti padroneggiati**: 2 (GDB, Puntatori)

---

### Info di Sistema

File generato automaticamente dal workflow esercizi-so.
