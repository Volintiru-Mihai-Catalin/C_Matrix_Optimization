# Tema2 - Volintiru Mihai Cătălin

## Implementarea celor 3 metode

Pentru toate cele 3 metode, valorile lui N pentru care am decis să rulez testele individuale sunt din 100 in 100, începând de la 400 până la 1600, în total 13 teste. Acestea se află in fișierul "myinput".

### blas
Pentru această metodă am alocat o matrice unde am copiat matricea B. Am început cu înmulțirea din stânga (A * B * At) și am gândit problema astfel: având în vedere că A este superior triunghiulară, am ales funcția "cblas_dtrmm" care îmi permite să fac înmulțirea a două matrice în care una dintre ele este superior triunghiulară (pentru At este aceeași poveste, chiar dacă este inferior triunghiulară, pentru că în această funcție pot să stabilesc dacă o matrice este transpusă sau nu). Mai apoi m-am folosit de funcția "cblas_dgemm" deoarece are avantajul că înmulțește 2 matrice (Bt * Bt) și după le adună la o a treia matrice (cea obținută mai sus). 
Din câte observ, această metodă este cea mai bună dintre toate, astfel că scoate un timp extrem de bun.


### neopt
Am calculat pe rând înmulțirile, exact cum este prezentat și în laborator, parcurgând matricele pe linii si coloane, fără să țin cont de accesele la memorie și de detectarea constantelor din bucle. În schimb, am ales ca în implementare să nu calculez transpusa matricelor, intrucât dacă am B * At pot foarte simplu să inmulțesc liniile din B cu liniile din A, fiind același lucru.
Aceasta este cea mai ineficientă metodă, nu are nici măcar o optimizare.


### opt_m
Pentru această variantă am identificat constantele din bucle și am încercat să gestionez accesul la vectori ca să nu mai las compilatorul să genereze expresii aritmetice complexe pentru a calcula adresele. Pentru prima înmulțire (A * B) am ales să fac iterațiile prin buclă în stilul i-k-j pentru a câștiga timp. La restul înmulțirilor, am lăsat iterațiile în stilul i-j-k.
Un lucru destul de important de menționat, am concluzionat faptul că dacă aș calcula transpusele matricelor, aș irosi atât timp, cât și spațiu. De aceea, m-am folosit de matricele deja existente pentru a face înmulțirile, fără a mai calcula în mod explicit transpusele. Pentru A * B * At am calculat prima dată A * B = R, deci mai am de calculat R * At. Când înmulțesc o linie din R cu o coloană din At, practic, coloana din At este chiar o linie din A; Deci R * At l-am redus la o înmulțire R * A în care nu se face regula "prima linie din R înmulțită cu prima coloană din A, etc.", ci "prima linie din R înmulțită cu prima linie din A, etc.". Același lucru se întâmplă și la înmulțirea Bt * Bt. Din această cauză, am decis să las iterarea prin bucle in stilul i-j-k (banuiesc că se poate face și în stil i-k-j, dar am simțit că mă complic mult prea mult, deci a fost un fel de trade-off). 
În această metodă am încercat să fac cât mai eficient posibil, dar nu am reușit să scot timpul mai mic de 12 secunde pentru testul 3, ci undeva pe la 13.4 - 13.6 secunde. Cu toate acestea, metoda este mai eficientă decât cea neoptimizată.


## Interpretarea cachegrind

### blas
Pentru această metodă, avem (I refs) numărul total de instrucțiuni executate de program 250,644,675 de instrucțiuni. Rata de miss pentru cache-ul de instrucțiuni (cât de des a trebuit programul să acceseze memoria principală pentru a obține o instrucțiune) pentru cache-ul de nivel 1 (I1) a fost de 0.01%, iar rata de miss pentru cache-ul de nivel 2 (LLi) a fost de 0.00%. 
Referința la date (D refs) este numărul de citiri și scrieri. Avem 93,711,794. Rata de miss pentru cache-ul de date, adică cât de des programul a trebuit să acceseze memoria principală pentru a obține date este: pentru cache-ul de nivel 1 (D1) este de 1.7%, iar pentru cache-ul de nivel 2 a fost de 0.1% (LLd).
Statisticile pentru cache-ul de nivel 2 (LL) sunt următoarele: programul a avut 1,655,797 de referințe la cache-ul de nivel 2 și o rată de miss de 0.0%
Pentru branches si branch misprediction avem următoarele statistici privind instrucțiunile de ramificare în program: 4,510,967 de ramuri și o rată de branch misprediction de 1.6%.

