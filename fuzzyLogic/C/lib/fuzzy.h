typedef struct pertinence pertinence;
struct pertinence
{
	float* data;
	int size;
};

typedef struct rule rule;
struct rule
{
	float value;
	pertinence* then;
};

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

float trimf(float _value, float _points[]){
	float a = (_value - _points[0])/(_points[1] - _points[0]);
	float b = (_points[2] - _value)/(_points[2] - _points[1]);
	return max(min(a,b),0);
}

float trapmf(float _value, float _points[]){
	float a = (_value - _points[0])/(_points[1] - _points[0]);
	float b = (_points[3] - _value)/(_points[3] - _points[2]);
	return max(min(min(a,b),1),0);
}

float fuzzify(float _value, pertinence _points){
	if(_points.size == 3){
		return trimf(_value,_points.data);
	}
	return trapmf(_value,_points.data);
}

float defuzzify(rule _rules[], int _size){//bySum
	int i,j;
	float uX = 0;
	float  u = 0;
	pertinence *p;
	for(i=0; i<_size;i++){
		p = _rules[i].then;
		for(j=0;j<(*p).size;j++){
			uX += (*p).data[j]*(_rules[i].value);
			 u += _rules[i].value;
		}
	}
	return uX/u;

}
