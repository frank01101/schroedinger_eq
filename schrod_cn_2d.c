/* Integrate Schrodinger equation (2D case; model 3 -- second-order implicit method (Cranck-Nicholson)
 * with solving the system of equations using the Jacobi iterative method) */
/* Observation: absolutely stable method */
/* Author: Franciszek Humieja
 * Version 1.0 (2017-08-12) */
#include <stdio.h>
#include <complex.h>
#include <math.h>

int main(void) {
	const int NX = 100;					/* space size */
	const int NY = 100;					/* space size */
	char v_nazwa[] = "potencjal_2d.dat";			/* filename with values of potential */
	char psi_nazwa[] = "schrod_cn_2d.dat";			/* filename with values of wave function */
	double v[NX*NY];					/* potential */
	double complex psi[NX*NY], psi_k[NX*NY], psi_k1[NX*NY];	/* wave function */
	FILE *fp;                                                                                           
	int k,i,j;                                                                                          
	double dt = 0.3;					/* time step */
	double dx = 1;						/* space step */
	int K = 20;						/* number of iterations in the Jacobi method */
	double complex a,b,w;

	/* read the potential */
	fp = fopen(v_nazwa, "r");
	fread(v, sizeof(double), NX*NY, fp);
	fclose(fp);

	/* read the wave function from the previous time step */
	fp = fopen(psi_nazwa, "r");
	fread(psi, sizeof(double complex), NX*NY, fp);
	fclose(fp);

	/* copy boundary values from the previous time step (useful if they were !=0) */
	/* for(i=0; i<NX; i++) {
	 *	psi_k1[i*NY] = psi_k[i*NY] = psi[i*NY];
	 *	psi_k1[i*NY+NY-1] = psi_k[i*NY+NY-1] = psi[i*NY+NY-1];
	 * }
	 * for(j=0; j<NY; j++) {
	 *	psi_k1[j] = psi_k[j] = psi[j];
	 *	psi_k1[(NX-1)*NY+j] = psi_k[(NX-1)*NY+j] = psi[(NX-1)*NY+j];
	 * } */

	/* finding a solution to the system of equations using the Jacobi iterative method;
	 * five-diagonal matrix -- the method comes down to a simple formula */
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

	/* print the value of wave function to the standard output */
	for(i=0; i<NX; i++) {
		for(j=0; j<NY; j++)
			printf("%d %d %g %g %g %g\n", i, j, creal(psi_k1[i*NY+j]), cimag(psi_k1[i*NY+j]), pow(cabs(psi_k1[i*NY+j]),2), v[i*NY+j]);
		printf("\n");
	}

	/* write the wave function from the current time step to the file */
	fp = fopen(psi_nazwa, "w");
	fwrite(psi_k1, sizeof(double complex), NX*NY, fp);
	fclose(fp);

	return 0;
}
