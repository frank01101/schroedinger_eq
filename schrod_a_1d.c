/* Całkowanie równania Schrodingera (przypadek jednowymiarowy; model 1 -- rozwiązanie analityczne) */
/* Autor: Franciszek Humieja
   Wersja 1.0 (2017-VII-30) */
#include <stdio.h>
#include <complex.h>
#include <math.h>

int main(void) {
	const int N = 100;			/* rozmiar przestrzeni */
	char v_nazwa[] = "potencjal_1d.dat";	/* nazwa pliku z wartościami potencjału */
	char psi_nazwa[] = "schrod_a_1d.dat";	/* nazwa pliku z wartościami funkcji falowej */
	double v[N];				/* potencjał */
	double complex psi[N];			/* funkcja falowa */
	double complex psi_s1[N], psi_s[N];	/* funkcja pomocnicza, składnik funkcji falowej */
	FILE *fp;
	int i,l;
	int IloscIteracji = 20;			/* ilość iteracji na przybliżenie wartości psi_s */
	double dt = 0.01;			/* krok czasowy */

	/* wczytanie odpowiedniego potencjału */
	fp = fopen(v_nazwa, "r");
	fread(v, sizeof(double), N, fp);
	fclose(fp);

	/* wczytanie funkcji falowej z poprzedniego kroku czasowego */
	fp = fopen(psi_nazwa, "r");
	fread(psi, sizeof(double complex), N, fp);
	fclose(fp);

	/* przybliżenie wzorem iteracyjnym funkcji pomocniczej psi_s */
	for(l=0; l<=IloscIteracji; l++) {
		psi_s1[1] = psi_s[1];
		for(i=1; i<N-1; i++) {
			psi_s1[i+1] = psi_s[i+1];
			psi_s[i] = 2*cexp(-I*v[i]*dt)*psi[i]+0.5*I*dt*(psi_s1[i+1]+psi_s1[i-1]-2*psi_s1[i]);
		}
	}

	/* ewolucja funkcji falowej psi w czasie */
	for(i=1; i<N-1; i++)
		psi[i] = psi_s[i]-cexp(-I*v[i]*dt)*psi[i];

	/* wypisanie wartości funkcji falowej na wyjście */
	for(i=0; i<N; i++)
		printf("%d %g %g %g %g\n", i, creal(psi[i]), cimag(psi[i]), pow(cabs(psi[i]),2), v[i]);

	/* zapis funkcji falowej z obecnego kroku czasowego */
	fp = fopen(psi_nazwa, "w");
	fwrite(psi, sizeof(double complex), N, fp);
	fclose(fp);

	return 0;
}
