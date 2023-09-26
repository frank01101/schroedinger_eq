/* Generowanie stanu początkowego -- stanu gaussowskiego unormowanego (przypadek jednowymiarowy) */
/* Autor: Franciszek Humieja
   Wersja 1.1 (2017-VIII-02) */
#include <stdio.h>
#include <complex.h>
#include <math.h>

int main(void) {
	const int N	= 100;	/* rozmiar przestrzeni */
	int x_s		= 20;	/* położenie środka paczki */
	double s	= 5;	/* szerokość paczki */
	double k	= -1;	/* wektor falowy */
	double complex psi[N];	/* funkcja falowa */
	int i;
	FILE *fp;

	for(i=0; i<N; i++) {
		if(i>0 && i<N-1)
			psi[i] = cexp(-pow(i-x_s,2)/(2*pow(s,2))-I*k*i);
		else
			psi[i] = 0;
		printf("%d %g %g %g\n", i, creal(psi[i]), cimag(psi[i]), pow(cabs(psi[i]),2));
	}

	fp = fopen("schrod_a_1d.dat", "w");
	fwrite(psi, sizeof(double complex), N, fp);
	fclose(fp);
	fp = fopen("schrod_e_1d.dat", "w");
	fwrite(psi, sizeof(double complex), N, fp);
	fclose(fp);
	fp = fopen("schrod_2s_1d.dat", "w");
	fwrite(psi, sizeof(double complex), N, fp);
	fclose(fp);
	fp = fopen("schrod_2s_5p_1d.dat", "w");
	fwrite(psi, sizeof(double complex), N, fp);
	fclose(fp);
	fp = fopen("schrod_rk4_1d.dat", "w");
	fwrite(psi, sizeof(double complex), N, fp);
	fclose(fp);
	fp = fopen("schrod_lw_1d.dat", "w");
	fwrite(psi, sizeof(double complex), N, fp);
	fclose(fp);
	fp = fopen("schrod_cn_1d.dat", "w");
	fwrite(psi, sizeof(double complex), N, fp);
	fclose(fp);

	return 0;
}
