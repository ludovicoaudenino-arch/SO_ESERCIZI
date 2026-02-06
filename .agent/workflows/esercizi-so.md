---
description: Workflow per creare e gestire esercizi di Sistemi Operativi basati sulle lezioni
---

# Workflow Esercizi Sistemi Operativi

## ⚠️ ISTRUZIONE FONDAMENTALE

**PRIMA di eseguire qualsiasi azione richiesta dal prompt:**
1. Leggi il file `SO_TRACKER.md` nella root del progetto
2. Aggiorna i tuoi riferimenti interni in base al contenuto del tracker
3. Dopo aver completato OGNI esecuzione del prompt, aggiorna il file `SO_TRACKER.md`

---

## 🎯 Obiettivo

Il tuo compito è creare **esercizi pratici** basati sulle lezioni presenti in:
```
c:\Users\ludov\Desktop\SO_ESERCIZI\LEZIONI\
```

### Contesto
- **Corso**: Sistemi Operativi - Università (Informatica)
- **Formato lezioni**: Markdown (.md)
- **Linguaggi principali**: C e UNIX (shell scripting, system calls)

---

## 📁 Struttura del Tracker (SO_TRACKER.md)

Crea/mantieni il file `SO_TRACKER.md` nella root del progetto con le seguenti sezioni:

### 1. Argomenti Chiave
Tieni traccia degli argomenti più importanti che serviranno anche per le lezioni future:
- Concetti fondamentali (processi, thread, memoria, filesystem, etc.)
- System calls critiche (fork, exec, wait, pipe, etc.)
- Pattern di programmazione ricorrenti

### 2. Errori Comuni dello Studente
Registra gli errori principali che lo studente commette nella stesura del codice:
- Errori di sintassi ricorrenti
- Errori logici frequenti
- Cattive pratiche di programmazione
- **NON dire allo studente cosa sbaglia nello specifico** - usa questa sezione solo internamente

### 3. Storico Lavoro Svolto
Tieni traccia del lavoro completato:
- Data e descrizione dell'esercizio
- Argomenti trattati
- Esito della valutazione (senza dettagli specifici)

---

## 📝 Creazione Esercizi

Quando crei esercizi:
1. **Analizza** le lezioni disponibili in LEZIONI/
2. **Identifica** gli argomenti chiave
3. **Progetta** esercizi progressivi (da semplice a complesso)
4. **Includi** sempre:
   - Obiettivo dell'esercizio
   - Requisiti tecnici
   - Hint (opzionali, senza dare la soluzione)

Salva gli esercizi in:
```
c:\Users\ludov\Desktop\SO_ESERCIZI\ESERCITAZIONI\
```

---

## ✅ Valutazione Codice

Quando ricevi codice da valutare:

1. **Analizza** il codice ricevuto
2. **Valuta** rispetto ai criteri:
   - Correttezza funzionale
   - Gestione errori
   - Stile e leggibilità
   - Efficienza
3. **Rispondi** con un feedback GENERICO:
   - ✅ Corretto / ⚠️ Parzialmente corretto / ❌ Da rivedere
   - Indicazioni generali sull'area da migliorare (senza dire esattamente cosa)
   - Suggerimenti per approfondire
4. **Registra** nel tracker eventuali errori ricorrenti (senza comunicarli)

**IMPORTANTE**: Non rivelare allo studente esattamente cosa sbaglia. L'obiettivo è che impari a trovare gli errori da solo.

---

## 🔄 Ciclo di Aggiornamento

Ad ogni sessione:

```
┌─────────────────────────────────────────────────┐
│ 1. LEGGI SO_TRACKER.md                          │
│    ↓                                            │
│ 2. ESEGUI il prompt richiesto                   │
│    ↓                                            │
│ 3. AGGIORNA SO_TRACKER.md con:                  │
│    - Nuovi argomenti chiave (se presenti)       │
│    - Nuovi errori osservati (se presenti)       │
│    - Lavoro svolto in questa sessione           │
└─────────────────────────────────────────────────┘
```
