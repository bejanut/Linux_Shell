				Linux Shell Commands
		
Grep

	Pentru a implementa functia grep din linux m-am folosit de functia strstr
pentru a determina daca sirul cautat exista intr-o linie citita. Se numara de
cate ori se gasea sirul cautat, liniei ii era marita dimensiunea, iar sirurile
gasite se colorau. Dupa acest procedeu se afisa linia.


Cut

	"Cuvintele" de pe o linie se extrag cu functia strtok, care lucreaza pe o
copie a liniei, numarandu-se cate cuvinte extragem. Numarul cuvantului este 
comparat cu valoarea din vectorul de coloane (care a fost sortat si din care 
s-au eliminat duplicatele). Daca cele 2 valori sunt egale "cuvantul" se adauga
intr-un sir auxiliar urmat de noul delimitator. Cand se termina cuvintele din
linie, se elimina ultimul delimitator si se afiseaza sirul auxiliar.


Sort

 	Se citesc liniile si se elimina nuamrul 0 de la final. Se extrag cuvintele 
 si se transforma din char in numere intregi. Se face media fiecarei linii si 
 se memoreaza intr-un vector de numere reale. La final se extrag mediile in
 ordine descrescatoare si se afiseaza langa ele linia corespunzatoare.


Encrypt

	 Cuvintele de pe o linie se extrag cu strtok si apoi sunt criptate in cazul
in care acestea nu sunt formate doar din cifre. Dupa criptatre cuvantul este
inlocuit in linie. La final se afiseaza toate liniile.
