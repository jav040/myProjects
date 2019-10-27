var express = require("express");
var app = express();
var bodyParser = require("body-parser");
var mongoose = require("mongoose");
var Campground = require("./models/campground");
var seedDB = require("./seeds");
var Comment = require("./models/comment");
var path = require('path');


seedDB();

mongoose.connect("mongodb://localhost/yelp_camp");
app.set("view engine", "ejs");
app.use('/static', express.static(path.join(__dirname, 'public')))
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
		res.render("campgrounds/index", {campgrounds:allCampgrounds});
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
	res.render("campgrounds/new");
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
		res.render("campgrounds/show", {campground: foundCampground});
	}

	});;
});



/*----------   COMMENT  	-------	*/
app.get("/campgrounds/:id/comments/new", function(req, resp){
						//Find campground by ID
					   Campground.findById(req.params.id, function(err, campground){
  if(err){console.log(err)}
  else{resp.render("comments/new", {campground: campground});}

}
					   );	
})

app.post("/campgrounds/:id/comments", function(req, resp){
	//lookup campground by ID
	Campground.findById(req.params.id, function(err, campground){
		if(err){
			console.log(err)
			resp.redirect("/campgrounds");
		}
		else{
			Comment.create(req.body.comment, function(err, comment){
				if(err){console.log(err)}
				else{
					console.log(campground);
					campground.comments.push(comment);
					campground.save();
					resp.redirect("/campgrounds/" + campground._id);		

				}
			});


		}

	});
	//Create new comment
	//connect new comment to campground
	//redirect to campground show page

})








app.listen(3000, function(req, res){
	console.log("YelpCamp server has started");

});
