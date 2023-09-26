/* Generowanie wybranego potencjału (przypadek dwuwymiarowy) */
/* Autor: Franciszek Humieja
   Wersja 1.0 (2017-VIII-11) */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char **argv) {
	int wybor;			/* numer potencjału, wybrany przez użytkownika */
	float wys;			/* współczynnik wysokości, przez który przemnożona będzie wartość potencjału */
	char szer[2] = {'n','\0'};
	int lSzer = 0;			/* szerokość potencjału ma być równa szerokości przestrzeni (1) czy nie (0)? */
	const int NX = 100;		/* rozmiar przestrzeni */
	const int NY = 100;		/* rozmiar przestrzeni */
	double v[NX*NY];		/* potencjał */
	int i,j;
	FILE *fp;

	/* sprawdzenie, czy podano przynajmniej 1 argument wywołania programu */
	if(argc>=2) {
		wybor = atoi(argv[1]);		/* pierwszy argument wywołania programu to numer potencjału... */
		if(wybor!=0) {
			if(argc>=3) {
				wys = atof(argv[2]);	/* ...drugi to współczynnik wysokości... */
				if(argc>=4) {
					szer[0] = argv[3][0];	/* ...natomiast trzeci to wybór szerokości potencjału */
					if(szer[0]=='t')
						lSzer = 1;
				}
			}
			else {
				printf("Podaj wysokosc potencjalu:\n");
				printf("> ");
				scanf("%f", &wys);
				printf("Czy szerokosc potencjalu ma byc rowna szerokosci przestrzeni? [t/n]:\n");
				printf("> ");
				scanf("%1s", szer);
				if(szer[0]=='t')
					lSzer = 1;
			}
		}
	}
	else {
		printf("Wybierz rodzaj potencjalu:\n");
		printf("0 -- brak\n");
		printf("1 -- delta Diraca\n");
		printf("2 -- stopien\n");
		printf("3 -- klin\n");
		printf("4 -- schodki\n");
		printf("5 -- krzywa Gaussa\n");
		printf("6 -- studnia\n");
		printf("7 -- rownia pochyla\n");
		printf("8 -- oscylator harmoniczny\n");
		printf("9 -- szczeliny\n");
		printf("> ");
		scanf("%d", &wybor);
		if(wybor!=0) {
			printf("Podaj wysokosc potencjalu:\n");
			printf("> ");
			scanf("%f", &wys);
			printf("Czy szerokosc potencjalu ma byc rowna szerokosci przestrzeni? [t/n]:\n");
			printf("> ");
			scanf("%1s", szer);
			if(szer[0]=='t')
				lSzer = 1;
		}
	}

	/* wypełnienie potencjału zerami
	   jest problem z wyciekiem pamięci (z powodu użycia scanf?) */
	for(i=0; i<NX; i++)
		for(j=0; j<NY; j++)
			v[i*NY+j] = 0;

	switch(wybor) {
		case 1:
			/* potencjał delta Diraca */
			for(i=0; i<NX; i++)
				for(j=0; j<NY; j++)
					if(i==NX/2)
						if(lSzer)
							v[i*NY+j] = wys;
						else if(j==NY/2)
							v[i*NY+j] = wys;
			break;
		case 2:
			/* potencjał stopień */
			for(i=0; i<NX; i++)
				for(j=0; j<NY; j++)
					if(i>=(int)(0.4*NX) && i<=(int)(0.6*NX))
						if(lSzer)
							v[i*NY+j] = wys;
						else if(j>=(int)(0.4*NY) && j<=(int)(0.6*NY))
							v[i*NY+j] = wys;
			break;
		case 3:
			/* potencjał klinowy */
			for(i=0; i<NX; i++)
				for(j=0; j<NY; j++)
					if(i>=(int)(0.3*NX) && i<=(int)(0.7*NX))
						if(lSzer && j>=-0.5*NY/(0.4*NX)*i+0.875*NY && j<=0.5*NY/(0.4*NX)*i+0.125*NY)
							v[i*NY+j] = wys;
						else if(j>=-0.1*NY/(0.4*NX)*i+0.575*NY && j<=0.1*NY/(0.4*NX)*i+0.425*NY)
							v[i*NY+j] = wys;
			break;
		case 4:
			/* potencjał schodkowy */
			for(i=0; i<NX; i++)
				for(j=0; j<NY; j++)
					if(i>=0.3*NX && i<0.4*NX) {
						if(lSzer)
							v[i*NY+j] = 0.25*wys;
						else if(j>=0.4*NY && j<=0.6*NY)
							v[i*NY+j] = 0.25*wys;
					}
					else if(i>=0.4*NX && i<0.5*NX) {
						if(lSzer)
							v[i*NY+j] = 0.5*wys;
						else if(j>=0.4*NY && j<=0.6*NY)
							v[i*NY+j] = 0.5*wys;
					}
					else if(i>=0.5*NX && i<0.6*NX) {
						if(lSzer)
							v[i*NY+j] = 0.75*wys;
						else if(j>=0.4*NY && j<=0.6*NY)
							v[i*NY+j] = 0.75*wys;
					}
					else if(i>=0.6*NX && i<=0.7*NX) {
						if(lSzer)
							v[i*NY+j] = wys;
						else if(j>=0.4*NY && j<=0.6*NY)
							v[i*NY+j] = wys;
					}
			break;
		case 5:
			/* potencjał gaussowski */
			for(i=0; i<NX; i++)
				for(j=0; j<NY; j++)
					if(lSzer)
						v[i*NY+j] = wys*exp(-pow(i-NX/2,2)/(2*pow(NX/20,2)));
					else
						v[i*NY+j] = wys*exp((-pow(i-NX/2,2)-pow(j-NY/2,2))/(2*pow(NX/20,2)));
			break;
		case 6:
			/* potencjał studni */
			for(i=0; i<NX; i++)
				for(j=0; j<NY; j++)
					if(i<0.1*NX || i>0.3*NX)
						v[i*NY+j] = wys;
					else if(!lSzer && (j<0.4*NY || j>0.6*NY))
						v[i*NY+j] = wys;
			break;
		case 7:
			/* potencjał równi pochyłej */
			for(i=0; i<NX; i++)
				for(j=0; j<NY; j++)
					if(i>=0.3*NX && i<=0.8*NX)
						if(lSzer)
							v[i*NY+j] = wys/(0.5*NX)*(i-0.3*NX);
						else if(j>=0.4*NY && j<=0.6*NY)
							v[i*NY+j] = wys/(0.5*NX)*(i-0.3*NX);
			break;
		case 8:
			/* potencjał oscylatora harmonicznego */
			for(i=0; i<NX; i++)
				for(j=0; j<NY; j++)
					if(lSzer)
						v[i*NY+j] = wys*(0.0025*i*i-0.1*i+1);
					else
						v[i*NY+j] = wys*(0.0025*(i*i+j*j)-0.1*i-0.2*j+5);
			break;
		case 9:
			/* potencjał szczelinowy */
			for(i=0; i<NX; i++)
				for(j=0; j<NY; j++)
					if(i==NX/2)
						if(lSzer && (j<(int)(0.44*NY) || j>(int)(0.46*NY) && j<(int)(0.54*NY) || j>(int)(0.56*NY)))
							v[i*NY+j] = wys;
						else if(!lSzer && (j>=(int)(0.44*NY) && j<=(int)(0.46*NY) || j>=(int)(0.54*NY) && j<=(int)(0.56*NY)))
							v[i*NY+j] = wys;
			break;
	}

	fp = fopen("potencjal_2d.dat", "w");
	fwrite(v, sizeof(double), NX*NY, fp);
	fclose(fp);

	return 0;
}
