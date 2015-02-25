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
	float pN[4] = {-1,-1,-0.5,0};
	float pZ[3] = {-0.5,0,0.5};
	float pP[4] = {0,0.5,1,1};

	pertinence N = {&pN,4};
	pertinence Z = {&pZ,3};
	pertinence P = {&pP,4};
	
//Range de X e Y das funções de pertinencia
	float xi = -1;
	float xf = 1;
	float yi = -1;
	float yf = 1;
	float step = 0.04;

	if(_ONBOARD_) system("echo -n 'out' > /sys/class/gpio/gpio27/direction");

	printf("Starting loop\n");
	while(1){
	// 	Regras-------------------------
			srand(time(NULL));
			e = rand()%1000;
			e = (e*2/1000.0)-1;

			srand(time(NULL));
			ed = rand()%1000;
			ed = (ed*2/1000.0)-1;
			
			if(_ONBOARD_) system("echo -n '1' > /sys/class/gpio/gpio27/value");

			rule rules[9] = {
				{andOp(fuzzify(e,N),fuzzify(ed,N)), &N},
				{andOp(fuzzify(e,N),fuzzify(ed,Z)), &N},
				{andOp(fuzzify(e,N),fuzzify(ed,P)), &Z},

				{andOp(fuzzify(e,Z),fuzzify(ed,N)), &N},
				{andOp(fuzzify(e,Z),fuzzify(ed,Z)), &Z},
				{andOp(fuzzify(e,Z),fuzzify(ed,P)), &P},

				{andOp(fuzzify(e,P),fuzzify(ed,N)), &Z},
				{andOp(fuzzify(e,P),fuzzify(ed,Z)), &P},
				{andOp(fuzzify(e,P),fuzzify(ed,P)), &P},
			};


		//-------------------------------
			out = defuzzify(rules,9);
			if(_ONBOARD_) system("echo -n '0' > /sys/class/gpio/gpio27/value");
			printf("E = %.3f, ED = %.3f Fuzzy = %.3f\n", e, ed, out);
	}	

}


int main(int argc, char *argv[]){
	//descomentar se for usar na galileo
	//setGalileo();
	runFuzzy();
	return 0;
}
