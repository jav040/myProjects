var express = require("express");
var router = express.Router({mergeParams: true});
// ^ this line merges the params from the campground and the comments together
var Campground = require("../models/campground");
var Comment = require("../models/comment");




//TAKE USER TO THE "ADD NEW COMMENT" FORM, TO CREATE A COMMENT
/*----------   COMMENT  	-------	*/
router.get("/new", isLoggedIn ,function(req, resp){
						//Find campground by ID
					   Campground.findById(req.params.id, function(err, campground){
  if(err){console.log(err)}
  else{resp.render("comments/new", {campground: campground});}

}
					   );	
})

// CREATE A NEW COMMENT, I.E. SAVE TO DATABASE

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



/* RENDER THE "EDIT COMMENT" FORM */
router.get("/:comment_id/edit", checkCommentOwnership, function(req, resp){

	Comment.findById(req.params.comment_id, function(err, foundComment){
	
	if(err){
		resp.redirect("back");
	}
	else{
		resp.render("comments/edit", {campground_id: req.params.id, comment: foundComment});
	}
	
        });

})



/* COMMENTS UPDATE (RETURN TO THE CAMPGROUND, WITH AN UPDATED COMMENT) */
router.put("/:comment_id", checkCommentOwnership, function(req, resp){

	Comment.findByIdAndUpdate(req.params.comment_id, req.body.comment, function(err, updatedComment){
		if(err){
			resp.redirect("back");
		}
		else{
			resp.redirect("/campgrounds/" + req.params.id);
		}

	})

})


//COMMENTS DESTROY ROUTE
router.delete("/:comment_id", checkCommentOwnership, function(req, resp){
	


	Comment.findByIdAndRemove(req.params.comment_id, function(err){
		if(err){
			resp.redirect("back");
		}
		else{
			resp.redirect("/campgrounds/" + req.params.id);
		}
	
	})

});



//Middleware to make sure that only logged in users could add comments
function isLoggedIn(req, resp, next){
	if(req.isAuthenticated()){
		return next();
	}
	resp.redirect("/login");
}




function checkCommentOwnership(req, resp, next){
if(req.isAuthenticated()){
  Comment.findById(req.params.comment_id, function(err, foundComment){
    if(err){
	res.redirect("back")
     }
    else{
	//Does user own comment
      if(foundComment.author.id.equals(req.user._id)){			      
		next();
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
