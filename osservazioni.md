A# Osservazioni — Esercitazione 0

Gruppo: LR-02

Componenti (nome, cognome e username GitHub di entrambi): Giulia Agostini,agostinigiulia  Ilaria Crivella, ilacrivella
URL del repository condiviso: https://github.com/Laboratorio-di-fisica-computazionale/laboratorio-di-fisica-computazionale-1-esercitazione-0-group-5.git

Chi ha usato la tastiera nello step 1 e nello step 2: Giulia Agostini per lo step numero 1, Ilaria crivella per lo step numero 2.

Compilate insieme le osservazioni e discutete le risposte: entrambi dovete
saper spiegare le prove svolte.

## Step 1 — Hello World: compilazione ed esecuzione

Comando di compilazione: Il comando di compilazione che è stato utilizzato consiste in gcc -o hello hello.c -Wall. Ha permesso di tradurre il programma scritto all'interno del file di testo "hello.c", il file sorgente, in un file eseguibile dal sistema operativo "hello".

Comando di esecuzione e risultato osservato: ./hello è il comando di esecuzione che è stato utilizzato per avviare il programma del file sorgente. Subito dopo il messaggio, scritto su emacs, "Hello, computational physics!", è comparso sul terminale. Affinché la frase comparisse isolata, ordinata ed in una riga a sé stante, su emacs è stato inserito il carattere "\n", alla fine della frase scritta dopo printf, subito prima di chiudere le virgolette e le parentesi.

Che cosa ho capito su sorgente ed eseguibile: Il file sorgente, hello.c, è il file di testo, in linguaggio C, che è stato possibile leggere e modificare tramite l'editor emacs. La compilazione ha tradotto il codice in un file eseguibile "hello", che è stato interpretato dal sistema operativo del computer affinché ci fosse la restituzione del messaggio sull'interfaccia del terminale . Quando la compilazione è avvenuta, l'eseguibile ha mostrato il messaggio; se avessimo voluto modificare il messaggio nel file sorgente, avremmo dovuto ricompilare con il comando "gcc", così che l'eseguibile mostrasse il nuovo messaggio, e non il precedente.

Output richiesto e comportamento del programma prima della modifica: Il file sorgente hello.c era vuoto, dato che non era stato inserito nessun messaggio da stampare tramite il comando printf(""). All'interno di hello.c c'era solamente lo scheletro del main. Quindi l'eseguibile non stampava nessun output sul terminale.

Esito dopo la modifica e spiegazione della correzione: Una volta scritto il messaggio "Hello, computational physics!\n", con il comando printf, e avviato l'eseguibile, il terminale ha stampato il messaggio. Si è inoltre fatta una prova inserendo il comando ./hello > output.txt sul terminale, per poi avviare il programma. Il terminale non restituiva nulla. Ciò significava che il messaggio scritto nella sorgente era stato trasferito dal terminale in un file di testo, appunto "output.txt". Per leggere il contenuto questo file, abbiamo imposto il comando "cat output.txt". A questo punto il terminale ha restituito il messaggio scritto nel file sorgente. 

## Step 1 — Git

Quali file ho incluso nel commit e perché: Nel commit di nome "Esercitazione su git e riflessioni su di esso", abbiamo aggiunto i file richiesti per la consegna, dopo aver verificato che non ci fossero errori nelle modifiche apportate. Questi sono: osservazioni.md, hello.c, hello. Prima di effettuare il vero e proprio commit, i file sono stati aggiunti alla staging area tramite il comando git add.

Come ho verificato che la versione provata sia presente su GitHub: Dopo aver effettuato il commit, abbiamo utilizzato il comando git push per inviare la copia remota alla piattaforma online. A questo punto è stato verificato che tutti i file fossero presenti su GitHub.

Che cosa ho osservato prima e dopo `git pull`, e perché non serve un nuovo clone: Prima di effettuare git pull, non era possibile visualizzare le modifiche da remoto. Per visualizzarle, abbiamo dovuto sincronizzare la copia dei file online con il sistema operativo del nostro computer, facendo git pull. Non è necessario effettuare un'altra volta git clone, come invece è stato fatto all'inizio dell'esercitazione, perché il repository remoto è già collegato a quello sulla piattaforma online. All'inizio dell'esercitazione, abbiamo verificato appunto che entrambi i repository fossero collegati tramite la risposta che ci ha fornito il terminale: "origin". Questa risposta ci ha assicurato che la sincronizzazione dei due repository fosse avvenuta correttamente.
