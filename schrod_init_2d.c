/* Generate the initial state---Gauss packet (2-dimensional case) */
/* Author: Franciszek Humieja
   Version 1.1 (2017-08-18) */
#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>

int main(int argc, char **argv) {
	int iloscPaczek	= 1;			/* number of packets; to be chosen by the user */
	const int NX	= 100;			/* space size */
	const int NY	= 100;			/* space size */
	int x_s1	= (int)(0.2*NX);	/* position of the packet 1 center */
	int y_s1	= (int)(0.5*NY);	/* position of the packet 1 center */
	int x_s2	= (int)(0.8*NX);	/* position of the packet 2 center */
	int y_s2	= (int)(0.5*NY);	/* position of the packet 2 center */
	int x_s3	= (int)(0.6*NX);	/* position of the packet 3 center */
	int y_s3	= (int)(0.8*NY);	/* position of the packet 3 center */
	int x_s4	= (int)(0.6*NX);	/* position of the packet 4 center */
	int y_s4	= (int)(0.2*NY);	/* position of the packet 4 center */
	double s1	= (double)NX/20;	/* packet 1 width */
	double s2	= (double)NX/20;	/* packet 2 width */
	double s3	= (double)NX/20;	/* packet 3 width */
	double s4	= (double)NX/20;	/* packet 4 width */
	double kx1	= 1;			/* wave vector 1 */
	double ky1	= 0;			/* wave vector 1 */
	double kx2	= -1;			/* wave vector 2 */
	double ky2	= 0;			/* wave vector 2 */
	double kx3	= -0.5;			/* wave vector 3 */
	double ky3	= -sqrt(3)/2;		/* wave vector 3 */
	double kx4	= -0.5;			/* wave vector 4 */
	double ky4	= sqrt(3)/2;		/* wave vector 4 */
	double complex psi[NX*NY];		/* wave function */
	int i,j;
	FILE *fp;

	/* read the packet number, given as the first command-line argument */
	if(argc>=2)
		iloscPaczek = atoi(argv[1]);

	/* creating the initial state */
	for(i=0; i<NX; i++) {
		for(j=0; j<NY; j++) {
			if(i>0 && i<NX-1 && j>0 && j<NY-1) {
				psi[i*NY+j] = cexp((-pow(i-x_s1,2)-pow(j-y_s1,2))/(2*pow(s1,2))+I*(kx1*i+ky1*j));
				if(iloscPaczek==2 || iloscPaczek==4)
					psi[i*NY+j] += cexp((-pow(i-x_s2,2)-pow(j-y_s2,2))/(2*pow(s2,2))+I*(kx2*i+ky2*j));
				if(iloscPaczek==3 || iloscPaczek==4)
					psi[i*NY+j] += cexp((-pow(i-x_s3,2)-pow(j-y_s3,2))/(2*pow(s3,2))+I*(kx3*i+ky3*j))+cexp((-pow(i-x_s4,2)-pow(j-y_s4,2))/(2*pow(s4,2))+I*(kx4*i+ky4*j));
			}
			else
				psi[i*NY+j] = 0;
			printf("%d %d %g %g %g\n", i, j, creal(psi[i*NY+j]), cimag(psi[i*NY+j]), pow(cabs(psi[i*NY+j]),2));
		}
		printf("\n");
	}

	/* writing to files---separately for each integration method */
	fp = fopen("schrod_a_2d.dat", "w");
	fwrite(psi, sizeof(double complex), NX*NY, fp);
	fclose(fp);
	fp = fopen("schrod_2s_2d.dat", "w");
	fwrite(psi, sizeof(double complex), NX*NY, fp);
	fclose(fp);
	fp = fopen("schrod_2s_2d_9p.dat", "w");
	fwrite(psi, sizeof(double complex), NX*NY, fp);
	fclose(fp);
	fp = fopen("schrod_cn_2d.dat", "w");
	fwrite(psi, sizeof(double complex), NX*NY, fp);
	fclose(fp);

	return 0;
}
