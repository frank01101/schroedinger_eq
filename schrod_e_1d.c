/* Całkowanie równania Schrodingera (przypadek jednowymiarowy; model 2 -- metoda Eulera) */
/* Obserwacja: jest niestabilna dla potencjału różnego od 0 */
/* Autor: Franciszek Humieja
   Wersja 1.0 (2017-VII-30) */
#include <stdio.h>
#include <complex.h>
#include <math.h>

int main(void) {
	const int N = 100;			/* rozmiar przestrzeni */
	char v_nazwa[] = "potencjal_1d.dat";	/* nazwa pliku z wartościami potencjału */
	char psi_nazwa[] = "schrod_e_1d.dat";	/* nazwa pliku z wartościami funkcji falowej */
	double v[N];				/* potencjał */
	double complex psi[N];			/* funkcja falowa */
	double complex psi_temp, psi1 = 0;
	FILE *fp;
	int i;
	double dt = 0.01;			/* krok czasowy; dt<=dx^2/(2+dx^4*v_max^2/8) */
	double dx = 1;				/* krok przestrzenny */

	/* wczytanie odpowiedniego potencjału */
	fp = fopen(v_nazwa, "r");
	fread(v, sizeof(double), N, fp);
	fclose(fp);

	/* wczytanie funkcji falowej z poprzedniego kroku czasowego */
	fp = fopen(psi_nazwa, "r");
	fread(psi, sizeof(double complex), N, fp);
	fclose(fp);

	/* ewolucja funkcji falowej psi w czasie */
	for(i=1; i<N-1; i++) {
		psi_temp = psi[i];
		psi[i] = (1-I*dt*v[i])*psi[i]+I*dt/pow(dx,2)*(psi[i+1]+psi1-2*psi[i]);
		psi1 = psi_temp;
	}

	/* wypisanie wartości funkcji falowej na wyjście */
	for(i=0; i<N; i++)
		printf("%d %g %g %g %g\n", i, creal(psi[i]), cimag(psi[i]), pow(cabs(psi[i]),2), v[i]);

	/* zapis funkcji falowej z obecnego kroku czasowego */
	fp = fopen(psi_nazwa, "w");
	fwrite(psi, sizeof(double complex), N, fp);
	fclose(fp);

	return 0;
}
