/* Integration of the Schrodinger equation (two-dimensional case; model 2a -- two-step explicit method
 * using the nine-point formula for Laplacian) */
/* Observation: unstable method for dt>0.01 with dx==1 (similar to the five-point pattern) */
/* Author: Franciszek Humieja
 * Version 1.0 (2017-08-12) */
#include <stdio.h>
#include <complex.h>
#include <math.h>

int main(void) {
	const int NX = 100;				/* space size */
	const int NY = 100;				/* space size */
	char v_nazwa[] = "potencjal_2d.dat";		/* filename with values of potential */
	char psi_nazwa[] = "schrod_2s_2d_9p.dat";	/* filename with values of wave function */
	double v[NX*NY];				/* potential */
	double complex psi[NX*NY], psih[NX*NY];		/* wave function */
	FILE *fp;                                                                                   
	int i,j;                                                                                    
	int il2,ip2,jl2,jp2;                            
	double dt = 0.01;				/* time step */
	double dx = 1;					/* space step */

	/* read the potential */
	fp = fopen(v_nazwa, "r");
	fread(v, sizeof(double), NX*NY, fp);
	fclose(fp);

	/* read the wave function from the previous time step */
	fp = fopen(psi_nazwa, "r");
	fread(psi, sizeof(double complex), NX*NY, fp);
	fclose(fp);

	/* evolution of the wave function psi in time */
	for(i=1; i<NX-1; i++)
		for(j=1; j<NY-1; j++) {
			il2 = (int)fmax(j,(i-2)*NY+j);
			ip2 = (int)fmin((NX-1)*NY+j,(i+2)*NY+j);
			jl2 = (int)fmax(i*NY,i*NY+j-2);
			jp2 = (int)fmin(i*NY+NY-1,i*NY+j+2);
			psih[i*NY+j] = (1-0.5*I*dt*v[i*NY+j])*psi[i*NY+j]+0.5*I*dt/pow(dx,2)*(-1/(double)12*(psi[jp2]+psi[jl2]+psi[ip2]+psi[il2])+4/(double)3*(psi[i*NY+j+1]+psi[i*NY+j-1]+psi[(i+1)*NY+j]+psi[(i-1)*NY+j])-5*psi[i*NY+j]);
		}
	for(i=1; i<NX-1; i++)
		for(j=1; j<NY-1; j++)
			psi[i*NY+j] += I*dt/pow(dx,2)*(-1/(double)12*(psih[jp2]+psih[jl2]+psih[ip2]+psih[il2])+4/(double)3*(psih[i*NY+j+1]+psih[i*NY+j-1]+psih[(i+1)*NY+j]+psih[(i-1)*NY+j])-5*psih[i*NY+j])-I*dt*v[i*NY+j]*psih[i*NY+j];

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
