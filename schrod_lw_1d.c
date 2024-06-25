/* Integrate the Schrodinger equation (1D case; model 5 -- Lax-Wendroff method) */
/* Observation: this method has very high dispersion in this case. The solution behaves
 * differently than the others (because it was a bit "over-engineered"). */
/* Author: Franciszek Humieja
 * Version 1.0 (2017-08-02) */
#include <stdio.h>
#include <complex.h>
#include <math.h>

int main(void) {
	const int N = 100;			/* space size */
	char v_nazwa[] = "potencjal_1d.dat";	/* filename with values of potential */
	char psi_nazwa[] = "schrod_lw_1d.dat";	/* filename with values of wave function */
	double v[N];				/* potential */
	double complex psi[N], psih[N];		/* wave function */
	int l1, l2, p2;                                                                     
	FILE *fp;                                                                           
	int i;                                  
	double dt = 0.01;			/* time step */
	double dx = 1;				/* space step */

	/* read the potential */
	fp = fopen(v_nazwa, "r");
	fread(v, sizeof(double), N, fp);
	fclose(fp);

	/* read the wave function from the previous time step */
	fp = fopen(psi_nazwa, "r");
	fread(psi, sizeof(double complex), N, fp);
	fclose(fp);

	/* evolution of the wave function psi in time */
	for(i=0; i<N-1; i++) {
		l1 = (int)fmax(0,i-1);
		p2 = (int)fmin(N-1,i+2);
		psih[i] = 0.5*(psi[i]+psi[i+1])+0.25*I*dt/pow(dx,2)*(psi[p2]-psi[i+1]-psi[i]+psi[l1])-0.25*I*dt*(v[i]*psi[i]+v[i+1]*psi[i+1]);
	}
	for(i=1; i<N-1; i++) {
		l2 = (i-2+N)%N;	/* cyclic boundary condition, because psih[0]!=0, so for i=1 we refer to psih[N-1]==0 */
		psi[i] += 0.5*I*dt/pow(dx,2)*(psih[i+1]-psih[i]-psih[i-1]+psih[l2])-0.5*I*dt*v[i]*(psih[i-1]+psih[i]);
	}

	/* print the value of wave function to the standard output */
	for(i=0; i<N; i++)
		printf("%d %g %g %g %g\n", i, creal(psi[i]), cimag(psi[i]), pow(cabs(psi[i]),2), v[i]);

	/* write the wave function from the current time step to the file */
	fp = fopen(psi_nazwa, "w");
	fwrite(psi, sizeof(double complex), N, fp);
	fclose(fp);

	return 0;
}
