var express = require("express");
var app = express();
var bodyParser = require("body-parser");
var mongoose = require("mongoose");

mongoose.connect("mongodb://localhost/yelp_camp");

//SCHEMA SETUP
var campgroundSchema = new mongoose.Schema({
	name: String,
	image: String,
	description: String
});

//Now compile this into a model, so we can have a bunch of methods
var Campground = mongoose.model("Campground", campgroundSchema);



Campground.create(
	{	
		name: "Salmon Creek", 
		image: "https://hips.hearstapps.com/hmg-prod.s3.amazonaws.com/images/camping-quotes-1556677391.jpg?crop=0.588xw:1.00xh;0.157xw,0&resize=640:*",
		description: "This is a huge granite hill, nice!"

        }, function(err, campground){
	if(err){
		console.log(err);
	}
	else{
		console.log("NEWLY CREATED CAMPGROUND: ");
		console.log(campground);
	}
});



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
	Campground.findById(req.params.id, function(err, foundCampground){
	if(err){
		console.log(err);
	}else{
		//render that show template with that campground
		res.render("show", {campground: foundCampground});
	}

	});;
});


app.listen(3000, function(req, res){
	console.log("YelpCamp server has started");

});
