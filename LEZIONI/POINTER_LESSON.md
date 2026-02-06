# 🧠 Lezione: Puntatori e Gestione della Memoria

**Sistemi Operativi - Università di Torino**  
*Basato sulle lezioni del Prof. Enrico Bini*

---

## 1. Rappresentazione della Memoria e Variabili

Prima di definire cosa sia un puntatore, dobbiamo formalizzare come il calcolatore vede le variabili.

### 1.1 La natura fisica delle variabili
Nel linguaggio C, tutte le variabili sono rappresentate in ultima analisi come una **sequenza di byte** in memoria. Il "tipo" della variabile (`int`, `float`, ecc.) non è altro che una **lente** attraverso cui interpretiamo quella sequenza di bit:

*   **int, long**: Vengono interpretati come interi in complemento a due.
*   **float, double**: Vengono interpretati come numeri in virgola mobile secondo lo standard IEEE 754.

### 1.2 Definizione di Puntatore
Un puntatore è una variabile speciale che viene interpretata non come un valore numerico tradizionale, ma come un **indirizzo di memoria**.

La dichiarazione avviene specificando il tipo della variabile a cui il puntatore "punterà":

```c
<type> * <identifier>;
```

> ⚠️ **Attenzione**: Quando dichiarate un puntatore, il sistema alloca spazio solo per il puntatore stesso (l'indirizzo), **non** per la variabile a cui esso punta!

Consideriamo l'esempio:
```c
int *pi1, *pi2, i, j;
```
In questo codice, `pi1` e `pi2` sono puntatori a intero, mentre `i` e `j` sono semplici interi. 
*Convenzione*: I nomi dei puntatori contengono spesso "p" o "ptr" (es. `ptr_count`) per facilitarne il riconoscimento.

---

## 2. Operatori sui Puntatori

Esistono due operatori fondamentali per manipolare i puntatori e gli indirizzi.

### 2.1 L'operatore "Address of" (`&`)
L'operatore unario `&` restituisce l'indirizzo di memoria di una variabile. Può essere applicato a qualsiasi variabile.
Se abbiamo una variabile `v` di tipo `T`, allora `&v` sarà di tipo `T*`.

**Esempio**: Se `v` è un `int`, `&v` è un `int *` (indirizzo di un intero).

### 2.2 L'operatore di "Dereferencing" (`*`)
L'operatore unario `*` (da non confondere con quello usato nella dichiarazione) è l'operazione inversa. Esso accede alla **variabile puntata** dal puntatore.

*   Può essere applicato solo a un puntatore.
*   Se `p` è un puntatore, `*p` rappresenta il valore della variabile situata all'indirizzo contenuto in `p`.

> **Nota sintattica critica**: Il simbolo `*` è **polimorfico**. Viene usato sia per dichiarare un puntatore (`int *p;`) sia per dereferenziarlo (`*p = 5;`).

**Domanda d'esame**: È lecito scrivere `&p`?  
*Assolutamente sì*. Poiché `p` è una variabile (che contiene un indirizzo), essa stessa risiede in memoria a un certo indirizzo. `&p` restituisce l'indirizzo della variabile puntatore stessa (un puntatore a puntatore).

---

## 3. Visualizzazione della Memoria: Un Caso di Studio

Analizziamo cosa accade in memoria durante l'esecuzione:

### Fase 1: Dichiarazione
```c
int v;
int *p;
```
*   `v` allocata all'indirizzo `8100` (4 byte). Contenuto: `????` (indefinito).
*   `p` allocata all'indirizzo `93A0` (8 byte su 64-bit). Contenuto: `????`.

### Fase 2: Assegnazione Valore
```c
v = 25;
```
*   Il sistema scrive `25` nei 4 byte all'indirizzo `8100`.

### Fase 3: Assegnazione del Puntatore
```c
p = &v;
```
*   L'indirizzo di `v` (`8100`) viene scritto come valore all'interno della variabile `p`. Ora diciamo che **p punta a v**.

### Fase 4: Dereferenziazione e Modifica
```c
*p += 1;
printf("%d", v);
```
1. Il sistema legge il valore di `p` (`8100`).
2. Accede alla memoria a quell'indirizzo.
3. Legge `25`, aggiunge `1`, e scrive `26` nella locazione `8100`.
4. La `printf` stamperà `26`.

---

## 4. Array e Puntatori: Una Relazione Intima

In C, array e puntatori sono strettamente correlati, ma non identici.

### 4.1 L'Array come Puntatore Costante
Il nome di un array è un **puntatore costante** alla prima cella dell'array stesso.
Dato un puntatore `T *p`, la sintassi `p[i]` è solo "zucchero sintattico" per `*(p + i)`.

```c
int v[10], *p;
```
Le seguenti operazioni sono equivalenti:
*   `*v = 8;` ↔ `v[0] = 8;`
*   `p = v;` ↔ `p = &v[0];` (p punta all'inizio dell'array)

### 4.2 Differenze Chiave
| Caratteristica | Array (`int v[10]`) | Puntatore (`int *p`) |
| :--- | :--- | :--- |
| **Assegnabilità** | Costante (non modificabile: `v = p` ❌) | Variabile (modificabile: `p = v` ✅) |
| **Allocazione** | Area contigua per N elementi | Spazio solo per un indirizzo |
| **sizeof** | Dimensione totale dell'array | Dimensione del solo indirizzo (8 byte) |

---

## 5. Casting di Puntatori

Il tipo del puntatore serve a capire **quanti byte leggere** e **come interpretarli** durante la dereferenziazione.

```c
int v = 256;      // 0x00000100 in memoria
char *p;
p = (char *)&v;   // Casting: interpretiamo l'indirizzo come puntatore a char
*p = 1;           // Modifichiamo solo il primo byte!
printf("%d", v);  // Risultato dipendente dall'endianness (es. 257)
```

---

## 6. Errori di Memoria: Segmentation Fault

Il **Segmentation Fault** avviene quando un processo tenta di accedere a un'area di memoria proibita o non mappata.

*   **Puntatore non inizializzato**:
    ```c
    int *p; 
    *p = 5; // CRASH: p contiene un indirizzo casuale
    ```
*   **Accesso fuori dai limiti (Out-of-bounds)**: Accedere a `v[100]` quando `v` ne ha solo 10.

---

## 7. Puntatori Generici (`void *`)

Un `void *` contiene un indirizzo grezzo senza tipo.

*   Può ricevere l'indirizzo di qualsiasi variabile (`p = &v;`).
*   **NON** può essere dereferenziato direttamente (`*p` ❌).
*   Deve essere castato prima dell'uso per dire al compilatore come interpretare i dati.

---

## 8. Aritmetica dei Puntatori

Se `p` è un puntatore a tipo `T`, l'operazione `p + i` sposta l'indirizzo di `i` posizioni di tipo `T`.

**Formula**:
$$\text{Indirizzo Finale} = \text{Indirizzo}(p) + (i \times \text{sizeof}(T))$$

**Esempio**:
```c
int v[10]; // v all'indirizzo 8100
int *q = v + 3; // q punta a v[3], indirizzo 8112 (8100 + 3*4)
```

---

## 9. Input e Manipolazione Memoria

### 9.1 `scanf` e l'operatore `&`
La `scanf` richiede l'**indirizzo** della variabile per poter scrivere il valore letto al suo interno.
```c
int n;
scanf("%i", &n); // Passiamo l'indirizzo di n
```

### 9.2 Funzioni di `string.h`
*   **`memcpy(dest, src, n)`**: Copia `n` byte da `src` a `dest`.
*   **`memset(p, val, n)`**: Inizializza `n` byte puntati da `p` al valore `val` (spesso usato per azzerare strutture con `0`).

---
*Note: I puntatori sono lo strumento più potente e pericoloso del C. Usali con cautela!*