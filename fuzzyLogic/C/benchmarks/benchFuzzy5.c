#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//FUZZY LIBRARY
#include "../lib/fuzzy.h"

int _ONBOARD_ = 0;
int setGalileo(){
	_ONBOARD_ = 1;
	return 0;
}

float e;  
float ed;
float out;
char res[40];


void runFuzzy(){
	
//Funções de pertinencia.--------
	float pGN[4] = {-1,-1,-0.75,-0.5};
	float pPN[3] = {-0.75,-0.5,-0.25};
	
	float pZZ[3] = {-0.5,0,0.5};
	
	float pPP[3] = {0.25,0.5,0.75};
	float pGP[4] = {0.5,0.75,1,1};

	pertinence GN = {&pGN,4};
	pertinence PN = {&pPN,3};
	pertinence ZZ = {&pZZ,3};
	pertinence PP = {&pPP,3};
	pertinence GP = {&pGP,4};
	
//Range de X e Y das funções de pertinencia
	float xi = -1;
	float xf = 1;
	float yi = -1;
	float yf = 1;
	float step = 0.14;


	FILE *fp;  
    char path[25] = "outputs/b5.fsurf";
    float i,j;
    if(_ONBOARD_) system("echo -n 'out' > /sys/class/gpio/gpio27/direction");

    fp = fopen(path, "w");
    fprintf(fp,"xb5=[%.3f:%.3f:%.3f];\nyb5=[%.3f:%.3f:%.3f];\nzb5=[", xi,step,xf-step,yi,step,yf-step);
    printf("Starting loop\n");
	for(i=xi;i<=xf;i=i+step){
	   for(j=yi;j<=yf;j=j+step){
    //while(1){
    //     Regras-------------------------
            e = i;
            ed = j;
			
			if(_ONBOARD_) system("echo -n '1' > /sys/class/gpio/gpio27/value");

			rule rules[49] = {
				{andOp(fuzzify(e,GN),fuzzify(ed,GN)), &GN},
				{andOp(fuzzify(e,GN),fuzzify(ed,PN)), &GN},
				{andOp(fuzzify(e,GN),fuzzify(ed,ZZ)), &PN},
				{andOp(fuzzify(e,GN),fuzzify(ed,PP)), &PN},
				{andOp(fuzzify(e,GN),fuzzify(ed,GP)), &ZZ},

				{andOp(fuzzify(e,PN),fuzzify(ed,GN)), &GN},
				{andOp(fuzzify(e,PN),fuzzify(ed,PN)), &PN},
				{andOp(fuzzify(e,PN),fuzzify(ed,ZZ)), &PN},
				{andOp(fuzzify(e,PN),fuzzify(ed,PP)), &ZZ},
				{andOp(fuzzify(e,PN),fuzzify(ed,GP)), &PP},

				{andOp(fuzzify(e,ZZ),fuzzify(ed,GN)), &PN},
				{andOp(fuzzify(e,ZZ),fuzzify(ed,PN)), &PN},
				{andOp(fuzzify(e,ZZ),fuzzify(ed,ZZ)), &ZZ},
				{andOp(fuzzify(e,ZZ),fuzzify(ed,PP)), &PP},
				{andOp(fuzzify(e,ZZ),fuzzify(ed,GP)), &PP},

				{andOp(fuzzify(e,PP),fuzzify(ed,GN)), &PN},
				{andOp(fuzzify(e,PP),fuzzify(ed,PN)), &ZZ},
				{andOp(fuzzify(e,PP),fuzzify(ed,ZZ)), &PP},
				{andOp(fuzzify(e,PP),fuzzify(ed,PP)), &PP},
				{andOp(fuzzify(e,PP),fuzzify(ed,GP)), &GP},

				{andOp(fuzzify(e,GP),fuzzify(ed,GN)), &ZZ},
				{andOp(fuzzify(e,GP),fuzzify(ed,PN)), &PP},
				{andOp(fuzzify(e,GP),fuzzify(ed,ZZ)), &PP},
				{andOp(fuzzify(e,GP),fuzzify(ed,PP)), &GP},
				{andOp(fuzzify(e,GP),fuzzify(ed,GP)), &GP},
			};


		//-------------------------------
			out = defuzzify(rules,25);
			if(_ONBOARD_) system("echo -n '0' > /sys/class/gpio/gpio27/value");
			printf("E = %.3f, ED = %.3f Fuzzy = %.3f\n", e, ed, out);
			fprintf(fp,"%.3f ",out);
        }
        fprintf(fp, "\n");
    }
    fprintf(fp, "];surf(xb5,yb5,zb5);\nxtitle('FUZZY SURFACE 5MFS');");
    fclose(fp);

}


int main(int argc, char *argv[]){
	runFuzzy();
	return 0;
}
