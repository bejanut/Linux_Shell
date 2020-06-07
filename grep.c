#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//citeste numarul sirurilor si sirurile
char **citire(int *pnr_linii, char **psrc);

/*inlocuieste stringul cautat cu unul colorat 
si afiseaza sirul in care s-a gasit.*/
void swap(char **matrice,char *src, int nr_linii);

//insereaza in sir la inceputul altui sir
char *strins (char *p, char *s);

//numara de cate ori se regaseste sirul src in sirul str
int count(char *str, char *src);

int main()
{
	char ** matrice, *src;
	int nr_linii;

	matrice = citire(&nr_linii, &src);
	swap(matrice, src, nr_linii);

	return 0;

}


char **citire(int *pnr_linii, char **psrc)
{
	char ** matrice, citit[200];
	int nr_linii, i;

	fgets(citit, 30, stdin );
	//se elimina caracterul '\n' daca se citeste prin fgets
	if(citit[strlen(citit) - 1 ] ==  '\n')
		citit[strlen(citit) - 1] = 0;
	//copiaza sirul citit si prelucrat printr-un pointer la sirul src
	*psrc = strdup(citit);

	scanf("%d ",&nr_linii); 
	//se scrie valoarea lui n printr-un pointer la valoarea sa
	*pnr_linii = nr_linii; 
	matrice = (char **)malloc(nr_linii * sizeof(char *) );
	if (matrice == NULL)
	{
		fprintf(stderr,"Nu s-a alocat memorie");
		exit(1);
	}
	
	for (i = 0; i < nr_linii; i++)
	{
		fgets(citit, 200, stdin);
		//se elimina caracterul '\n' dace se citeste prin fgets
		if(citit[strlen(citit) - 1 ] ==  '\n')
			citit[strlen(citit) - 1] = 0;
		matrice[i] = strdup(citit);
	}

	

	return matrice;
}

void swap(char **matrice, char *src, int nr_linii)
{
	int i;

	for(i = 0; i < nr_linii; i++)
	{
		//variabila src memoreaza de cate ori s-a gasit stringul src
		int nr = count(matrice[i], src);
		if(nr)
		{	/*se realoca memorie sirului matrice[i] pentru a putea 
			sa se coloreze instantele gasite*/
			matrice[i] = (char *)realloc
			(matrice[i], strlen(matrice[i]) + 10 * nr + 1);
			if (matrice == NULL)
			{
				fprintf(stderr,"Nu s-a alocat memorie");
				exit(1);
			}

			char *aux = strstr(matrice[i], src);
			while(aux) 
			{
				//se coloreaza cuvintele
				strins(aux,"\e[0;31m");
				aux+= 7 + strlen(src);
				strins(aux,"\e[m");
				aux += 3;
				aux = strstr(aux,src);
			}

			printf("%s\n", matrice[i]);
		}

		free(matrice[i]);
	}
	free(src);
	free(matrice);

}

int count(char *str, char *src)
{
	char *aux = strstr(str, src);
	int nr = 0;

	while(aux) 
		{
			nr ++;
			aux += strlen(src);
			aux = strstr(aux, src);
		}
	return nr;
}

char *strins(char *p, char *s)
{
	char aux[ 200 ];
	strcpy(aux, p);
	strcpy(p, s);
	strcat(p, aux);

	return p;
}

