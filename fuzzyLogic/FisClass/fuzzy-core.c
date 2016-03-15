#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "fuzzy-core.h"

float max(float _a, float _b){
	return _a > _b ? _a : _b;
}

float min(float _a, float _b){
	return _a < _b ? _a : _b;
}

float orOp(float _a, float _b){
	return max(_a,_b);
}

float andOp(float _a, float _b){
	return min(_a,_b);
}

float trimf(float _value, float* _points){
	float a = (_value - _points[0])/(_points[1] - _points[0]);
	float b = (_points[2] - _value)/(_points[2] - _points[1]);
	return max(min(a,b),0);
}

float trapmf(float _value, float* _points){
	float a = (_value - _points[0])/(_points[1] - _points[0]);
	float b = (_points[3] - _value)/(_points[3] - _points[2]);
	return max(min(min(a,b),1),0);
}

float fuzzify(float _value, float* _points, int size){
	//printf("%f\n",_value);
	if(size == 3){
		return trimf(_value, _points);
	}
	return trapmf(_value,_points);
}

void defuzzify( double _value, float* _rules, int _size, double* uX, double* u){
	int i,j;
	for(i = 0; i < _size; i++){
		*uX += _rules[i]*_value;
		*u += _value;
	}
}
