/* Generate initial state---two Gauss packets (1-dimensional case) */
/* Author: Franciszek Humieja
   Version 1.0 (2017-08-03) */
#include <stdio.h>
#include <complex.h>
#include <math.h>

int main(void) {
	const int N	= 100;	/* space size */
	int x_s1	= 20;	/* position of the packet 1 center */
	int x_s2	= 80;	/* position of the packet 2 center */
	double s1	= 5;	/* packet 1 width */
	double s2	= 5;	/* packet 2 width */
	double k1	= -1;	/* wave vector 1 */
	double k2	= 1;	/* wave vector 2 */
	double complex psi[N];	/* wave function */
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
