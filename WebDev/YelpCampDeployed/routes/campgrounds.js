
var express = require("express");
var router = express.Router();
var Campground = require("../models/campground");
var NodeGeocoder = require('node-geocoder');
var options = {
	provider: 'google',
	httpAdapter: 'https',
	apiKey: 'AIzaSyDnaeNfasSZKX6j9MMB7oRvruj2W2L81oA',
	formatter: null
};
var geocoder = NodeGeocoder(options);



/*----------   INDEX	-------	*/
router.get("/", function(req, res){
	// GET ALL CAMPGROUNDS FROM DB
	console.log(req.user);
	Campground.find({}, function(err, allCampgrounds){
	if(err){
		console.log(err);
	}
	else{
		res.render("campgrounds/index", {campgrounds:allCampgrounds, currentUser: req.user });
	}
   
   });

//	res.render("campgrounds",{campgrounds:campgrounds});
});


/*----------   CREATE	-------	*/
//CREATE - add new campground to DB
router.post("/", isLoggedIn, function(req, res){
  // get data from form and add to campgrounds array
  var name = req.body.name;
  var image = req.body.image;
  var desc = req.body.description;
  var author = {
      id: req.user._id,
      username: req.user.username
  }
  console.log(geocoder);
  geocoder.geocode(req.body.location, function (err, data) {
	console.log(req.body.location);
	console.log(res);
	console.log(err);
    if (err) {
//      req.flash('error', 'Invalid address');
      return res.redirect('back');
    }
    var lat = data[0].latitude;
    var lng = data[0].longitude;
    var location = data[0].formattedAddress;
    var newCampground = {name: name, image: image, description: desc, author:author, location: location, lat: lat, lng: lng};
    // Create a new campground and save to DB
    Campground.create(newCampground, function(err, newlyCreated){
        if(err){
            console.log(err);
        } else {
            //redirect back to campgrounds page
            console.log(newlyCreated);
            res.redirect("/campgrounds");
        }
    });
  });
});



/*----------   NEW	-------	*/
router.get("/new", isLoggedIn, function(req, res){
	res.render("campgrounds/new");
});


/*----------   SHOW	-------	*/
router.get("/:id", function(req, res){
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



//EDIT CAMPGROUND ROUTE
router.get("/:id/edit", function(req, resp){
	Campground.findById(req.params.id, function(err, foundCampground){
	if(err){res.redirect("/campgrounds")}
	else{

	resp.render("campgrounds/edit", {campground: foundCampground});
	}

	});


});




// UPDATE CAMPGROUND ROUTE
router.put("/:id", function(req, res){
  geocoder.geocode(req.body.location, function (err, data) {
    if (err || !data.length) {
      req.flash('error', 'Invalid address');
      return res.redirect('back');
    }
    req.body.campground.lat = data[0].latitude;
    req.body.campground.lng = data[0].longitude;
    req.body.campground.location = data[0].formattedAddress;

    Campground.findByIdAndUpdate(req.params.id, req.body.campground, function(err, campground){
        if(err){
            res.redirect("back");
        } else {
            res.redirect("/campgrounds/" + campground._id);
        }
    });
  });
});


// DESTROY CAMPGROUND ROUTE
router.delete("/:id", function(req, resp){

	Campground.findByIdAndRemove(req.params.id, function(err){

	if(err){resp.redirect("/campgrounds")}

	else{resp.redirect("/campgrounds")}


	});


})













//Middleware to make sure that only logged in users could add comments
function isLoggedIn(req, resp, next){
	if(req.isAuthenticated()){
		return next();
	}
	resp.redirect("/login");

}







module.exports = router;