### neopt
Pentru această metodă, avem (I refs) numărul total de instrucțiuni executate de program 6,563,319,295 de instrucțiuni. Rata de miss pentru cache-ul de instrucțiuni (cât de des a trebuit programul să acceseze memoria principală pentru a obține o instrucțiune) pentru cache-ul de nivel 1 (I1) a fost de 0.00%, iar rata de miss pentru cache-ul de nivel 2 (LLi) a fost de 0.00%. 
Referința la date (D refs) este numărul de citiri și scrieri. Avem 3,409,624,626. Rata de miss pentru cache-ul de date, adică cât de des programul a trebuit să acceseze memoria principală pentru a obține date este: pentru cache-ul de nivel 1 (D1) este de 2.9%, iar pentru cache-ul de nivel 2 a fost de 0.0% (LLd).
Statisticile pentru cache-ul de nivel 2 (LL) sunt următoarele: programul a avut 98,318,195 de referințe la cache-ul de nivel 2 și o rată de miss de 0.0%
Pentru branches si branch misprediction avem următoarele statistici privind instrucțiunile de ramificare în program: 323,913,028 de ramuri și o rată de branch misprediction de 0.3%.

### opt_m
Pentru această metodă, avem (I refs) numărul total de instrucțiuni executate de program 2,241,416,238 de instrucțiuni. Rata de miss pentru cache-ul de instrucțiuni (cât de des a trebuit programul să acceseze memoria principală pentru a obține o instrucțiune) pentru cache-ul de nivel 1 (I1) a fost de 0.00%, iar rata de miss pentru cache-ul de nivel 2 (LLi) a fost de 0.00%. 
Referința la date (D refs) este numărul de citiri și scrieri. Avem 1,136,673,752. Rata de miss pentru cache-ul de date, adică cât de des programul a trebuit să acceseze memoria principală pentru a obține date este: pentru cache-ul de nivel 1 (D1) este de 6.7%, iar pentru cache-ul de nivel 2 a fost de 0.0% (LLd).
Statisticile pentru cache-ul de nivel 2 (LL) sunt următoarele: programul a avut 76,456,450 de referințe la cache-ul de nivel 2 și o rată de miss de 0.0%
Pentru branches si branch misprediction avem următoarele statistici privind instrucțiunile de ramificare în program: 228,073,287 de ramuri și o rată de branch misprediction de 0.3%.

## Efectul optimizărilor
Efectul optimizărilor se poate observa destul de ușor. În primul rând, sunt mai puține accese la memorie pentru instrucțiuni în metoda opt_m (2,241,416,238) față de neopt (6,563,319,295), deși numărul de misses pentru ambele nivele de cash pare să fie același. În al doilea rând, sunt mai puține accese de memorie pentru date în metoda opt_m (1,136,673,752) față de metoda neopt (3,409,624,626); acest fapt este datorat de optimizările făcute pentru accesul la memorie și detectarea constantelor din bucle, astfel că datele au fost aduse eficient în cash și utilizate la fel de eficient. Per total, numărul de miss-uri este clar mai mic in varianta optimizată (76,456,450) față de cealaltă (98,318,195). În final, numărul de branch-uri în prima metodă este clar mai mic decât numârul metodei neoptimizate, deci procesorul a reușit să intuiască destul de bine ramificațiile, ducând la o performanță mai mare.


## Analiza comparativă

### Metoda blas
![image info](blas_graph.bmp)
După cum se poate observa și din imaginea de mai sus, metoda blas are un timp de execuție pentru cel mai mare test de aproximativ 2.25 secunde, extrem de rapid. Creșterea timpului este liniară, cu cât crește dimensiunea matricei cu atât crește și timpul de execuție.

### Metoda opt_m
![image info](opt_m_graph.bmp)
După cum se poate observa și din imaginea de mai sus, metoda opt_m are un timp de execuție pentru cel mai mare test de aproximativ 36 de secunde, cât de cât ok. Creșterea timpului este liniară, cu cât crește dimensiunea matricei cu atât crește și timpul de execuție.

