_fuzzify = function (ranges, value){
	var index = null;
	//find range
	for(var i = 0; i < ranges.length - 1; i++){
		var pi = ranges[i][0];
		var pf = ranges[i+1][0];

		if (value >= pi && value <= pf){
			index = i;
			break; 
		}
	}
	//out of range
	//console.log("ou of range");
	if(index === null) return 0;

	var pi = ranges[index][0];
	var pf = ranges[index+1][0];
	var vi = ranges[index][1];
	var vf = ranges[index+1][1];
	
	
	if(vf == vi){
		//console.log("cte "+ vf);
		return vf;
	} 
		
	//console.log("reta");
	var a = ((vf-vi)/(pf-pi));
	var offset  = a < 0 ? 1 : 0;
	var res = a*(value-pi) + offset; 
	//console.log(res);
	return res;

}

_implication = function(_rules, _mode){
	var mode = _mode ? _mode : "MULT"; //TODO
	var out = [];
	for(rule in _rules){
		var aux = [];
		for(var i = 0; i < _rules[rule].then.length; i++){
			var k = _rules[rule].then[i][0];
			var l = _rules[rule].then[i][1]*_rules[rule].ifValue;
			aux.push([k,l])
		}
		out.push(aux);
	}
	

	return out;

}

_agregation = function(imp, _mode){
	var mode = _mode ? _mode : "MAX"; //TODO
	var aux = {};

	for(var i =0 ;i<imp.length; i++){
		var imp1 = imp[i];
		for (var j=0; j<imp1.length; j++){
			var range = imp1[j];
			if(aux[range[0]]){
				if(aux[range[0]].value < range[1])
				aux[range[0]].value = range[1];
				continue;
			}
			aux[range[0]] = {value:range[1]};
		}
	}

	return aux;

}

_defuzzify = function(lst, _mode){
	var mode = _mode ? _mode : "CENT"; //TODO
	var n = 0,
		d = 0;
	for(i in lst){
		//console.log(i);
		n += i*lst[i].value;
		d += lst[i].value;
	}

	return n/d;
}

_and = function(p1,p2, _mode){
	return Math.min(p1,p2);
}

_or = function(p1,p2, _mode){
	return Math.max(p1,p2);
}


module.exports = {
	fuzzify: _fuzzify,
	implication: _implication,
	agregation: _agregation,
	defuzzify: _defuzzify,
	and:_and,
	or:_or,
	mode:{
		MULTIPLICATION: "MULT",
		MAX: "MAX",
		MIN: "MIN",
		CENTROID: "CENTROID"
	}
};
