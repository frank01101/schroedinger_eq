/* Całkowanie równania Schrodingera (przypadek jednowymiarowy; model 5 -- metoda Laxa-Wendroffa) */
/* Obserwacja: ta metoda ma w tym przypadku bardzo dużą dyspersję. Rozwiązanie zachowuje się inaczej niż pozostałe (bo było ono nieco „kombinowane”). */
/* Autor: Franciszek Humieja
   Wersja 1.0 (2017-VIII-02) */
#include <stdio.h>
#include <complex.h>
#include <math.h>

int main(void) {
	const int N = 100;			/* rozmiar przestrzeni */
	char v_nazwa[] = "potencjal_1d.dat";	/* nazwa pliku z wartościami potencjału */
	char psi_nazwa[] = "schrod_lw_1d.dat";	/* nazwa pliku z wartościami funkcji falowej */
	double v[N];				/* potencjał */
	double complex psi[N], psih[N];		/* funkcja falowa */
	int l1, l2, p2;
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
	for(i=0; i<N-1; i++) {
		l1 = (int)fmax(0,i-1);
		p2 = (int)fmin(N-1,i+2);
		psih[i] = 0.5*(psi[i]+psi[i+1])+0.25*I*dt/pow(dx,2)*(psi[p2]-psi[i+1]-psi[i]+psi[l1])-0.25*I*dt*(v[i]*psi[i]+v[i+1]*psi[i+1]);
	}
	for(i=1; i<N-1; i++) {
		l2 = (i-2+N)%N;	/* warunek brzegowy cykliczny, bo psih[0]!=0, więc dla i=1 odnoszę do psih[N-1]==0 */
		psi[i] += 0.5*I*dt/pow(dx,2)*(psih[i+1]-psih[i]-psih[i-1]+psih[l2])-0.5*I*dt*v[i]*(psih[i-1]+psih[i]);
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
