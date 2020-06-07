#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// functia pentru citirea matricei alocata dinamic
char **citire(int *pnr_linii); 

//functie pentru calcularea mediei
void medie(char *s, float *n);

//functie pentru calcularea si scrierea mediilor in vector
float *vec_med(char **matrice, int nr_linii);

//fucntia pentru afisearea mediilor si a notelor si eliberarea memoriei
void afisare(char **matrice, float *med, int nr_linii);

int main()
{
	
	int nr_linii;
	float *med;
	char **matrice;

	matrice = citire(&nr_linii);
	med = vec_med(matrice, nr_linii);
	afisare(matrice, med, nr_linii);

	return 0;
}

char ** citire(int* pnr_linii)
{
	char ** matrice;  
	int nr_linii, dim = 3, i;

	scanf("%d", &nr_linii);
	matrice = (char **)malloc( nr_linii * sizeof(char *) );
	if (matrice == NULL)
	{
		fprintf(stderr,"Nu s-a alocat memorie");
		exit(1);
	}

	//se citesc liniile carcater cu caracter
	for (i = 0; i < nr_linii; i++)
	{
		int p = 0;
		matrice[i] = (char *)malloc( dim * sizeof(char) );
		if (matrice == NULL)
		{
			fprintf(stderr,"Nu s-a alocat memorie");
			exit(1);
		}

		do
		{
			scanf("%c", &matrice[i][p]);
		}while( !(matrice[i][p] <= '9' && matrice[i][p] >= '0') );

		scanf("%c", &matrice[i][p+1] );
		p += 2;

		do
		{
			//se verifica daca mai este memorie libera in vector
			if( p < dim )
			{
				scanf("%c", &matrice[i][p] );
				p++;
			}
			else
			{
				//se realoca memorie pentru vector
				dim += 3;
				matrice[i] = (char *)realloc( matrice[i], dim * sizeof(char) );
				if (matrice == NULL)
				{
					fprintf(stderr,"Nu s-a alocat memorie");
					exit(1);
				}
				scanf("%c", &matrice[i][p] );
				p++;
			}

		}while(!(matrice[i][p-2] == ' ' && matrice[i][p-1] == '0'));
		/*se muta terminatorul de sir la stanga 2 pozitii pentru a elimina
		valoarea 0 din sir*/
		matrice[i][p-2] = 0;
	}
	//se transmite printr-un pointer valoarea citita pentru nr_linii
	*pnr_linii = nr_linii; 

	return matrice;
}

void medie(char *s, float *n)
{
	char * aux, *cuv;
	float medie = 0;
	int x, nr = 0;
	/*creem o copie sa sirului transis ca parametru pentru a nu il strica cu 
	functia strtok*/
	aux = strdup(s);
	cuv = strtok(aux, " ");
	
	do
	{
		//trasnformam caracterele in numere cu functia atoi
		x = atoi(cuv);
		medie += x;
		nr++;
		cuv = strtok(NULL, " ");
	}while(cuv != NULL);
	
	free(aux);
	medie = medie / nr;
	*n = medie;
}

float *vec_med(char **matrice, int nr_linii)
{
	/*se aloca dinamic un vector de numere reale, pentru a putea fi returnat de
	functie*/
	float *med = (float *)malloc( nr_linii * sizeof(float) );
	if (med == NULL)
	{
		fprintf(stderr,"Nu s-a alocat memorie");
		exit(1);
	}

	int i;

	for (i = 0; i < nr_linii; i++)
		medie(matrice[i], &med[i] );

	return med;
}

void afisare(char **matrice, float *med, int nr_linii)
{
	int i, j, src;
	float test;

	for (i = 0; i < nr_linii; i++)
	{
		test = 0;
		src = 0;
		for (j = 0; j < nr_linii; j++)

			if( test < med[j] )
			{
				src = j;
				test = med[j];
			}

		printf("%-10.3f%s\n", med[src], matrice[src] );
		/*media care a fost extrasa se egaleaza cu 0 pentru a putea extrage
		 urmatoarea medie*/
		med[src] = 0;
		free( matrice[src] );
	}
	free(matrice);
	free(med);
}