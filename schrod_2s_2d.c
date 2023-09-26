/* Całkowanie równania Schrodingera (przypadek dwuwymiarowy; model 2 -- metoda dwustopniowa jawna) */
/* Obserwacja: metoda niestabilna dla dt>0.01 przy dx==1 */
/* Autor: Franciszek Humieja
   Wersja 1.0 (2017-VIII-12) */
#include <stdio.h>
#include <complex.h>
#include <math.h>

int main(void) {
	const int NX = 100;				/* rozmiar przestrzeni */
	const int NY = 100;				/* rozmiar przestrzeni */
	char v_nazwa[] = "potencjal_2d.dat";		/* nazwa pliku z wartościami potencjału */
	char psi_nazwa[] = "schrod_2s_2d.dat";		/* nazwa pliku z wartościami funkcji falowej */
	double v[NX*NY];				/* potencjał */
	double complex psi[NX*NY], psih[NX*NY];		/* funkcja falowa */
	FILE *fp;
	int i,j;
	double dt = 0.01;				/* krok czasowy; */
	double dx = 1;					/* krok przestrzenny */

	/* wczytanie odpowiedniego potencjału */
	fp = fopen(v_nazwa, "r");
	fread(v, sizeof(double), NX*NY, fp);
	fclose(fp);

	/* wczytanie funkcji falowej z poprzedniego kroku czasowego */
	fp = fopen(psi_nazwa, "r");
	fread(psi, sizeof(double complex), NX*NY, fp);
	fclose(fp);

	/* ewolucja funkcji falowej psi w czasie */
	for(i=1; i<NX-1; i++)
		for(j=1; j<NY-1; j++)
			psih[i*NY+j] = (1-0.5*I*dt*v[i*NY+j])*psi[i*NY+j]+0.5*I*dt/pow(dx,2)*(psi[i*NY+j+1]+psi[i*NY+j-1]+psi[(i+1)*NY+j]+psi[(i-1)*NY+j]-4*psi[i*NY+j]);
	for(i=1; i<NX-1; i++)
		for(j=1; j<NY-1; j++)
			psi[i*NY+j] += I*dt/pow(dx,2)*(psih[i*NY+j+1]+psih[i*NY+j-1]+psih[(i+1)*NY+j]+psih[(i-1)*NY+j]-4*psih[i*NY+j])-I*dt*v[i*NY+j]*psih[i*NY+j];


	/* wypisanie wartości funkcji falowej na wyjście */
	for(i=0; i<NX; i++) {
		for(j=0; j<NY; j++)
			printf("%d %d %g %g %g %g\n", i, j, creal(psi[i*NY+j]), cimag(psi[i*NY+j]), pow(cabs(psi[i*NY+j]),2), v[i*NY+j]);
		printf("\n");
	}

	/* zapis funkcji falowej z obecnego kroku czasowego */
	fp = fopen(psi_nazwa, "w");
	fwrite(psi, sizeof(double complex), NX*NY, fp);
	fclose(fp);

	return 0;
}
