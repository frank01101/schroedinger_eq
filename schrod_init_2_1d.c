/* Generowanie stanu początkowego -- dwóch paczek gaussowskich (przypadek jednowymiarowy) */
/* Autor: Franciszek Humieja
   Wersja 1.0 (2017-VIII-03) */
#include <stdio.h>
#include <complex.h>
#include <math.h>

int main(void) {
	const int N	= 100;	/* rozmiar przestrzeni */
	int x_s1	= 20;	/* położenie środka paczki 1 */
	int x_s2	= 80;	/* położenie środka paczki 2 */
	double s1	= 5;	/* szerokość paczki 1 */
	double s2	= 5;	/* szerokość paczki 2 */
	double k1	= -1;	/* wektor falowy 1 */
	double k2	= 1;	/* wektor falowy 2 */
	double complex psi[N];	/* funkcja falowa */
	int i;
	FILE *fp;

	for(i=0; i<N; i++) {
		if(i>0 && i<N-1)
			psi[i] = cexp(-pow(i-x_s1,2)/(2*pow(s1,2))-I*k1*i)+cexp(-pow(i-x_s2,2)/(2*pow(s2,2))-I*k2*i);
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
