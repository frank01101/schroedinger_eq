/* Całkowanie równania Schrodingera (przypadek dwuwymiarowy; model 3 --- metoda niejawna drugiego rzędu (Crancka-Nicholsona) z rozwiązaniem układu równań metodą iteracyjną Jacobiego) */
/* Obserwacja: metoda bezwzględnie stabilna */
/* Autor: Franciszek Humieja
   Wersja 1.0 (2017-VIII-12) */
#include <stdio.h>
#include <complex.h>
#include <math.h>

int main(void) {
	const int NX = 100;					/* rozmiar przestrzeni */
	const int NY = 100;					/* rozmiar przestrzeni */
	char v_nazwa[] = "potencjal_2d.dat";			/* nazwa pliku z wartościami potencjału */
	char psi_nazwa[] = "schrod_cn_2d.dat";			/* nazwa pliku z wartościami funkcji falowej */
	double v[NX*NY];					/* potencjał */
	double complex psi[NX*NY], psi_k[NX*NY], psi_k1[NX*NY];	/* funkcja falowa */
	FILE *fp;
	int k,i,j;
	double dt = 0.3;					/* krok czasowy; */
	double dx = 1;						/* krok przestrzenny */
	int K = 20;						/* ilość iteracji w metodzie Jacobiego */
	double complex a,b,w;

	/* wczytanie odpowiedniego potencjału */
	fp = fopen(v_nazwa, "r");
	fread(v, sizeof(double), NX*NY, fp);
	fclose(fp);

	/* wczytanie funkcji falowej z poprzedniego kroku czasowego */
	fp = fopen(psi_nazwa, "r");
	fread(psi, sizeof(double complex), NX*NY, fp);
	fclose(fp);

	/* przekopiowanie wartości brzegowych z poprzedniego kroku czasowego (przydatne, gdyby były !=0) */
	/*for(i=0; i<NX; i++) {
		psi_k1[i*NY] = psi_k[i*NY] = psi[i*NY];
		psi_k1[i*NY+NY-1] = psi_k[i*NY+NY-1] = psi[i*NY+NY-1];
	}
	for(j=0; j<NY; j++) {
		psi_k1[j] = psi_k[j] = psi[j];
		psi_k1[(NX-1)*NY+j] = psi_k[(NX-1)*NY+j] = psi[(NX-1)*NY+j];
	}*/

	/* znalezienie rozwiązania układu równań metodą iteracyjną Jacobiego;
	   macierz pięcioprzekątniowa --- metoda sprowadza się do prostego wzoru */
	for(k=1; k<=K; k++) {
		for(i=1; i<NX-1; i++)
			for(j=1; j<NY-1; j++)
				psi_k[i*NY+j] = psi_k1[i*NY+j];
		for(i=1; i<NX-1; i++)
			for(j=1; j<NY-1; j++) {
				a = pow(dx,2)*(2*I/dt-v[i*NY+j])-4;
				b = pow(dx,2)*(2*I/dt+v[i*NY+j])+4;
				w = -psi[(i-1)*NY+j]-psi[(i+1)*NY+j]-psi[i*NY+j-1]-psi[i*NY+j+1]+b*psi[i*NY+j];
				psi_k1[i*NY+j] = (1/a)*(w-psi_k[(i-1)*NY+j]-psi_k[(i+1)*NY+j]-psi_k[i*NY+j-1]-psi_k[i*NY+j+1]);
			}
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
