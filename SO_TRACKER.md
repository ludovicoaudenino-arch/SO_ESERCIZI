# 📊 SO Tracker - Sistemi Operativi

> **Ultimo aggiornamento**: 2026-02-05

---

## 📚 Argomenti Chiave

### Concetti Fondamentali
<!-- Aggiungi qui i concetti man mano che vengono trattati nelle lezioni -->
- [ ] Processi e stati dei processi
- [ ] Thread e concorrenza
- [ ] Gestione della memoria
- [ ] Filesystem
- [ ] IPC (Inter-Process Communication)

### Debug e Strumenti di Sviluppo
- [x] GDB (GNU Debugger) - breakpoint, stepping, backtrace

### System Calls Critiche
<!-- System calls importanti per C/UNIX -->
| System Call | Descrizione | Priorità |
|-------------|-------------|----------|
| `fork()` | Creazione processi | 🔴 Alta |
| `exec()` | Esecuzione programmi | 🔴 Alta |
| `wait()` | Sincronizzazione | 🔴 Alta |
| `pipe()` | Comunicazione | 🟡 Media |
| `signal()` | Gestione segnali | 🟡 Media |

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

### Errori Logici
<!-- Registra qui errori logici frequenti -->
- Tracciamento valori variabili durante iterazioni (off-by-one/timing)

### Cattive Pratiche
<!-- Registra qui pattern negativi ricorrenti -->
_Nessun errore ancora registrato_

---

## 📝 Storico Lavoro Svolto

### Sessioni Completate

| Data | Tipo | Descrizione | Esito |
|------|------|-------------|-------|
| 2026-02-05 | Setup | Creazione workflow e tracker | ✅ |
| 2026-02-05 | Esercizi | Creazione esercizi GDB (6 esercizi) | ✅ |

### Esercizi Creati
<!-- Lista degli esercizi creati con riferimento ai file -->
1. **GDB_Esercizi.md** - 6 esercizi su debugging con GDB
   - Compilazione per debug (-g -O0)
   - Comandi base (list, break, run)
   - Stepping (next vs step)
   - Analisi Segmentation Fault (backtrace)
   - Monitoraggio variabili (print/display)
   - Debug multi-file

### Valutazioni Effettuate
<!-- Storico delle valutazioni del codice dello studente -->
| Data | Esercizio | Esito |
|------|-----------|-------|
| 2026-02-05 | GDB Ex.1 - Compilazione per debug | ✅ |
| 2026-02-05 | GDB Ex.2 - Breakpoint e ispezione | ⚠️ |
| 2026-02-05 | GDB Ex.5 - Monitoraggio variabili | ✅ |

---

## 📈 Progresso Generale

- **Lezioni analizzate**: 1
- **Esercizi creati**: 6
- **Codici valutati**: 3
- **Argomenti padroneggiati**: 1 (GDB)

---

*File generato automaticamente dal workflow esercizi-so*
