/* Całkowanie równania Schrodingera (przypadek jednowymiarowy; model 4 -- metoda Rungego-Kutty czwartego rzędu) */
/* Obserwacja: Ta metoda, pomimo swojego wyszukania, ma taką samą dyfuzję numeryczną, jak metoda dwustopniowa. */
/* Autor: Franciszek Humieja
   Wersja 1.0 (2017-VII-31) */
#include <stdio.h>
#include <complex.h>
#include <math.h>

int main(void) {
	const int N = 100;				/* rozmiar przestrzeni */
	char v_nazwa[] = "potencjal_1d.dat";		/* nazwa pliku z wartościami potencjału */
	char psi_nazwa[] = "schrod_rk4_1d.dat";		/* nazwa pliku z wartościami funkcji falowej */
	double v[N], v2[N], v3[N], v4[N];		/* potencjał (oraz jego potęgi kolejno od 2 do 4) */
	double complex psi[N], psi1[N];			/* funkcja falowa (w poprzednim i nowym kroku czasowym) */
	double complex k1, k2, k3, k4;			/* funkcje występujące w metodzie RK4 */
	FILE *fp;
	int i;
	int l2, l3, l4, p2, p3, p4;
	double dt  = 0.01;				/* krok czasowy; */
	double dt2 = pow(dt, 2);
	double dt3 = pow(dt, 3);
	double dx  = 1;					/* krok przestrzenny */
	double dx2 = pow(dx, 2);
	double dx4 = pow(dx2, 2);
	double dx6 = pow(dx2, 3);
	double dx8 = pow(dx4, 2);

	/* wczytanie odpowiedniego potencjału */
	fp = fopen(v_nazwa, "r");
	fread(v, sizeof(double), N, fp);
	fclose(fp);

	/* wyliczenie 2, 3 i 4 potęg potencjału */
	for(i=0; i<N; i++) {
		v2[i] = pow(v[i], 2);
		v3[i] = pow(v[i], 3);
		v4[i] = pow(v2[i], 2);
	}

	/* wczytanie funkcji falowej z poprzedniego kroku czasowego */
	fp = fopen(psi_nazwa, "r");
	fread(psi, sizeof(double complex), N, fp);
	fclose(fp);

	/* ewolucja funkcji falowej psi w czasie */
	for(i=1; i<N-1; i++) {
		l2 = (int)fmax(0,i-2);
		l3 = (int)fmax(0,i-3);
		l4 = (int)fmax(0,i-4);
		p2 = (int)fmin(N-1,i+2);
		p3 = (int)fmin(N-1,i+3);
		p4 = (int)fmin(N-1,i+4);

		k1 = (I*(psi[-1 + i] + psi[1 + i] - psi[i]*(2 + dx2*v[i])))/dx2;
		k2 = -((1/(2*dx4))*(dt*psi[l2] + 6*dt*psi[i] + 4*I*dx2*psi[i] - 4*dt*psi[1 + i] - 2*I*dx2*psi[1 + i] + dt*psi[p2] + 4*dt*dx2*psi[i]*v[i] + 2*I*dx4*psi[i]*v[i] - dt*dx2*psi[1 + i]*v[i] + dt*dx4*psi[i]*v2[i] - psi[-1 + i]*(4*dt + 2*I*dx2 + dt*dx2*v[-1 + i] + dt*dx2*v[i]) - dt*dx2*psi[1 + i]*v[1 + i]));
		k3 = (1/(4*dx6))*(I*((-dt2)*psi[l3] - 15*dt2*psi[-1 + i] - 8*I*dt*dx2*psi[-1 + i] + 4*dx4*psi[-1 + i] + 20*dt2*psi[i] + 12*I*dt*dx2*psi[i] - 8*dx4*psi[i] - 15*dt2*psi[1 + i] - 8*I*dt*dx2*psi[1 + i] + 4*dx4*psi[1 + i] + 6*dt2*psi[p2] + 2*I*dt*dx2*psi[p2] - dt2*psi[p3] - 6*dt2*dx2*psi[-1 + i]* v[-1 + i] - 2*I*dt*dx4*psi[-1 + i]*v[-1 + i] + dt2*dx2*psi[i]*v[-1 + i] - dt2*dx4*psi[-1 + i]*v2[-1 + i] - 6*dt2*dx2*psi[-1 + i]*v[i] - 2*I*dt*dx4*psi[-1 + i]*v[i] + 16*dt2*dx2*psi[i]*v[i] + 8*I*dt*dx4*psi[i]*v[i] - 4*dx6*psi[i]*v[i] - 6*dt2*dx2*psi[1 + i]*v[i] - 2*I*dt*dx4*psi[1 + i]*v[i] + dt2*dx2*psi[p2]*v[i] - dt2*dx4*psi[-1 + i]*v[-1 + i]*v[i] - dt2*dx4*psi[-1 + i]*v2[i] + 6*dt2*dx4*psi[i]*v2[i] + 2*I*dt*dx6*psi[i]*v2[i] - dt2*dx4*psi[1 + i]*v2[i] + dt2*dx6*psi[i]*v3[i] + dt*psi[l2]*(6*dt + 2*I*dx2 + dt*dx2*v[l2] + dt*dx2*v[-1 + i] + dt*dx2*v[i]) + dt2*dx2*psi[i]*v[1 + i] - 6*dt2*dx2*psi[1 + i]*v[1 + i] - 2*I*dt*dx4*psi[1 + i]*v[1 + i] + dt2*dx2*psi[p2]*v[1 + i] - dt2*dx4*psi[1 + i]*v[i]*v[1 + i] - dt2*dx4*psi[1 + i]*v2[1 + i] + dt2*dx2*psi[p2]*v[p2]));
		k4 = (1/(4*dx8))*(dt3*psi[l4] + 28*dt3*psi[l2] + 12*I*dt2*dx2*psi[l2] - 4*dt*dx4*psi[l2] - 56*dt3*psi[-1 + i] - 30*I*dt2*dx2*psi[-1 + i] + 16*dt*dx4*psi[-1 + i] + 4*I*dx6*psi[-1 + i] + 70*dt3*psi[i] + 40*I*dt2*dx2*psi[i] - 24*dt*dx4*psi[i] - 8*I*dx6*psi[i] - 56*dt3*psi[1 + i] - 30*I*dt2*dx2*psi[1 + i] + 16*dt*dx4*psi[1 + i] + 4*I*dx6*psi[1 + i] + 28*dt3*psi[p2] + 12*I*dt2*dx2*psi[p2] - 4*dt*dx4*psi[p2] - 8*dt3*psi[p3] - 2*I*dt2*dx2*psi[p3] + dt3*psi[p4] + 8*dt3*dx2*psi[l2]*v[l2] + 2*I*dt2*dx4*psi[l2]*v[l2] - dt3*dx2*psi[-1 + i]*v[l2] + dt3*dx4*psi[l2]*v2[l2] + 8*dt3*dx2*psi[l2]*v[-1 + i] + 2*I*dt2*dx4*psi[l2]*v[-1 + i] - 29*dt3*dx2*psi[-1 + i]*v[-1 + i] - 12*I*dt2*dx4*psi[-1 + i]* v[-1 + i] + 4*dt*dx6*psi[-1 + i]*v[-1 + i] + 8*dt3*dx2*psi[i]*v[-1 + i] + 2*I*dt2*dx4*psi[i]*v[-1 + i] - dt3*dx2*psi[1 + i]*v[-1 + i] + dt3*dx4*psi[l2]*v[l2]* v[-1 + i] + dt3*dx4*psi[l2]*v2[-1 + i] - 8*dt3*dx4*psi[-1 + i]*v2[-1 + i] - 2*I*dt2*dx6*psi[-1 + i]* v2[-1 + i] + dt3*dx4*psi[i]*v2[-1 + i] - dt3*dx6*psi[-1 + i]*v3[-1 + i] + 8*dt3*dx2*psi[l2]*v[i] + 2*I*dt2*dx4*psi[l2]*v[i] - 29*dt3*dx2*psi[-1 + i]*v[i] - 12*I*dt2*dx4*psi[-1 + i]*v[i] + 4*dt*dx6*psi[-1 + i]*v[i] + 64*dt3*dx2*psi[i]*v[i] + 32*I*dt2*dx4*psi[i]*v[i] - 16*dt*dx6*psi[i]*v[i] - 4*I*dx8*psi[i]*v[i] - 29*dt3*dx2*psi[1 + i]*v[i] - 12*I*dt2*dx4*psi[1 + i]*v[i] + 4*dt*dx6*psi[1 + i]*v[i] + 8*dt3*dx2*psi[p2]*v[i] + 2*I*dt2*dx4*psi[p2]*v[i] - dt3*dx2*psi[p3]*v[i] + dt3*dx4*psi[l2]*v[l2]*v[i] + dt3*dx4*psi[l2]*v[-1 + i]* v[i] - 8*dt3*dx4*psi[-1 + i]*v[-1 + i]*v[i] - 2*I*dt2*dx6*psi[-1 + i]*v[-1 + i]*v[i] + 2*dt3*dx4*psi[i]*v[-1 + i]* v[i] - dt3*dx6*psi[-1 + i]*v2[-1 + i]*v[i] + dt3*dx4*psi[l2]*v2[i] - 8*dt3*dx4*psi[-1 + i]*v2[i] - 2*I*dt2*dx6*psi[-1 + i]*v2[i] + 30*dt3*dx4*psi[i]*v2[i] + 12*I*dt2*dx6*psi[i]*v2[i] - 4*dt*dx8*psi[i]*v2[i] - 8*dt3*dx4*psi[1 + i]*v2[i] - 2*I*dt2*dx6*psi[1 + i]*v2[i] + dt3*dx4*psi[p2]*v2[i] - dt3*dx6*psi[-1 + i]*v[-1 + i]*v2[i] - dt3*dx6*psi[-1 + i]*v3[i] + 8*dt3*dx6*psi[i]*v3[i] + 2*I*dt2*dx8*psi[i]*v3[i] - dt3*dx6*psi[1 + i]*v3[i] + dt3*dx8*psi[i]*v4[i] - dt2*psi[l3]* (8*dt + 2*I*dx2 + dt*dx2*v[l3] + dt*dx2*v[l2] + dt*dx2*v[-1 + i] + dt*dx2*v[i]) - dt3*dx2*psi[-1 + i]*v[1 + i] + 8*dt3*dx2*psi[i]*v[1 + i] + 2*I*dt2*dx4*psi[i]*v[1 + i] - 29*dt3*dx2*psi[1 + i]*v[1 + i] - 12*I*dt2*dx4*psi[1 + i]*v[1 + i] + 4*dt*dx6*psi[1 + i]*v[1 + i] + 8*dt3*dx2*psi[p2]*v[1 + i] + 2*I*dt2*dx4*psi[p2]*v[1 + i] - dt3*dx2*psi[p3]*v[1 + i] + 2*dt3*dx4*psi[i]*v[i]*v[1 + i] - 8*dt3*dx4*psi[1 + i]*v[i]* v[1 + i] - 2*I*dt2*dx6*psi[1 + i]*v[i]*v[1 + i] + dt3*dx4*psi[p2]*v[i]*v[1 + i] - dt3*dx6*psi[1 + i]*v2[i]* v[1 + i] + dt3*dx4*psi[i]*v2[1 + i] - 8*dt3*dx4*psi[1 + i]* v2[1 + i] - 2*I*dt2*dx6*psi[1 + i]*v2[1 + i] + dt3*dx4*psi[p2]*v2[1 + i] - dt3*dx6*psi[1 + i]*v[i]* v2[1 + i] - dt3*dx6*psi[1 + i]*v3[1 + i] - dt3*dx2*psi[1 + i]*v[p2] + 8*dt3*dx2*psi[p2]*v[p2] + 2*I*dt2*dx4*psi[p2]*v[p2] - dt3*dx2*psi[p3]*v[p2] + dt3*dx4*psi[p2]*v[i]*v[p2] + dt3*dx4*psi[p2]*v[1 + i]* v[p2] + dt3*dx4*psi[p2]*v2[p2] - dt3*dx2*psi[p3]*v[p3]);

		psi1[i] = psi[i]+dt*(k1+2*k2+2*k3+k4)/6;
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
