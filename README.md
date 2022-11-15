# cartella esercizi LSN 

### Contenuto:

Ciascuna cartella contiene il jupyer notebook con i risultati ottenuti in ogni esercitazione, il codice sorgente `.cpp`, l'header file `.h`l'eseguibile `.exe`, il Makefile, la libreria `random` ed eventuali altre piccole librerie scritte da me. 


### Istruzuioni per la compilazione:
Per compilare gli esercizi dei primi 9 laboratori entrare nella cartella d'interesse, digitare
 `$ make`
e quindi
`$ ./"nome file codice sorgente.exe` (ad esempio `main.exe`). 
Per compilare gli esercizi dell'esercitazione 10 invece, dopo aver digitato `make` si deve digitare
` mpiexec -np "$ numero nodi" ./main.exe` (ad esempio `  mpiexec -np 4 ./main.exe` per utilizzare 4 nodi.
