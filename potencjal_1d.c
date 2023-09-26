/* Generowanie wybranego potencjału (przypadek jednowymiarowy) */
/* Autor: Franciszek Humieja
   Wersja 1.0 (2017-VII-30) */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char **argv) {
	int wybor;		/* numer potencjału, wybrany przez użytkownika */
	float wys;		/* współczynnik wysokości, przez który przemnożona będzie wartość potencjału */
	const int N = 100;	/* rozmiar przestrzeni */
	double v[N];		/* potencjał */
	int i;
	FILE *fp;

	/* sprawdzenie, czy podano przynajmniej 1 argument wywołania programu */
	if(argc>=2) {
		wybor = atoi(argv[1]);		/* pierwszy argument wywołania programu to numer potencjału... */
		if(wybor!=0 && argc>2)
			wys = atof(argv[2]);	/* ...natomiast drugi to współczynnik wysokości */
		else if(wybor!=0) {
			printf("Podaj wysokosc potencjalu:\n");
			printf("> ");
			scanf("%f", &wys);
		}
	}
	else {
		printf("Wybierz rodzaj potencjalu:\n");
		printf("0 -- brak\n");
		printf("1 -- delta Diraca\n");
		printf("2 -- stopien\n");
		printf("3 -- schodki\n");
		printf("4 -- krzywa Gaussa\n");
		printf("5 -- studnia\n");
		printf("6 -- rownia pochyla\n");
		printf("7 -- oscylator harmoniczny\n");
		printf("> ");
		scanf("%d", &wybor);
		if(wybor!=0) {
			printf("\n");
			printf("Podaj wysokosc potencjalu:\n");
			printf("> ");
			scanf("%f", &wys);
		}
	}

	switch(wybor) {
		case 0:
			/* potencjał zerowy */
			for(i=0; i<N; i++)
				v[i] = 0;
			break;
		case 1:
			/* potencjał delta Diraca */
			for(i=0; i<N; i++)
				if(i==50)
					v[i] = wys;
				else
					v[i] = 0;
			break;
		case 2:
			/* potencjał stopień */
			for(i=0; i<N; i++)
				if(i>=40 && i<=60)
					v[i] = wys;
				else
					v[i] = 0;
			break;
		case 3:
			/* potencjał schodkowy */
			for(i=0; i<N; i++)
				if(i>=30 && i<=40)
					v[i] = 0.25*wys;
				else if(i>=40 && i<=50)
					v[i] = 0.5*wys;
				else if(i>=50 && i<=60)
					v[i] = 0.75*wys;
				else if(i>=60 && i<=70)
					v[i] = wys;
				else
					v[i] = 0;
			break;
		case 4:
			/* potencjał gaussowski */
			for(i=0; i<N; i++)
				v[i] = wys*exp(-pow(i-50, 2)/(2*pow(5, 2)));
			break;
		case 5:
			/* potencjał studni */
			for(i=0; i<N; i++)
				if(i<10 || i>30)
					v[i] = wys;
				else
					v[i] = 0;
			break;
		case 6:
			/* potencjał równi pochyłej */
			for(i=0; i<N; i++)
				if(i>=30 && i<=80)
					v[i] = wys/50*(i-30);
				else
					v[i] = 0;
			break;
		case 7:
			/* potencjał oscylatora harmonicznego */
			for(i=0; i<N; i++)
				v[i] = wys*(0.0025*i*i-0.1*i+1);
			break;
		default:
			printf("Sory, kalafiory\n");
			break;
	}

	fp = fopen("potencjal_1d.dat", "w");
	fwrite(v, sizeof(double), N, fp);
	fclose(fp);

	return 0;
}
