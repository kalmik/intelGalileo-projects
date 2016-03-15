#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <string.h>
#include "fuzzy-loader.h"

void next_line(FILE* fp)
{
    int foundline;
    foundline = fscanf(fp, "%*s\n");
}

int get_numInputs(FILE* fp)
{
    int foundline  = 0;
    int r;

    while(!foundline){
        foundline = fscanf(fp, "NumInputs=%i\n", &r);
        if(!foundline) next_line(fp);
    }

    return r;
}

int get_numOutputs(FILE* fp)
{
    int foundline  = 0;
    int r;

    while(!foundline){
        foundline = fscanf(fp, "NumOutputs=%i\n", &r);
        if(!foundline) next_line(fp);
    }

    return r;
}

int get_numRules(FILE* fp)
{
    int foundline  = 0;
    int r;

    while(!foundline){
        foundline = fscanf(fp, "NumRules=%i\n", &r);
        if(!foundline) next_line(fp);
    }

    return r;
}

float* pack_io(FILE* fp, int* sz)
{

    float a,b,c,d;
    int foundline = 0;
    int tmp;
    char type[10];
    char name[10];

    int size = 0;
    int offsetR = 0;
    int offsetL = 0;

    /*Skiping 3 lines*/
    next_line(fp);
    next_line(fp);
    next_line(fp);
    /*---------------*/
    foundline = fscanf(fp, "NumMFs=%i\n", &tmp);

    float* stackR = (float*)malloc(sizeof(float));
    float* stackL = (float*)malloc(sizeof(float)*(tmp+1));
    float* fullStack;

    stackL[offsetL++] = tmp;
    for(tmp; tmp>0; tmp--){
        foundline = fscanf(fp, "MF%*i=\'%[aA-zZ]\':\'%[a-z]\',[%f %f %f %f]\n", name, type, &a, &b, &c, &d);
        if(foundline != 6){ /* trimf case, read only 3 floats*/
            next_line(fp);
            size+= 3;
            stackR = (float*)realloc(stackR, (sizeof(float))*size);
            stackL[offsetL++] = 3;
            stackR[offsetR++] = a;
            stackR[offsetR++] = b;
            stackR[offsetR++] = c;
            continue; 
        }
        size += 4;
        stackR = (float*)realloc(stackR, (sizeof(float))*size);
        stackL[offsetL++] = 4;
        stackR[offsetR++] = a;
        stackR[offsetR++] = b;
        stackR[offsetR++] = c;
        stackR[offsetR++] = d;
    }
    fullStack = (float*)malloc(sizeof(float)*(offsetL+offsetR));
    int i;
    for(i = 0; i < offsetL+offsetR; i++){
            fullStack[i] = i < offsetL ? stackL[i] : stackR[i - offsetL];
    }

    if(sz != NULL) *sz = (offsetL+offsetR);

    free(stackL);
    free(stackR);

    return fullStack;
}

float* load_input(FILE* fp, int* sz)
{   
    int foundline = 0;
    int tmp;

    //Looking for input zone
    while(!foundline){    
        foundline = fscanf(fp, "[Input%i]\n", &tmp);
        if(!foundline) next_line(fp);
    }

    return pack_io(fp, sz);
}

float* load_output(FILE* fp, int* sz)
{
    
    int foundline = 0;
    int tmp;

    //looking for Output zone
    while(!foundline){    
        foundline = fscanf(fp, "[Output%i]\n", &tmp);
        if(!foundline) next_line(fp);
    }

    return pack_io(fp, sz);
}

int* load_rules(FILE *fp,int numInputs, int numOutputs, int numRules, int *sz)
{
    int *r;
    int foundline = 0;
    int i,j,k;
    int total = (numInputs+numOutputs+1)*numRules;
    if(sz != NULL) *sz = total;
    char aux[40];

    r = (int*)malloc(sizeof(int)*(total));

    //looking for the last zone, Rules
    while(!foundline){    
        foundline = fscanf(fp, "%s\n", aux);
        if(!foundline) next_line(fp);
    }


    k = 0;
    for(i = 0; i < numRules; i++){
        for(j = 0; j < numInputs; j++)
            foundline = fscanf(fp, "%i ", &r[k++]);

        foundline = fscanf(fp, "%c ", aux); //Scaping , char

        for(j = 0; j < numOutputs; j++)
            foundline = fscanf(fp, "%i ", &r[k++]);

        foundline = fscanf(fp, "(%*i) : %i\n", &r[k++]);
    }

    return r;

}
