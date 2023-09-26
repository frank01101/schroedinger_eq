#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
	char dupa = 'd';	
	char dupa1[] = {'d', 'u', 'p', 'a', '\0'};	
	char dupa2[] = "dupsko";
	char *dupa3 = "dupisko";
	char *dupa4 = dupa2;
	char dupa5[7];
	strcpy(dupa5, dupa2);
	char *dupa6 = dupa3;
	char *dupka = "334.2";
	float dupeczka = atof(dupka);
	int a = 5;
	double b = a+0.00000001;
	float c = a+0.00000001;
	float g = 0;
	char paulajestgupia[2];
	char pau;
	double z = (double)4/3;

	printf("%f %f %d %f %f\n", b, c, (int)(0.2*11), z, sqrt(3));
	printf("%c %s %s %s %s %s %s %f\n", dupa, dupa1, dupa2, dupa3, dupa4, dupa5, dupa6, dupeczka);

	if(!g) printf("dupa duap\n");

	if(1>0)
		if(2>3)
			printf("lalala\n");
		else
			printf("lahahaha\n");

	//pau = argv[1][0];
	scanf("%1s", paulajestgupia);
	scanf("%f", &g);
	scanf("%1s", &pau);
	printf("%s %s %f %c\n", argv[1], paulajestgupia, g, pau);

	return 0;
}
