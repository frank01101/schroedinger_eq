/* Generating a selected potential for one-dimensional case */
/* Author: Franciszek Humieja
   Version 1.0 (2017-07-30) */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char **argv) {
	int wybor;		/* number of potential provided by the user */
	float wys;		/* height coefficient multiplying the potential value */
	const int N = 100;	/* space size */
	double v[N];		/* potential */
	int i;
	FILE *fp;

	/* checking if at least 1 command-line argument has been given */
	if(argc>=2) {
		wybor = atoi(argv[1]);		/* the first command-line argument should be the number of potential... */
		if(wybor!=0 && argc>2)
			wys = atof(argv[2]);	/* ...and the second should be the height coefficient */
		else if(wybor!=0) {
			printf("Input the potential height:\n");
			printf("> ");
			scanf("%f", &wys);
		}
	}
	else {
		printf("Choose the potential type:\n");
		printf("0 -- null\n");
		printf("1 -- Dirac delta\n");
		printf("2 -- threshold\n");
		printf("3 -- stairs\n");
		printf("4 -- Gauss function\n");
		printf("5 -- well\n");
		printf("6 -- inclined plane\n");
		printf("7 -- harmonic oscillator\n");
		printf("> ");
		scanf("%d", &wybor);
		if(wybor!=0) {
			printf("\n");
			printf("Input the potential height:\n");
			printf("> ");
			scanf("%f", &wys);
		}
	}

	switch(wybor) {
		case 0:
			/* null potential */
			for(i=0; i<N; i++)
				v[i] = 0;
			break;
		case 1:
			/* Dirac delta potential */
			for(i=0; i<N; i++)
				if(i==50)
					v[i] = wys;
				else
					v[i] = 0;
			break;
		case 2:
			/* threshold potential */
			for(i=0; i<N; i++)
				if(i>=40 && i<=60)
					v[i] = wys;
				else
					v[i] = 0;
			break;
		case 3:
			/* stairs potential */
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
			/* Gauss potential */
			for(i=0; i<N; i++)
				v[i] = wys*exp(-pow(i-50, 2)/(2*pow(5, 2)));
			break;
		case 5:
			/* well potential */
			for(i=0; i<N; i++)
				if(i<10 || i>30)
					v[i] = wys;
				else
					v[i] = 0;
			break;
		case 6:
			/* inclined plane potential */
			for(i=0; i<N; i++)
				if(i>=30 && i<=80)
					v[i] = wys/50*(i-30);
				else
					v[i] = 0;
			break;
		case 7:
			/* harmonic oscillator potential */
			for(i=0; i<N; i++)
				v[i] = wys*(0.0025*i*i-0.1*i+1);
			break;
		default:
			printf("Sorry, kalafiorry\n");
			break;
	}

	fp = fopen("potencjal_1d.dat", "w");
	fwrite(v, sizeof(double), N, fp);
	fclose(fp);

	return 0;
}
