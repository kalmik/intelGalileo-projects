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
	float pMN[3] = {-0.75,-0.5,-0.25};
	float pPN[3] = {-0.5,-0.25,0};
	float pZZ[3] = {-0.25,0,0.25};
	float pPP[3] = {0,0.25,0.5};
	float pMP[3] = {0.25,0.5,0.75};
	float pGP[4] = {0.5,0.75,1,1};

	pertinence GN = {&pGN,4};
	pertinence MN = {&pMN,3};
	pertinence PN = {&pPN,3};
	pertinence ZZ = {&pZZ,3};
	pertinence PP = {&pPP,3};
	pertinence MP = {&pMP,3};
	pertinence GP = {&pGP,4};
	
//Range de X e Y das funções de pertinencia
	float xi = -1;
	float xf = 1;
	float yi = -1;
	float yf = 1;
	float step = 0.14;


	FILE *fp;  
    char path[25] = "outputs/b7.fsurf";
    float i,j;
    if(_ONBOARD_) system("echo -n 'out' > /sys/class/gpio/gpio27/direction");

    fp = fopen(path, "w");
    fprintf(fp,"xb7=[%.3f:%.3f:%.3f];\nyb7=[%.3f:%.3f:%.3f];\nzb7=[", xi,step,xf-step,yi,step,yf-step);
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
				{andOp(fuzzify(e,GN),fuzzify(ed,MN)), &GN},
				{andOp(fuzzify(e,GN),fuzzify(ed,PN)), &MN},
				{andOp(fuzzify(e,GN),fuzzify(ed,ZZ)), &MN},
				{andOp(fuzzify(e,GN),fuzzify(ed,PP)), &PN},
				{andOp(fuzzify(e,GN),fuzzify(ed,MP)), &PN},
				{andOp(fuzzify(e,GN),fuzzify(ed,GP)), &ZZ},

				{andOp(fuzzify(e,MN),fuzzify(ed,GN)), &GN},
				{andOp(fuzzify(e,MN),fuzzify(ed,MN)), &MN},
				{andOp(fuzzify(e,MN),fuzzify(ed,PN)), &MN},
				{andOp(fuzzify(e,MN),fuzzify(ed,ZZ)), &PN},
				{andOp(fuzzify(e,MN),fuzzify(ed,PP)), &PN},
				{andOp(fuzzify(e,MN),fuzzify(ed,MP)), &ZZ},
				{andOp(fuzzify(e,MN),fuzzify(ed,GP)), &PP},

				{andOp(fuzzify(e,PN),fuzzify(ed,GN)), &MN},
				{andOp(fuzzify(e,PN),fuzzify(ed,MN)), &MN},
				{andOp(fuzzify(e,PN),fuzzify(ed,PN)), &PN},
				{andOp(fuzzify(e,PN),fuzzify(ed,ZZ)), &PN},
				{andOp(fuzzify(e,PN),fuzzify(ed,PP)), &ZZ},
				{andOp(fuzzify(e,PN),fuzzify(ed,MP)), &PP},
				{andOp(fuzzify(e,PN),fuzzify(ed,GP)), &PP},

				{andOp(fuzzify(e,ZZ),fuzzify(ed,GN)), &MN},
				{andOp(fuzzify(e,ZZ),fuzzify(ed,MN)), &PN},
				{andOp(fuzzify(e,ZZ),fuzzify(ed,PN)), &PN},
				{andOp(fuzzify(e,ZZ),fuzzify(ed,ZZ)), &ZZ},
				{andOp(fuzzify(e,ZZ),fuzzify(ed,PP)), &PP},
				{andOp(fuzzify(e,ZZ),fuzzify(ed,MP)), &PP},
				{andOp(fuzzify(e,ZZ),fuzzify(ed,GP)), &MP},

				{andOp(fuzzify(e,PP),fuzzify(ed,GN)), &PN},
				{andOp(fuzzify(e,PP),fuzzify(ed,MN)), &PN},
				{andOp(fuzzify(e,PP),fuzzify(ed,PN)), &ZZ},
				{andOp(fuzzify(e,PP),fuzzify(ed,ZZ)), &PP},
				{andOp(fuzzify(e,PP),fuzzify(ed,PP)), &PP},
				{andOp(fuzzify(e,PP),fuzzify(ed,MP)), &MP},
				{andOp(fuzzify(e,PP),fuzzify(ed,GP)), &MP},

				{andOp(fuzzify(e,MP),fuzzify(ed,GN)), &PN},
				{andOp(fuzzify(e,MP),fuzzify(ed,MN)), &ZZ},
				{andOp(fuzzify(e,MP),fuzzify(ed,PN)), &PP},
				{andOp(fuzzify(e,MP),fuzzify(ed,ZZ)), &PP},
				{andOp(fuzzify(e,MP),fuzzify(ed,PP)), &MP},
				{andOp(fuzzify(e,MP),fuzzify(ed,MP)), &MP},
				{andOp(fuzzify(e,MP),fuzzify(ed,GP)), &GP},

				{andOp(fuzzify(e,GP),fuzzify(ed,GN)), &ZZ},
				{andOp(fuzzify(e,GP),fuzzify(ed,MN)), &PP},
				{andOp(fuzzify(e,GP),fuzzify(ed,PN)), &PP},
				{andOp(fuzzify(e,GP),fuzzify(ed,ZZ)), &MP},
				{andOp(fuzzify(e,GP),fuzzify(ed,PP)), &MP},
				{andOp(fuzzify(e,GP),fuzzify(ed,MP)), &GP},
				{andOp(fuzzify(e,GP),fuzzify(ed,GP)), &GP}
			};


		//-------------------------------
			out = defuzzify(rules,49);
			if(_ONBOARD_) system("echo -n '0' > /sys/class/gpio/gpio27/value");
			printf("E = %.3f, ED = %.3f Fuzzy = %.3f\n", e, ed, out);
			fprintf(fp,"%.3f ",out);
        }
        fprintf(fp, "\n");
    }
    fprintf(fp, "];surf(xb7,yb7,zb7);\nxtitle('FUZZY SURFACE 7MFS');");
    fclose(fp);

}


int main(int argc, char *argv[]){
	runFuzzy();
	return 0;
}
