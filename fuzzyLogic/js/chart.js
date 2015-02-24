Chart = function(operation,target,config){
  settings = {
    width:320,
    height:200
  };
  if(config)
    $.extend(config,settings);
  var $name = $("<strong>").addClass("monitor-name")
  var $value = $("<span>").addClass("monitor-value")
  var $time = $("<span>").addClass("monitor-time")
  var $ct = $("<div>")
    .css({
      display:'inline-block',
      margin:5
    })
    .append($name)
    .append($("<br>"))
    .append($value)
    .append($("<br>"))
    .append($time)
    .append($("<br>"))
    .appendTo(target);

  var _canvas = $("<canvas>").attr({
    'data-parent-id':$(target).attr("id"),
    width: settings.width,
    height: settings.height,
    'data-current-value':0
  }).appendTo($ct);

  
  var _smoothie = new SmoothieChart({
    maxValue:1,
    minValue:-1,
    grid: {
      strokeStyle:'rgb(125, 125, 125)',
      fillStyle:'rgb(60, 60, 60)',
      lineWidth: 1,
      millisPerLine: 250,
      verticalSections: 6,
    },
    labels: {
      fillStyle:'rgb(255, 255, 255)',
      fontSize:14
    }
  });
  var _lines = [[new TimeSeries(),'rgba(255, 255, 255, alpha)']];

  
  _smoothie.streamTo(_canvas[0],1000);
  
  socketsCallbacks[operation].element = _canvas;
  //bind listner
  _canvas.on(operation,socketsCallbacks[operation].callback);
  var _init = function(request) {
    var self = this;

    self.interval = setInterval(function() {
      if(!!websocket) websocket.send(request);

      var valuesStr = self.canvas.attr('data-current-value');
      var values = valuesStr.split("|");

      self.lines[0][0].append(new Date().getTime(), 0);
      for(value in values){
        if(!self.lines[+value+1]){
          self.lines.push([new TimeSeries(),'rgba('+parseInt(Math.random() * 255)+',' + parseInt(Math.random() * 255) + ',' + parseInt(Math.random() * 255) + ', alpha)']);
          self.smoothie.addTimeSeries(self.lines[+value+1][0],
            {
              strokeStyle: self.lines[+value+1][1].replace("alpha",'1'),
              fillStyle: self.lines[+value+1][1].replace("alpha",'0.5'),
              lineWidth:1
            }
          );
        }
        self.lines[+value+1][0].append(new Date().getTime(),parseFloat(values[value]));
      }

      self.canvas.closest("div").find(".monitor-name").text(socketsCallbacks[operation].name);
      self.canvas.closest("div").find(".monitor-value").text("VALUE " + valuesStr);
      self.canvas.closest("div").find(".monitor-time").text("TIME: " + ++self.time + " seconds");
      $("#"+self.canvas.attr("data-parent-id")).trigger('teste',['parameter']);
    }, 1000);

    
    self.smoothie.addTimeSeries(self.lines[0][0],{ strokeStyle:self.lines[0][1].replace("alpha",'1'), lineWidth:2 });
  }

  var _destroy = function(){
    console.log("destroing " + this.canvas)
    clearInterval(this.interval);
    this.time = 0;
  }
  

  return{
    init: _init,
    destroy: _destroy,
    canvas: _canvas,
    smoothie: _smoothie,
    lines: _lines,
    value:0,
    time:0,
    interval: null
  }
}

$.fn.sync = function(){
  console.log("sync view "+$(this).attr("href"));
  for(var monitor in monitorInstances){
      var m = monitorInstances[monitor];
      if(m.element == $(this).attr("href")){
        console.log(m);
        m.object.destroy();
        m.object.init(m.operation);
      }
  }
}