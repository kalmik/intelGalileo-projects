#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <string.h>
#include "fis.h"
#include "fuzzy-loader.h"
#include "fuzzy-core.h"


#define TEST if(1)
#ifndef DEBUG
	#define TEST if(0)
#endif

Fis::Fis(){
	printf("Fuzzy-Loader\n");
};

Fis::Fis(char* path){
	fp = fopen(path, "r");

	numInputs = get_numInputs(fp);
	numOutputs = get_numOutputs(fp);
	numRules = get_numRules(fp);

	TEST
	{
		printf("Number of Inputs %i\n", numInputs);
		printf("Number of Outputs %i\n", numOutputs);
		printf("Number of Rules %i\n", numRules);
	}

	inputRange = (float**)malloc(sizeof(float*)*numInputs);
	for(int i = 0; i < numInputs; i++){
		inputRange[i] = load_input(fp, NULL);
	}

	outputRange = (float**)malloc(sizeof(float*)*numOutputs);
	for(int i = 0; i < numOutputs; i++)
		outputRange[i] = load_output(fp, NULL);

	rules = load_rules(fp, numInputs, numOutputs, numRules, NULL);
};

double* Fis::Evalfis(double* in){

	int i, j, k, jump, cur_MF_sz;
	float* cur_MF;
	double cur_value;
	double *fuzzyValues, *outValues, *cur_value_v, *out;

	int rules_sz_ln = 1 + numInputs + numOutputs;

	fuzzyValues = (double*)malloc(sizeof(double)*numRules);
	outValues = (double*)malloc(sizeof(double)*numOutputs*2);
	cur_value_v = (double*)malloc(sizeof(double)*numInputs);

	out = (double*)malloc(sizeof(double)*numOutputs);

	for(i = 0; i < numOutputs*2; i++){
		outValues[i] = 0;
	}

	for(i = 0; i < numRules; i++){

		for(j = 0; j < numInputs; j++){

			cur_MF_sz = (int)(inputRange[j][rules[i*rules_sz_ln+j]]);
			cur_MF = (float*)malloc(sizeof(float)*cur_MF_sz);

			jump = 0;
			for(k = 0; k < rules[i*rules_sz_ln+j]; k++)
				jump += (int)(inputRange[j][k]);

			for(k = 0; k < cur_MF_sz; k++){
				cur_MF[k] = inputRange[j][k+jump+1];
			}

			cur_value_v[j] = fuzzify(in[j], cur_MF, cur_MF_sz);
			free(cur_MF);
		}

		//Implications

		fuzzyValues[i] = cur_value_v[0];
		for(j = 1; j < numInputs; j ++){

			if(rules[i*rules_sz_ln+rules_sz_ln-1] == 1)//andOp
				fuzzyValues[i] = andOp(cur_value_v[j], fuzzyValues[i]);

			else if(rules[i*rules_sz_ln+rules_sz_ln-1] == 2)//andOp
				fuzzyValues[i] = orOp(cur_value_v[j], fuzzyValues[i]);
		}

		//Aggregations

		int l = 0;
		for(j = numInputs; j < numOutputs+numInputs; j++){

			cur_MF_sz = (int)(outputRange[j - numInputs][rules[i*rules_sz_ln+j]]);
			cur_MF = (float*)malloc(sizeof(float)*cur_MF_sz);

			jump = 0;
			for(k = 0; k < rules[i*rules_sz_ln+j]; k++)
				jump += (int)(outputRange[j - numInputs][k]);

			for(k = 0; k < cur_MF_sz; k++){
				cur_MF[k] = outputRange[j - numInputs][k+jump+1];
			}
			defuzzify(fuzzyValues[i], cur_MF, cur_MF_sz, &outValues[l], &outValues[l+1]);
			l += 2;
			free(cur_MF);
		}

	}

	for (i = 0; i < numOutputs*2; i += 2 )
	{
		TEST printf("Output%i Ux = %f, U = %f, Ux/U = %f\n", i, outValues[i], outValues[i+1], outValues[i]/outValues[i+1]);
		out[i] = outValues[i]/outValues[i+1];
	}

	return out;
};