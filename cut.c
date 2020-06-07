#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//citeste valorile initiale
int * citire_init(char **pdel, int *nr_col, char **newdel);

//citeste numarul liniilor din matrice si matricea
char ** citire_mat(int *pn);

//sorteaza vectorul eliminand duplicatele
void bsort(int *vec, int *n);

/*selecteaza coloanele corespunzatoare pozitiilor citite si afiseaza sirul cu 
noul delimitator*/
void cut(char **matrice, int nr_linii, int *col, int nr_col, char *del, char *ndel);

//functie folosita pentru eliberarea memoriei
void freeall(char **matrice, char *del, char *newdel, int *col);

int main()
{
	char **matrice, *del, *newdel;
	int *col, nr_col, nr_linii;

	col = citire_init(&del, &nr_col, &newdel);
	matrice = citire_mat(&nr_linii);
	cut(matrice, nr_linii, col, nr_col, del, newdel);
	freeall(matrice, del, newdel, col);

	return 0;
}

int * citire_init(char **pdel, int *nr_col, char **newdel)
{
	int *col, i;
	char aux[10], c;

	fgets(aux, 10, stdin);
	/*se verifica daca ultimul caracter este terminator de lini si se elimina
	in cazul unui raspuns pozitiv*/ 
	if(aux[strlen(aux) - 1] == '\n')
		aux[strlen(aux) - 1] = 0;
	*pdel = strdup(aux);

	scanf("%d", nr_col);
	col = (int *)malloc(*nr_col * sizeof(int));
	if (col == NULL)
	{
		fprintf(stderr,"Nu s-a alocat memorie");
		exit(1);
	}

	for(i = 0; i < *nr_col; i++)
		scanf("%d,", &col[i]);
	/*se citeste un carcater pentru a elimina caracterul '\n' de pe linia cu
	anterioara*/ 
	scanf("%c", &c);
	
	fgets(aux, 10, stdin);
	/*se verifica daca ultimul caracter este terminator de lini si se elimina
	in cazul unui raspuns pozitiv*/ 
	if(aux[strlen(aux) - 1] == '\n')
		aux[strlen(aux) - 1] = 0;
    *newdel = strdup(aux);
    
    //sortam vectorul inainte sa il returnam
    bsort(col, nr_col);
	
	return col;
}

char ** citire_mat(int* pnr_linii)
{
	char ** matrice, citit[200];  
	int nr_linii,i;
	scanf("%d ",&nr_linii);
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
		if(citit[strlen(citit) - 1] ==  '\n')
			citit[strlen(citit) - 1] = 0;
		matrice[i] = strdup(citit);
	}

	return matrice;
}


void bsort(int *vec, int *nr_linii)
{
	int i,j;
	int aux;

	for(i = 0; i < *nr_linii-1; i++)

		for(j = i+1; j < *nr_linii; j++)

			if(vec[i] >= vec[j])
			{
				//se elimina elementele duplicate din vector
				if(vec[i] == vec[j])
				{
					vec[j] = vec[(*nr_linii) - 1];
					j--;
					(*nr_linii)--;
				}
				else
				{	
					aux = vec[i];
					vec[i] = vec[j];
					vec[j] = aux;
				}
			}
}

void cut(char **matrice, int nr_linii, int *col, int nr_col, char *del, char *ndel)
{
	//folosim sirul print pentru a adauga coloanele cerute si a le afisa
	char print[ 200 ], *p, *cpys;
	int nr, poz, i;

	for(i = 0; i < nr_linii; i++)
	{
		strcpy(print, "");
		nr = 0; 
		poz = 0;
		cpys = strdup( matrice[i] );
		p = strtok(cpys, del);
		
		do
		{
			/*variabila nr numara cate "cuvinte" au fost extrase, iar poz pe ce
			pozitie a vectorului de coloane ne aflam*/
			nr++;

			if(nr == col[poz])
			{	
				strcat(print, p);
				strcat(print, ndel);
				poz++;
			}
			p = strtok(NULL, del);
		}while(p != NULL && poz < nr_col);
		/*verficam daca a fost scris ceva in sirul pentru printat, inainte 
		de a sterge din el ultimul delimitator*/
		if(strlen(print) > 1)
			print[strlen(print) - strlen(ndel) ] = '\0';

		printf("%s\n", print);

		free( matrice[i] );
		free(cpys);
	}
}

void freeall(char **matrice, char *del, char *newdel, int *col)
{
	free(del);
	free(newdel);
	free(matrice);
	free(col);
}