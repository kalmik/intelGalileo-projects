window.WebSocket = window.WebSocket || window.MozWebSocket;

var websocket = new WebSocket('ws://10.13.100.200:9001',
                              'dumb-increment-protocol');

websocket.onopen = function () {
    $('h1').css('color', 'green');
};

websocket.onerror = function () {
    $('h1').css('color', 'red');
};

websocket.onmessage = function (message) {
    var packet = message.data.split('\n');
    switch(packet[0])
    {
      case 'GET_FUZZY_VALUE_RESPONSE':
        //fuzzyValue = parseFloat(packet[1]);
        socketsCallbacks['GET_FUZZY_VALUE_RESPONSE'].element
          .trigger('GET_FUZZY_VALUE_RESPONSE',[packet[1]]);
      break;
      case 'GET_INPUT_VALUE_RESPONSE':
        //INPUTValue = parseFloat(packet[1]);
        socketsCallbacks['GET_INPUT_VALUE_RESPONSE'].element
          .trigger('GET_INPUT_VALUE_RESPONSE',[packet[1]]);
      break;
    }
    
};