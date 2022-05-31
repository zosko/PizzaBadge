var express = require("express");
var app = express();
var http = require("http");
var server = http.createServer(app);
const path = require('path');

var responseValue = "0";
var sliceToEat = false;

function resetResponse() {
  sliceToEat = false;
  responseValue = "0";
}

app.get('/', function(req, res){
  res.sendFile(path.join(__dirname, 'index.html'));
})

app.get('/return/:value', function(req, res){
  responseValue = req.params.value;
  res.send("ok");
})

app.get('/random', function(req, res){
  sliceToEat = !sliceToEat;
  res.send("ok");
})

app.get('/check/:email', function(req, res){
  if (sliceToEat) {
    console.log("random");
    res.send("random-eat");
  } else {
    var email = req.params.email;
    console.log("[" + email + "] return: " + responseValue);
    if (responseValue == 8 ) {
      res.send("free-pizza");
    } else {
      res.send(responseValue);
    }
    
  }
  resetResponse();
})

server.listen(8080);
