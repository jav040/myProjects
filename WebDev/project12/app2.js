var express = require("express");
var app = express();



app.get("/", function(req, resp){
	resp.send("Hi there, welcome to my assignment");

});


app.get("/speak/:animal", function(req, resp){
	var sounds = {
	pig: "Oink",
	cow: "Moo",
	dog: "Woof Woof!",
	cat: "I hate you human",
	goldfish: "...."
	}
	var animal = req.params.animal;
	var sound = sounds[animal];
	resp.send("The " + animal + " says " + sound);
});



app.get("/repeat/:message/:times", function(req, res){
	var message = req.params.message;
	var times = Number(req.params.times);
	var result = "";
	for(var i = 0; i < times; i++)
	{
		result += message + " ";
	}
	res.send(result);

});


app.listen(4000, function(){

	console.log("Server has started up");
});
