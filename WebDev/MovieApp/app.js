var express = require("express");
var app = express();
var request = require("request");
app.set("view engine", "ejs");


/*
app.get("/results", function(req, res){
	request("http://www.omdbapi.com/?s=fast&apikey=a44575f2", function(error, response, body){
	if(!error && response.statusCode == 200)
	{
		var results = JSON.parse(body);
		res.send(results["Search"][0]);
//		console.log(typeof body);
//		res.send(body);
	}
  });
});
*/



app.get("/", function(req, res){
	res.render("Search");

});






//Now we're rendering to another ejs page, to 
// redirect the client to another page
app.get("/results", function(req, res){
	var query = req.query.search;
	request("http://www.omdbapi.com/?s="+query+"&apikey=a44575f2", function(error, response, body){
	if(!error && response.statusCode == 200)
	{
		var movieList = JSON.parse(body);
		res.render("land1", {data: movieList}); 
	}
  });
});






app.listen(3000, function(){
	console.log("Movie project has started");

});
