socketsCallbacks = {
  'GET_FUZZY_VALUE_RESPONSE': {
      name: "Fuzzy value monitor",
      description: "Get current fuzzy value at time",
      element:null,
      callback: function(event, param){
        if(param)
          $(this).attr('data-current-value',param);
      }
  },
  'GET_INPUT_VALUE_RESPONSE': {
      name: "Input values monitor",
      description: "Get current fuzzy input at time",
      element:null,
      callback: function(event, param){
        if(param)
          $(this).attr('data-current-value',param);
      }
  }
};

monitorInstances = [];