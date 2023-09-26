/* Generowanie stanu początkowego -- paczki gaussowskiej (przypadek dwuwymiarowy) */
/* Autor: Franciszek Humieja
   Wersja 1.1 (2017-VIII-18) */
#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>

int main(int argc, char **argv) {
	int iloscPaczek	= 1;			/* ilość paczek; do wyboru przez użytkownika */
	const int NX	= 100;			/* rozmiar przestrzeni */
	const int NY	= 100;			/* rozmiar przestrzeni */
	int x_s1	= (int)(0.2*NX);	/* położenie środka paczki 1 */
	int y_s1	= (int)(0.5*NY);	/* położenie środka paczki 1 */
	int x_s2	= (int)(0.8*NX);	/* położenie środka paczki 2 */
	int y_s2	= (int)(0.5*NY);	/* położenie środka paczki 2 */
	int x_s3	= (int)(0.6*NX);	/* położenie środka paczki 3 */
	int y_s3	= (int)(0.8*NY);	/* położenie środka paczki 3 */
	int x_s4	= (int)(0.6*NX);	/* położenie środka paczki 4 */
	int y_s4	= (int)(0.2*NY);	/* położenie środka paczki 4 */
	double s1	= (double)NX/20;	/* szerokość paczki 1 */
	double s2	= (double)NX/20;	/* szerokość paczki 2 */
	double s3	= (double)NX/20;	/* szerokość paczki 3 */
	double s4	= (double)NX/20;	/* szerokość paczki 4 */
	double kx1	= 1;			/* wektor falowy 1 */
	double ky1	= 0;			/* wektor falowy 1 */
	double kx2	= -1;			/* wektor falowy 2 */
	double ky2	= 0;			/* wektor falowy 2 */
	double kx3	= -0.5;			/* wektor falowy 3 */
	double ky3	= -sqrt(3)/2;		/* wektor falowy 3 */
	double kx4	= -0.5;			/* wektor falowy 4 */
	double ky4	= sqrt(3)/2;		/* wektor falowy 4 */
	double complex psi[NX*NY];		/* funkcja falowa */
	int i,j;
	FILE *fp;

	/* wczytanie ilości paczek, podanej jako pierwszy argument wywołania programu */
	if(argc>=2)
		iloscPaczek = atoi(argv[1]);

	/* tworzenie stanu początkowego */
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

	/* zapis do plików, oddzielnie dla każdej metody całkowania */
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
