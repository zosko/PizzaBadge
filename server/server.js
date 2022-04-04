var express = require("express");
var app = express();
var http = require("http");
var server = http.createServer(app);

app.get('/check/:code', function(req, res){
  res.send(JSON.stringify(Math.floor(Math.random() * 7)));
})

server.listen(8080);
