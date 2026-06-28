# PercepBot — A Perceptron-Inspired Q&A Chatbot in C

A lightweight natural language processing experiment written in C that expands on the basic concept of the perceptron. Given a phrase typed by the user, the program analyzes its grammatical structure and finds the most semantically similar answer from a predefined knowledge base using a weighted matching algorithm.

---

## Concept

The core idea is inspired by the **perceptron**: instead of learning numeric weights from labeled data, this program assigns *importance scores* to different grammatical roles and uses them to measure how well a user's question matches any known question-answer pair.

| Grammatical role | Weight |
|---|---|
| Verb | 6 |
| Noun | 8 |
| Prefix / Question word | 2 |

A question is "understood" by reducing it to a compact structural fingerprint:

```
[keyword] [verb1] [verb2] [noun1] [noun2] [prefix]
```

This fingerprint is then compared against all stored answer fingerprints. The answer with the highest cumulative score wins.

---

## Features

- **Grammatical classification** — words are labeled as `verbo`, `nome`, `prefisso`, or `chiave` via an external `grammatica.txt` file
- **Question parsing** — the program detects whether user input is a question (`?`) and extracts a keyword (e.g. `dove`, `come`, `chi`, `quanto`, `di cosa`)
- **Sentiment analysis** — non-question phrases are classified as `FELICE`, `TRISTE`, or `PREOCCUPATO` using a simple bag-of-words frequency model trained on hardcoded example sentences
- **Answer retrieval** — the best matching answer is selected from the knowledge base using weighted structural comparison
- **Debug mode** — interactive debug output showing internal phrase fingerprints and answer indices

---

## File Structure

```
.
├── main.c           # Full source code
├── grammatica.txt   # Word → grammatical role mappings (one per line)
└── README.md
```

### `grammatica.txt` format

One entry per line, word followed by its role:

```
mangiare verbo
pane     nome
il       prefisso
dove     prefisso
```

Supported roles: `verbo`, `nome`, `prefisso`, `chiave`

---

## How It Works

### 1. Startup & Learning (`learn()`)
On launch the program:
1. Reads `grammatica.txt` and populates the grammar lexicon
2. Loads a hardcoded set of training questions (`data_import("domanda", ...)`) 
3. Loads sentiment training sentences for `felice`, `triste`, `preoccupato`
4. Loads the answer knowledge base (`data_import_soluz(...)`)

### 2. User Input (`write_question()`)
The user types a phrase. If it ends with `?`:
- `dividi_domanda()` extracts the question word (e.g. `"dove"`, `"di cosa"`)
- `data_import("domanda", ...)` tokenizes the rest and builds a structural fingerprint
- `confronta_domanda()` scores each stored answer and returns the best match

If there is no `?`:
- `classifica()` runs a bag-of-words sentiment scoring pass and prints `FELICE`, `TRISTE`, or `PREOCCUPATO`

### 3. Answer Matching (`confronta_domanda()`)
For each stored answer, the program compares its structural fingerprint against the user's question fingerprint position by position. Matching tokens earn points according to their grammatical weight. The answer with the most points is printed.

---

## Building

Requires a standard C compiler (GCC or Clang). Tested on Windows with MinGW; the `system("chcp 65001")` and `system("cls")` calls are Windows-specific and can be removed for Linux/macOS.

```bash
gcc main.c -o percepbot
./percepbot
```

---

## Usage Example

```
want debug? 1 yes     0 no
0

> dove posso studiare in silenzio?

la biblioteca è il posto ideale per studiare in silenzio

> oggi mi sento molto solo e triste

TRISTE
```

---

## Limitations & Known Issues

- **Fixed vocabulary size** — `MAX_WORDS 10000`, `MAX_LEN 100`; exceeding these causes undefined behavior
- **No fuzzy matching** — word comparison is exact (`strcmp`); typos or inflected forms not in `grammatica.txt` are ignored
- **`goto` in main loop** — control flow uses `goto ghig` instead of a `while` loop (functionally equivalent but non-idiomatic)
- **Windows-only system calls** — `chcp 65001` and `cls` should be wrapped in `#ifdef _WIN32` guards for portability
- **No persistence** — the knowledge base is entirely hardcoded; restarting the program resets everything
- **Single-token question word limit** — two-word question words like `"di cosa"` or `"di quale"` are handled manually and may break on unexpected input

---

## Possible Extensions

- Load the knowledge base from a file instead of hardcoding it
- Add simple stemming or lemmatization to handle verb conjugations
- Replace the linear scan in `trova_parola()` with a hash map for performance
- Extend `dividi_domanda()` to handle all compound question forms generically
- Port the sentiment training data to an external CSV

---

## Author

Personal experiment — built to explore whether a perceptron-style weighted-score approach can drive basic natural language understanding in pure C, without any external NLP libraries.

Written entirely on a genuinely terrible IDE, with no grand ambition behind it — just a self-training exercise from the period when I was transitioning from C beginner to intermediate. The goal was never to build something production-ready, but to get comfortable with pointers, strings, structs, and file I/O by throwing them at a problem slightly too big for where I was at the time. It shows in the code, and that's fine.
