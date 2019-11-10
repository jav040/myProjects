
var express = require("express");
var router = express.Router();
var passport = require("passport");
var User = require("../models/user");



router.get("/", function(req, res){
	res.render("landing");
});
router.get("/register", function(req, resp){

	resp.render("register");
})

//Handle the sign up
router.post("/register", function(req, resp){
	console.log("made it to before creating new user");
	var newUser = new User({username: req.body.username});
	console.log("made it to after creating new user");
	User.register(newUser, req.body.password, function(err, user){
		console.log("made it to inside of register method");
		console.log(user);
		if(err){
		console.log("last but not least, inside of err");
			console.log(err);
			return resp.render("register");
		}
		console.log("REALLY LAST NOW");
		passport.authenticate("local")(req, resp, function(){
		console.log("made it to secret");
		resp.redirect("/campgrounds");



		});

	});
});


//Show the login form
router.get("/login", function(req, resp){
	resp.render("login");
});

//Handle the login logic
// This logic presumes that the user exists already (i.e. has already registered)
router.post("/login", passport.authenticate("local", 
{successRedirect: "/campgrounds",
 failureRedirect: "/login"


}), 

	function(req, resp){

	resp.send("logic happens here");
})



//LOGOUT ROUTE
router.get("/logout", function(req, resp){

	req.logout();
	resp.redirect("/campgrounds");

})


//Middleware to make sure that only logged in users could add comments
function isLoggedIn(req, resp, next){
	if(req.isAuthenticated()){
		return next();
	}
	resp.redirect("/login");

}


module.exports = router;

