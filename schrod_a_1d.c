/* Integrate the Schrodinger equation (1D case; model 1 -- approximating evolution
 * with sort of analytical solution) */
/* Author: Franciszek Humieja
 * Version 1.0 (2017-07-30) */
#include <stdio.h>
#include <complex.h>
#include <math.h>

int main(void) {
	const int N = 100;			/* space size */
	char v_nazwa[] = "potencjal_1d.dat";	/* filename with values of potential */
	char psi_nazwa[] = "schrod_a_1d.dat";	/* filename with values of wave function */
	double v[N];				/* potential */
	double complex psi[N];			/* wave function */
	double complex psi_s1[N], psi_s[N];	/* auxiliary function, component of evolution of the wave function */
	FILE *fp;
	int i,l;
	int IloscIteracji = 20;			/* number of iterations for approximating the value of psi_s */
	double dt = 0.01;			/* time step */

	/* read the potential */
	fp = fopen(v_nazwa, "r");
	fread(v, sizeof(double), N, fp);
	fclose(fp);

	/* read the wave function from the previous time step */
	fp = fopen(psi_nazwa, "r");
	fread(psi, sizeof(double complex), N, fp);
	fclose(fp);

	/* approximation with the iterative pattern the auxiliary function psi_s */
	for(l=0; l<=IloscIteracji; l++) {
		psi_s1[1] = psi_s[1];
		for(i=1; i<N-1; i++) {
			psi_s1[i+1] = psi_s[i+1];
			psi_s[i] = 2*cexp(-I*v[i]*dt)*psi[i]+0.5*I*dt*(psi_s1[i+1]+psi_s1[i-1]-2*psi_s1[i]);
		}
	}

	/* evolution of the wave function psi in time */
	for(i=1; i<N-1; i++)
		psi[i] = psi_s[i]-cexp(-I*v[i]*dt)*psi[i];

	/* print the value of wave function to the standard output */
	for(i=0; i<N; i++)
		printf("%d %g %g %g %g\n", i, creal(psi[i]), cimag(psi[i]), pow(cabs(psi[i]),2), v[i]);

	/* write the wave function from the current time step to the file */
	fp = fopen(psi_nazwa, "w");
	fwrite(psi, sizeof(double complex), N, fp);
	fclose(fp);

	return 0;
}
