/* Całkowanie równania Schrodingera (przypadek jednowymiarowy; model 6 --- metoda niejawna drugiego rzędu (Crancka-Nicholsona) z rozwiązaniem układu równań metodą iteracyjną Jacobiego) */
/* Obserwacja: metoda jest niestabilna dla dt >= 0.03 i dx = 1 */
/* Autor: Franciszek Humieja
   Wersja 1.0 (2017-VIII-02) */
#include <stdio.h>
#include <complex.h>
#include <math.h>

int main(void) {
	const int N = 100;			/* rozmiar przestrzeni */
	char v_nazwa[] = "potencjal_1d.dat";	/* nazwa pliku z wartościami potencjału */
	char psi_nazwa[] = "schrod_cn_1d.dat";	/* nazwa pliku z wartościami funkcji falowej */
	double v[N];				/* potencjał */
	double complex psi[N], psi1[N];		/* funkcja falowa */
	double complex psi1_temp, psi1l;
	FILE *fp;
	int k, i;
	double dt = 0.01;			/* krok czasowy; */
	double dx = 1;				/* krok przestrzenny */
	int K = 20;				/* ilość iteracji w metodzie Jacobiego */
	double complex a, b, d, w;
	int el, e;

	/* wczytanie odpowiedniego potencjału */
	fp = fopen(v_nazwa, "r");
	fread(v, sizeof(double), N, fp);
	fclose(fp);

	/* wczytanie funkcji falowej z poprzedniego kroku czasowego */
	fp = fopen(psi_nazwa, "r");
	fread(psi, sizeof(double complex), N, fp);
	fclose(fp);

	/* znalezienie rozwiązania układu równań metodą iteracyjną Jacobiego;
	   macierz A jest trójprzekątniowa, cała metoda redukuje się do prostego wzoru z jedną pętlą po współrzędnej przestrzennej x */
	for(k=1; k<=K; k++) {
		psi1l = psi1[0];
		for(i=1; i<N-1; i++) {
			a = pow(dx,2)*(2*I/dt-v[i])-2;
			b = pow(dx,2)*(2*I/dt+v[i])+2;
			d = 1/a;
			w = -psi[i+1]+b*psi[i]-psi[i-1];
			if(i==1)   el = 0;
			else       el = 1;
			if(i==N-2) e  = 0;
			else       e  = 1;
			psi1_temp = psi1[i];
			psi1[i]   = d*(w-el*psi1l-e*psi[i+1]);
			psi1l     = psi1_temp;
		}
	}

	/* wypisanie wartości funkcji falowej na wyjście */
	for(i=0; i<N; i++)
		printf("%d %g %g %g %g\n", i, creal(psi1[i]), cimag(psi1[i]), pow(cabs(psi1[i]),2), v[i]);

	/* zapis funkcji falowej z obecnego kroku czasowego */
	fp = fopen(psi_nazwa, "w");
	fwrite(psi1, sizeof(double complex), N, fp);
	fclose(fp);

	return 0;
}
