var express = require("express");
var app = express();
var http = require("http");
var server = http.createServer(app);

var random = false;

app.get('/check/:code', function(req, res){
  if (random) {
    console.log("random");
    res.send("random");
  } else {
    var code = req.params.code;
    var slice = JSON.stringify(Math.floor(Math.random() * 8));
    console.log("[" + code + "] return: " + slice);
    res.send(slice);
  }
})

server.listen(8080);
