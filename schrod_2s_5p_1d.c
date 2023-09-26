/* Całkowanie równania Schrodingera (przypadek jednowymiarowy; model 3a -- metoda dwustopniowa jawna ze wzorem pięciopunktowym na laplasjan) */
/* Obserwacja: ta metoda ma większą dyfuzję numeryczną niż metoda dwustopniowa ze wzorem trójpunktowym. */
/* Autor: Franciszek Humieja
   Wersja 1.0 (2017-VII-31) */
#include <stdio.h>
#include <complex.h>
#include <math.h>

int main(void) {
	const int N = 100;			/* rozmiar przestrzeni */
	char v_nazwa[] = "potencjal_1d.dat";	/* nazwa pliku z wartościami potencjału */
	char psi_nazwa[] = "schrod_2s_5p_1d.dat";	/* nazwa pliku z wartościami funkcji falowej */
	double v[N];				/* potencjał */
	double complex psi[N], psih[N];		/* funkcja falowa */
	int l2, p2;
	FILE *fp;
	int i;
	double dt = 0.01;			/* krok czasowy; */
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
		l2 = (int)fmax(0,i-2);
		p2 = (int)fmin(N-1,i+2);
		psih[i] = (1-0.5*I*dt*v[i])*psi[i]+0.5*I*dt/pow(dx,2)*(-1/(double)12*(psi[l2]+psi[p2])+4/(double)3*(psi[i-1]+psi[i+1])-5/(double)2*psi[i]);
	}
	for(i=1; i<N-1; i++) {
		l2 = (int)fmax(0,i-2);
		p2 = (int)fmin(N-1,i+2);
		psi[i] += I*dt/pow(dx,2)*(-1/(double)12*(psih[l2]+psih[p2])+4/(double)3*(psih[i-1]+psih[i+1])-5/(double)2*psih[i])-I*dt*v[i]*psih[i];
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
