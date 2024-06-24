/* Integrate Schrodinger equation (2D case; model 3a -- second-order implicit method (Cranck-Nicholson)
 * with solving the system of equations using the Jacobi iterative method) */
/* Author: Franciszek Humieja
   Version 1.0 (2017-08-11) */
#include <stdio.h>
#include <complex.h>
#include <math.h>

/* Heaviside function */
int t(int a) {
	if(a>=0)
		return 1;
	else
		return 0;
}

/* Kronecker delta */
int d(int a, int b) {
	if(a==b)
		return 1;
	else
		return 0;
}

int main(void) {
	const int NX = 100;					/* space size */
	const int NY = 100;					/* space size */
	char v_nazwa[] = "potencjal_2d.dat";			/* filename with values of potential */
	char psi_nazwa[] = "schrod_cn_2d.dat";			/* filename with values of wave function */
	double v[NX*NY];					/* potential */
	double complex psi[NX*NY], psi_k[NX*NY], psi_k1[NX*NY];	/* wave function */
	FILE *fp;                                                                                           
	int k,i,j;                                                                                          
	double dt = 0.1;					/* time step */
	double dx = 1;						/* space step */
	int K = 20;						/* number of iterations in the Jacobi method */
	int il,jl,ip,jp;
	double complex a,b,w;
	int c;

	/* read the potential */
	fp = fopen(v_nazwa, "r");
	fread(v, sizeof(double), NX*NY, fp);
	fclose(fp);

	/* read the wave function from the previous time step */
	fp = fopen(psi_nazwa, "r");
	fread(psi, sizeof(double complex), NX*NY, fp);
	fclose(fp);

	/* finding a solution to the system of equations using the Jacobi iterative method; */
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
