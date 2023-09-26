/* Całkowanie równania Schrodingera (przypadek dwuwymiarowy; model 3a --- metoda niejawna drugiego rzędu (Crancka-Nicholsona) z rozwiązaniem układu równań metodą iteracyjną Jacobiego) */
/* Autor: Franciszek Humieja
   Wersja 1.0 (2017-VIII-11) */
#include <stdio.h>
#include <complex.h>
#include <math.h>

/* funkcja Heaviside'a */
int t(int a) {
	if(a>=0)
		return 1;
	else
		return 0;
}

/* delta Kroneckera */
int d(int a, int b) {
	if(a==b)
		return 1;
	else
		return 0;
}

int main(void) {
	const int NX = 100;					/* rozmiar przestrzeni */
	const int NY = 100;					/* rozmiar przestrzeni */
	char v_nazwa[] = "potencjal_2d.dat";			/* nazwa pliku z wartościami potencjału */
	char psi_nazwa[] = "schrod_cn_2d.dat";			/* nazwa pliku z wartościami funkcji falowej */
	double v[NX*NY];					/* potencjał */
	double complex psi[NX*NY], psi_k[NX*NY], psi_k1[NX*NY];	/* funkcja falowa */
	FILE *fp;
	int k,i,j;
	double dt = 0.1;			/* krok czasowy; */
	double dx = 1;				/* krok przestrzenny */
	int K = 20;				/* ilość iteracji w metodzie Jacobiego */
	int il,jl,ip,jp;
	double complex a,b,w;
	int c;

	/* wczytanie odpowiedniego potencjału */
	fp = fopen(v_nazwa, "r");
	fread(v, sizeof(double), NX*NY, fp);
	fclose(fp);

	/* wczytanie funkcji falowej z poprzedniego kroku czasowego */
	fp = fopen(psi_nazwa, "r");
	fread(psi, sizeof(double complex), NX*NY, fp);
	fclose(fp);

	/* znalezienie rozwiązania układu równań metodą iteracyjną Jacobiego */
	for(k=1; k<=K; k++) {
		for(i=0; i<NX*NY; i++) {
			il = (int)fmax(0,i-1);
			jl = (int)fmax(0,i-NY);
			ip = (int)fmin(NX*NY-1,i+1);
			jp = (int)fmin(NX*NY-1,i+NY);
			if(i%NY==0 || i%NY==NY-1 || i/NY==0 || i/NY==NX-1) {
				a = 1;
				b = 1;
				c = 0;
			}
			else {
				a = pow(dx,2)*(2*I/dt-v[i])-4;
				b = pow(dx,2)*(2*I/dt+v[i])+4;
				c = 1;
			}
			w = -c*(psi[il]+psi[ip]+psi[jl]+psi[jp])+b*psi[i];
			psi_k1[i] = (1/a)*(w-t(i-1-NY)*t((NX-1)*NY-i-1)*(1-d(i%NY,NY-1))*psi_k[il]-t(i-NY)*t((NX-1)*NY-i-1)*(1-d(i%NY,0)-d(i%NY,NY-1))*psi_k[jl]-t(i-NY)*t((NX-1)*NY-i-2)*(1-d(i%NY,0))*psi_k[ip]-t(i-NY)*t((NX-1)*NY-i-1)*(1-d(i%NY,0)-d(i%NY,NY-1))*psi_k[jp]);
		}
		for(i=0; i<NX*NY; i++)
			psi_k[i] = psi_k1[i];
	}

	/* wypisanie wartości funkcji falowej na wyjście */
	for(i=0; i<NX; i++) {
		for(j=0; j<NY; j++)
			printf("%d %d %g %g %g %g\n", i, j, creal(psi_k1[i*NY+j]), cimag(psi_k1[i*NY+j]), pow(cabs(psi_k1[i*NY+j]),2), v[i*NY+j]);
		printf("\n");
	}

	/* zapis funkcji falowej z obecnego kroku czasowego */
	fp = fopen(psi_nazwa, "w");
	fwrite(psi_k1, sizeof(double complex), NX*NY, fp);
	fclose(fp);

	return 0;
}
