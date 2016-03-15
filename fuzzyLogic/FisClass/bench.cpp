#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <string.h>
#include "fis.h"

int main(){

	Fis* f = new Fis("b7matlab.fis");


	double* out = (double*)malloc(sizeof(double)*f->numOutputs);
	double* in = (double*)malloc(sizeof(double)*f->numInputs);

	char path[25] = "tests/b7.m";

	FILE *fp;
	fp = fopen(path, "w+");

	float xi = -1;
    float xf = 1;
    float yi = -1;
    float yf = 1;
    float step = 0.14;

    float i,j;

    fprintf(fp,"xb7=[%f:%f:%f];\nyb7=[%f:%f:%f];\nzb7=[", xi,step,xf,yi,step,yf);
 	for(i=xi;i<=xf;i=i+step){
		for(j=yi;j<=yf;j=j+step){

			in[0] = i;
			in[1] = j;
			out = f->Evalfis(in);

			fprintf(fp,"%f ", out[0]);
		}
		fprintf(fp,";");
	}
	fprintf(fp, "];\nx7 = (xb7.^0)'*xb7;\ny7 = yb7'*(yb7.^0);\nsurf(x7,y7,zb7);\ntitle('FUZZY SURFACE 7MFS');");
    fclose(fp);

	return 0;
}

