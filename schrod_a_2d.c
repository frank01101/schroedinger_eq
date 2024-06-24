/* Integrate Schrodinger equations (2D case; model 1 -- analytical solution) */
/* Observation: method unstable for dt>0.1 with dx==1 */
/* Author: Franciszek Humieja
   Version 1.0 (2017-08-12) */
#include <stdio.h>
#include <complex.h>
#include <math.h>

int main(void) {
	const int NX = 100;				/* space size */
	const int NY = 100;				/* space size */
	char v_nazwa[] = "potencjal_2d.dat";		/* filename with values of potential */
	char psi_nazwa[] = "schrod_a_2d.dat";		/* filename with values of wave function */
	double v[NX*NY];				/* potential */
	double complex psi[NX*NY];			/* wave function */
	double complex psi_s1[NX*NY], psi_s[NX*NY];	/* auxiliary function, wave function component */
	FILE *fp;
	int i,j,l;
	int L = 20;					/* number of iterations for approximation of the psi_s value */
	double dt = 0.1;				/* time step */
	double dx = 1;					/* space step */

	/* read the potential */
	fp = fopen(v_nazwa, "r");
	fread(v, sizeof(double), NX*NY, fp);
	fclose(fp);

	/* read the wave function from the previous time step */
	fp = fopen(psi_nazwa, "r");
	fread(psi, sizeof(double complex), NX*NY, fp);
	fclose(fp);

	/* approximation of the auxiliary function psi_s with the iterative pattern */
	for(l=0; l<=L; l++) {
		for(i=1; i<NX-1; i++)
			for(j=1; j<NY-1; j++)
				psi_s[i*NY+j] = psi_s1[i*NY+j];
		for(i=1; i<NX-1; i++)
			for(j=1; j<NY-1; j++)
				psi_s1[i*NY+j] = 2*cexp(-I*v[i*NY+j]*dt)*psi[i*NY+j]+0.5*I*dt/pow(dx,2)*(psi_s[(i+1)*NY+j]+psi_s[(i-1)*NY+j]+psi_s[i*NY+j+1]+psi_s[i*NY+j-1]-4*psi_s[i*NY+j]);
	}

	/* evolution of the wave function psi in time */
	for(i=1; i<NX-1; i++)
		for(j=1; j<NY-1; j++)
			psi[i*NY+j] = psi_s1[i*NY+j]-cexp(-I*v[i*NY+j]*dt)*psi[i*NY+j];

	/* print the value of wave function to the standard output */
	for(i=0; i<NX; i++) {
		for(j=0; j<NY; j++)
			printf("%d %d %g %g %g %g\n", i, j, creal(psi[i*NY+j]), cimag(psi[i*NY+j]), pow(cabs(psi[i*NY+j]),2), v[i*NY+j]);
		printf("\n");
	}

	/* write the wave function from the current time step to the file */
	fp = fopen(psi_nazwa, "w");
	fwrite(psi, sizeof(double complex), NX*NY, fp);
	fclose(fp);

	return 0;
}