### Metoda neopt
![image info](neopt_graph.bmp)
După cum se poate observa și din imaginea de mai sus, metoda neopt are un timp de execuție pentru cel mai mare test de aproximativ 96 de secunde, un timp extrem de mare. Creșterea timpului este liniară, cu cât crește dimensiunea matricei cu atât crește și timpul de execuție.

### Comparare cele 3 metode
![image info](all_graph.bmp)
Dacă le punem pe toate unele lângă altele, se poate observa că pe departe cea mai eficientă metodă este blas, urmată de metoda care folosește optimizări. Ultima din punct de vedere al eficienței este, după cum se intuiește, metoda neopt. Motivul pentru care opt_m are un timp de execuție mai mic decât neopt este pentru că folosește optimizări cache friendly, reduce numărul de accese la memroie, implicit numărul de cache miss-uri.


## Rezultat rulare teste brut
Am decis să atașez si rezultatele rulării celor 13 teste pentru a mă asigura că README-ul este complet. Testele se află in fișierul "myinput".

### blas
```
BLAS SOLVER
Run=./tema2_blas: N=400: Time=0.038201
BLAS SOLVER
Run=./tema2_blas: N=500: Time=0.077124
BLAS SOLVER
Run=./tema2_blas: N=600: Time=0.127487
BLAS SOLVER
Run=./tema2_blas: N=700: Time=0.193809
BLAS SOLVER
Run=./tema2_blas: N=800: Time=0.279289
BLAS SOLVER
Run=./tema2_blas: N=900: Time=0.389728
BLAS SOLVER
Run=./tema2_blas: N=1000: Time=0.553806
BLAS SOLVER
Run=./tema2_blas: N=1100: Time=0.724513
BLAS SOLVER
Run=./tema2_blas: N=1200: Time=0.922376
BLAS SOLVER
Run=./tema2_blas: N=1300: Time=1.154277
BLAS SOLVER
Run=./tema2_blas: N=1400: Time=1.415802
BLAS SOLVER
Run=./tema2_blas: N=1500: Time=1.803433
BLAS SOLVER
Run=./tema2_blas: N=1600: Time=2.158571
```

### opt_m
```
OPT SOLVER
Run=./tema2_opt_m: N=400: Time=0.497523
OPT SOLVER
Run=./tema2_opt_m: N=500: Time=0.965196
OPT SOLVER
Run=./tema2_opt_m: N=600: Time=1.639344
OPT SOLVER
Run=./tema2_opt_m: N=700: Time=2.612578
OPT SOLVER
Run=./tema2_opt_m: N=800: Time=3.834122
OPT SOLVER
Run=./tema2_opt_m: N=900: Time=5.537555
OPT SOLVER
Run=./tema2_opt_m: N=1000: Time=7.611030
OPT SOLVER
Run=./tema2_opt_m: N=1100: Time=10.067021
OPT SOLVER
Run=./tema2_opt_m: N=1200: Time=13.426654
OPT SOLVER
Run=./tema2_opt_m: N=1300: Time=19.065281
OPT SOLVER
Run=./tema2_opt_m: N=1400: Time=22.797579
OPT SOLVER
Run=./tema2_opt_m: N=1500: Time=30.746492
OPT SOLVER
Run=./tema2_opt_m: N=1600: Time=36.274368
```

### neopt
```
NEOPT SOLVER
Run=./tema2_neopt: N=400: Time=1.302821
NEOPT SOLVER
Run=./tema2_neopt: N=500: Time=2.536625
NEOPT SOLVER
Run=./tema2_neopt: N=600: Time=4.491308
NEOPT SOLVER
Run=./tema2_neopt: N=700: Time=6.904852
NEOPT SOLVER
Run=./tema2_neopt: N=800: Time=10.885470
NEOPT SOLVER
Run=./tema2_neopt: N=900: Time=14.519846
NEOPT SOLVER
Run=./tema2_neopt: N=1000: Time=19.844658
NEOPT SOLVER
Run=./tema2_neopt: N=1100: Time=26.703547
NEOPT SOLVER
Run=./tema2_neopt: N=1200: Time=34.880543
NEOPT SOLVER
Run=./tema2_neopt: N=1300: Time=44.422531
NEOPT SOLVER
Run=./tema2_neopt: N=1400: Time=56.238918
NEOPT SOLVER
Run=./tema2_neopt: N=1500: Time=72.232941
NEOPT SOLVER
Run=./tema2_neopt: N=1600: Time=93.672722
```