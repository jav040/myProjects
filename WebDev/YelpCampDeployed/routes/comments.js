var express = require("express");
var router = express.Router({mergeParams: true});
// ^ this line merges the params from the campground and the comments together
var Campground = require("../models/campground");
var Comment = require("../models/comment");





/*----------   COMMENT  	-------	*/
router.get("/new", isLoggedIn ,function(req, resp){
						//Find campground by ID
					   Campground.findById(req.params.id, function(err, campground){
  if(err){console.log(err)}
  else{resp.render("comments/new", {campground: campground});}

}
					   );	
})

// CREATE A NEW COMMENT

router.post("/", isLoggedIn, function(req, resp){
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
					

					//add username and id to comments 
					comment.author.id = req.user._id;
					comment.author.username = req.user.username;

					//and then save comment
					comment.save();
					campground.comments.push(comment);
					campground.save();
					console.log(comment);
					resp.redirect("/campgrounds/" + campground._id);		

				}
			});


		}

	});
	//Create new comment
	//connect new comment to campground
	//redirect to campground show page

})



//Middleware to make sure that only logged in users could add comments
function isLoggedIn(req, resp, next){
	if(req.isAuthenticated()){
		return next();
	}
	resp.redirect("/login");

}








module.exports = router;
