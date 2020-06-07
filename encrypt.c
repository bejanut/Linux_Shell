#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*citeste cate linii are matricea, dupa care citeste liniile ei*/
char **citire(int *pnr_linii);

/*cripteaza un anumit cuvant doar daca nu este format doar din cifre*/
char *crypt(char *sir);

//cripteaza toate liniile din matrice
char **fullcrypt(char **matrice, int nr_linii);

//elimina primele n caractere la inceputul uni string
char *strdel(char *p, int n);

//insereaza in sir la inceputul altui sir
char *strins (char *p, char *s);

/*inlocuieste un cuvant dat, cu cuvantul criptat, corespunzator, folosindu-se 
de pointerul la variablia poz pentru a se asigura ca este modificat cuvantul
potrivit*/ 
char *swap(char *sir, char *cuv, int *poz);

//fucntie pentru afisare si eliberarea memoriei
void afisare(char **matrice, int nr_linii);

int main()
{
	char **matrice;
	int nr_linii;
	matrice = citire(&nr_linii);
	matrice = fullcrypt(matrice, nr_linii);
	afisare(matrice, nr_linii);

	return 0;
}

char **citire(int *pnr_linii)
{
	char **matrice, citit[200];  
	int nr_linii, i;

	scanf("%d ", &nr_linii);
	// se transmite printr-un pointer valoarea citita pentru nr_linii
	*pnr_linii = nr_linii; 
	matrice = (char **) malloc (nr_linii * sizeof (char *) );
	if (matrice == NULL)
	{
		fprintf(stderr,"Nu s-a alocat memorie");
		exit(1);
	}
	for (i=0; i < nr_linii; i++)
	{
		fgets(citit,200,stdin);
		/*daca linia citica se termina in spatiu (' ') 
		inainte de /n eliminam spatiul*/
		if(citit[strlen(citit) - 2] == ' ')
			{
				citit[strlen(citit) - 2] = '\n';
				citit[strlen(citit) - 1] = '\0';
			}
		//se copiaza si se aloca memorie in acelasi timp
		matrice[i] = strdup(citit);
	}
	return matrice;
}

char *crypt(char *sir)
{
	char *aux = strdup(sir);
	strcpy(aux, sir);
	//se foloseste o variabila intreaga cu scop de variabila logica
	int ok=1, i;

	//se testeaza daca sirul are caratere diferite de cifre
	if(sir[0] < '0' || sir[0] > '9') ok=0;

	//se verifica fiecare caracter, daca este o cifra, iar dupa se crpiteaza
	for(i = 1; i < strlen(aux); i++)
	{
		if( sir[i] < '0' || sir[i] > '9')
			ok=0;
		aux[i] = (aux[0] + aux[i]) % 256;
	}

	/*se verifica daca cuvantul trimis prin string-ul "sir" a fost un sir de 
	numere, iar in functie de aceasta evaluare se pregateste sirul criptat sau
	sirul initial pentru a fi returnat*/
	if( ok == 0)
		strcpy(sir,aux);
	free(aux);
	return sir;
}

char **fullcrypt(char **matrice, int nr_linii)
{
	int i;

	for(i = 0; i < nr_linii; i++)
	{
		char *aux, *cuv;
		int poz = 0;
		/*copiem liniiile din matrice prin variabila aux, pentru a nu fi 
		afectate de functia strtok*/
		aux = strdup(matrice[i]);
		cuv = strtok(aux, " ");
		
		do
		{	
			if( cuv[strlen(cuv) - 1] == '\n')
				cuv[strlen(cuv) - 1] = 0;

			matrice[i] = swap(matrice[i], cuv, &poz);
			cuv=strtok(NULL, " ");

		}while( cuv != NULL);

		free(aux);
	}
	return matrice;
}

char *strdel(char *p, int nr)
{
	char aux[200];

	strcpy(aux, p + nr);
	strcpy(p, aux);
	
	return p;
}

char *strins(char *p,char *s)
{
	char aux[200];
	
	strcpy(aux, p);
	strcpy(p, s);
	strcat(p, aux);
	
	return p;
}

char *swap(char *sir,char *cuv,int *poz)
{
	/*sirul criptat s-a folosit pentru a retin cuvantul dupa criptare, iar aux
	pentru a ne pozitiona corect pe sirul in care criptam cuvintele*/
	char *criptat, *aux = strstr(sir + *poz, cuv);
	
	criptat = strdup(cuv);
	strdel(aux, strlen(cuv) );
	criptat = crypt(criptat);
	strins(aux, criptat);
	*poz += strlen(cuv) + 1;
	free(criptat);

	return sir;
}

void afisare(char **matrice, int nr_linii)
{
	int i;

	for( i = 0; i < nr_linii; i++) 
	{
		printf("%s", matrice[i]);
		free(matrice[i]);
	}
	free(matrice);
}