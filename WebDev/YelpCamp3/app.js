var express = require("express");
var app = express();
var bodyParser = require("body-parser");
var mongoose = require("mongoose");
var Campground = require("./models/campground");
var seedDB = require("./seeds");

seedDB();

mongoose.connect("mongodb://localhost/yelp_camp");
app.set("view engine", "ejs");

app.use(bodyParser.urlencoded({extended: true}));

app.get("/", function(req, res){
	res.render("landing");
});




/*----------   INDEX	-------	*/
app.get("/campgrounds", function(req, res){
	// GET ALL CAMPGROUNDS FROM DB
	Campground.find({}, function(err, allCampgrounds){
	if(err){
		console.log(err);
	}
	else{
		res.render("index", {campgrounds:allCampgrounds});
	}
   
   });

//	res.render("campgrounds",{campgrounds:campgrounds});
});


/*----------   CREATE	-------	*/
app.post("/campgrounds", function(req, res){
	//Get data from form and add to campgrounds array
	var name = req.body.name;
	var img  = req.body.image;
	var desc  = req.body.description;
	var newCampGround = {name: name, image:img, description:desc};

	// CREATE A NEW CAMPGROUND AND SAVE TO DATABASE
	
	Campground.create(newCampGround, function(err, newlyCreated){
	if(err){
		console.log(err);
	}
	else{
		//Redirect back to campgrounds page
		res.redirect("/campgrounds");
	}

     });


});


/*----------   NEW	-------	*/
app.get("/campgrounds/new", function(req, res){
	res.render("new.ejs");
});


/*----------   SHOW	-------	*/
app.get("/campgrounds/:id", function(req, res){
	// Find the campground with the provided id
	Campground.findById(req.params.id).populate("comments").exec(function(err, foundCampground){
	if(err){
		console.log(err);
	}else{
		//render that show template with that campground
		console.log(foundCampground);
		res.render("show", {campground: foundCampground});
	}

	});;
});


app.listen(3000, function(req, res){
	console.log("YelpCamp server has started");

});
