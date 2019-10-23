var express = require("express");
var app = express();
var bodyParser = require("body-parser");
app.set("view engine", "ejs");

app.use(bodyParser.urlencoded({extended: true}));

var campgrounds = [
		{name: "Salmon Creek", image: "https://hips.hearstapps.com/hmg-prod.s3.amazonaws.com/images/camping-quotes-1556677391.jpg?crop=0.588xw:1.00xh;0.157xw,0&resize=640:*"},
		{name: "Granite Hill", image: "https://hips.hearstapps.com/hmg-prod.s3.amazonaws.com/images/camping-quotes-1556677391.jpg?crop=0.588xw:1.00xh;0.157xw,0&resize=640:*"},

		{name: "Mountain Goat's rest", image: "https://www.newzealand.com/assets/Tourism-NZ/Nelson/ba40378fe9/img-1536928144-4748-13836-F53C3949-ED9E-E0DC-CF6EC0D789D9308A__FocalPointCropWzI0MCw0ODAsNTAsNTAsNzUsImpwZyIsNjUsMi41XQ.jpg" } ]





app.get("/", function(req, res){
	res.render("landing");
});

app.get("/campgrounds", function(req, res){

	res.render("campgrounds",{campgrounds:campgrounds});
});


app.post("/campgrounds", function(req, res){
	//Get data from form and add to campgrounds array
	var name = req.body.name;
	var img  = req.body.image;
	var newCampGround = {name: name, image:img};
	campgrounds.push(newCampGround);

	//Redirect back to campgrounds page
	res.redirect("/campgrounds");
});

app.get("/campgrounds/new", function(req, res){

	res.render("new.ejs");

});

app.listen(3000, function(req, res){
	console.log("YelpCamp server has started");

});
