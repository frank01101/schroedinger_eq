/* Integrate the Schrodinger equation (1D case; model 6 -- second-order implicit
 * method (Cranck-Nicholson) with solution of the system of equations using
 * the Jacobi iterative method) */
/* Observation: the method is unstable for dt >= 0.03 and dx = 1 */
/* Author: Franciszek Humieja
 Version 1.0 (2017-08-02) */
#include <stdio.h>
#include <complex.h>
#include <math.h>

int main(void) {
	const int N = 100;			/* space size */
	char v_nazwa[] = "potencjal_1d.dat";	/* filename with values of potential */
	char psi_nazwa[] = "schrod_cn_1d.dat";	/* filename with values of wave function */
	double v[N];				/* potential */
	double complex psi[N], psi1[N];		/* wave function */
	double complex psi1_temp, psi1l;                                                    
	FILE *fp;                                                                           
	int k, i;                               
	double dt = 0.01;			/* time step */
	double dx = 1;				/* space step */
	int K = 20;				/* number of iterations in the Jacobi method */
	double complex a, b, d, w;
	int el, e;

	/* read the potential */
	fp = fopen(v_nazwa, "r");
	fread(v, sizeof(double), N, fp);
	fclose(fp);

	/* read the wave function from the previous time step */
	fp = fopen(psi_nazwa, "r");
	fread(psi, sizeof(double complex), N, fp);
	fclose(fp);

	/* finding a solution to the system of equations using the Jacobi
	 * iterative method; matrix A is three-diagonal, the entire method
	 * reduces to a simple formula with one loop along the spatial coordinate x */
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

	/* print the value of wave function to the standard output */
	for(i=0; i<N; i++)
		printf("%d %g %g %g %g\n", i, creal(psi1[i]), cimag(psi1[i]), pow(cabs(psi1[i]),2), v[i]);

	/* write the wave function from the current time step to the file */
	fp = fopen(psi_nazwa, "w");
	fwrite(psi1, sizeof(double complex), N, fp);
	fclose(fp);

	return 0;
}
