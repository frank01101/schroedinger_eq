/* Generate the selected potential for two-dimensional case */
/* Author: Franciszek Humieja
   Version 1.0 (2017-08-11) */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char **argv) {
	int wybor;			/* number of potential provided by the user */
	float wys;			/* height coefficient multiplying the potential value */
	char szer[2] = {'n','\0'};
	int lSzer = 0;			/* does the potential width have to be equal to the space width (1) or not (0)? */
	const int NX = 100;		/* space size */
	const int NY = 100;		/* space size */
	double v[NX*NY];		/* potential */
	int i,j;
	FILE *fp;

	/* checking if at least 1 command-line argument has been given */
	if(argc>=2) {
		wybor = atoi(argv[1]);		/* the first command-line argument should be the number of potential... */
		if(wybor!=0) {
			if(argc>=3) {
				wys = atof(argv[2]);	/* ...the second should be the height coefficient... */
				if(argc>=4) {
					szer[0] = argv[3][0];	/* ...and the third is the choice of the potential width */
					if(szer[0]=='y')
						lSzer = 1;
				}
			}
			else {
				printf("Input the potential height:\n");
				printf("> ");
				scanf("%f", &wys);
				printf("Should the potential width be equal to the space width? [y/n]:\n");
				printf("> ");
				scanf("%1s", szer);
				if(szer[0]=='y')
					lSzer = 1;
			}
		}
	}
	else {
		printf("Choose the potential type:\n");
		printf("0 -- null\n");
		printf("1 -- Dirac delta\n");
		printf("2 -- threshold\n");
		printf("3 -- wedge\n");
		printf("4 -- stairs\n");
		printf("5 -- Gauss function\n");
		printf("6 -- well\n");
		printf("7 -- inclined plane\n");
		printf("8 -- harmonic oscillator\n");
		printf("9 -- slits\n");
		printf("> ");
		scanf("%d", &wybor);
		if(wybor!=0) {
			printf("Input the potential height:\n");
			printf("> ");
			scanf("%f", &wys);
			printf("Should the potential width be equal to the space width? [y/n]:\n");
			printf("> ");
			scanf("%1s", szer);
			if(szer[0]=='y')
				lSzer = 1;
		}
	}

	/* filling the potential with zeros
	   because of the issue with memory leakage (due to the usage of scanf?) */
	for(i=0; i<NX; i++)
		for(j=0; j<NY; j++)
			v[i*NY+j] = 0;

	switch(wybor) {
		case 1:
			/* Dirac delta potential */
			for(i=0; i<NX; i++)
				for(j=0; j<NY; j++)
					if(i==NX/2)
						if(lSzer)
							v[i*NY+j] = wys;
						else if(j==NY/2)
							v[i*NY+j] = wys;
			break;
		case 2:
			/* threshold potential */
			for(i=0; i<NX; i++)
				for(j=0; j<NY; j++)
					if(i>=(int)(0.4*NX) && i<=(int)(0.6*NX))
						if(lSzer)
							v[i*NY+j] = wys;
						else if(j>=(int)(0.4*NY) && j<=(int)(0.6*NY))
							v[i*NY+j] = wys;
			break;
		case 3:
			/* wedge potential */
			for(i=0; i<NX; i++)
				for(j=0; j<NY; j++)
					if(i>=(int)(0.3*NX) && i<=(int)(0.7*NX))
						if(lSzer && j>=-0.5*NY/(0.4*NX)*i+0.875*NY && j<=0.5*NY/(0.4*NX)*i+0.125*NY)
							v[i*NY+j] = wys;
						else if(j>=-0.1*NY/(0.4*NX)*i+0.575*NY && j<=0.1*NY/(0.4*NX)*i+0.425*NY)
							v[i*NY+j] = wys;
			break;
		case 4:
			/* stairs potential */
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
			/* Gauss potential */
			for(i=0; i<NX; i++)
				for(j=0; j<NY; j++)
					if(lSzer)
						v[i*NY+j] = wys*exp(-pow(i-NX/2,2)/(2*pow(NX/20,2)));
					else
						v[i*NY+j] = wys*exp((-pow(i-NX/2,2)-pow(j-NY/2,2))/(2*pow(NX/20,2)));
			break;
		case 6:
			/* well potential */
			for(i=0; i<NX; i++)
				for(j=0; j<NY; j++)
					if(i<0.1*NX || i>0.3*NX)
						v[i*NY+j] = wys;
					else if(!lSzer && (j<0.4*NY || j>0.6*NY))
						v[i*NY+j] = wys;
			break;
		case 7:
			/* inclined plane potential */
			for(i=0; i<NX; i++)
				for(j=0; j<NY; j++)
					if(i>=0.3*NX && i<=0.8*NX)
						if(lSzer)
							v[i*NY+j] = wys/(0.5*NX)*(i-0.3*NX);
						else if(j>=0.4*NY && j<=0.6*NY)
							v[i*NY+j] = wys/(0.5*NX)*(i-0.3*NX);
			break;
		case 8:
			/* harmonic oscillator potential */
			for(i=0; i<NX; i++)
				for(j=0; j<NY; j++)
					if(lSzer)
						v[i*NY+j] = wys*(0.0025*i*i-0.1*i+1);
					else
						v[i*NY+j] = wys*(0.0025*(i*i+j*j)-0.1*i-0.2*j+5);
			break;
		case 9:
			/* slit potential */
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
