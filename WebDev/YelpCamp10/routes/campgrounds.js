
var express = require("express");
var router = express.Router();
var Campground = require("../models/campground");

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
router.post("/", isLoggedIn, function(req, res){
	//Get data from form and add to campgrounds array
	var name = req.body.name;
	var img  = req.body.image;
	var desc  = req.body.description;
	var author = {
		id: req.user._id,
		username: req.user.username	


	}
	var newCampGround = {name: name, image:img, description:desc, author:author};

	// CREATE A NEW CAMPGROUND AND SAVE TO DATABASE
	
	Campground.create(newCampGround, function(err, newlyCreated){
	if(err){
		console.log(err);
	}
	else{
		//Redirect back to campgrounds page
		console.log(newlyCreated);
		res.redirect("/campgrounds");
	}

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
router.get("/:id/edit", checkCampgroundOwnership, function(req, resp){
	Campground.findById(req.params.id, function(err, foundCampground){
	resp.render("campgrounds/edit", {campground: foundCampground});
	});
});




// UPDATE CAMPGROUND ROUTE
router.put("/:id", checkCampgroundOwnership, function(req, resp){

	//find and update the correct campground

	Campground.findByIdAndUpdate(req.params.id, req.body.campground, function(err, updatedCampground){
		if(err){
		resp.redirect("/campgrounds");
		}
		else{
			resp.redirect("/campgrounds/" + req.params.id);
		}
	})	

	//redirect somewhere (the showpage)		

});




// DESTROY CAMPGROUND ROUTE
router.delete("/:id", checkCampgroundOwnership, function(req, resp){

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


function checkCampgroundOwnership(req, resp, next){
if(req.isAuthenticated()){
  Campground.findById(req.params.id, function(err, foundCampground){
    if(err){
	res.redirect("back")
     }
    else{
	//Does user own campground
      if(foundCampground.author.id.equals(req.user._id)){			      next();
      }
      else{
        resp.redirect("back");
      }
     }
  });
	} 
else {
		resp.redirect("back");
	}
}

module.exports = router;
