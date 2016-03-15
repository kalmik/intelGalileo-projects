#include <stdio.h>
#include <stdlib.h>
#include <time.h>

class Fis
{
	FILE* fp;

	public:
		//config
		int numInputs;
		int numOutputs;
		int numRules;

		float** inputRange;
		float** outputRange;
		int* rules;

		Fis();
		Fis(char* path);

		double* Evalfis(double* in);

};