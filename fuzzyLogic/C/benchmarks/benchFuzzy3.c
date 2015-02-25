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
    float step = 0.05;

    FILE *fp;  
    char path[25] = "outputs/b3.fsurf";
    float i,j;
    if(_ONBOARD_) system("echo -n 'out' > /sys/class/gpio/gpio27/direction");

    fp = fopen(path, "w");
    fprintf(fp,"xb3=[%.3f:%.3f:%.3f];\nyb3=[%.3f:%.3f:%.3f];\nzb3=[", xi,step,xf-step,yi,step,yf-step);
    printf("Starting loop\n");
    for(i=xi;i<=xf;i=i+step){
        for(j=yi;j<=yf;j=j+step){
    //while(1){
    //     Regras-------------------------
            e = i;
            ed = j;
            
            
            
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
            fprintf(fp,"%.3f ",out);
        }
        fprintf(fp, "\n");
    }
    fprintf(fp, "];\nsurf(xb3,yb3,zb3);\nxtitle('FUZZY SURFACE 3MFS');");
    fclose(fp);

}


int main(int argc, char *argv[]){
    //descomentar se for usar na galileo
    //setGalileo();
    runFuzzy();
    return 0;
}