var express = require("express");
var mongoose = require("mongoose");
var passport = require("passport");
var bodyParser = require("body-parser");
var LocalStrategy = require("passport-local");
var passportLocalMongoose = require("passport-local-mongoose");
var User = require("./models/user");


mongoose.connect("mongodb://localhost/auth_demo_app");

var app = express();

app.set("view engine", "ejs");

app.use(bodyParser.urlencoded({extended: true}));

app.use(require("express-session")({
	secret: "I like my new apple-watch",
	resave: false,
	saveUninitialized: false
}));


app.use(passport.initialize());
app.use(passport.session());

// use static authenticate method of model in LocalStrategy
passport.use(new LocalStrategy(User.authenticate()));
//^^ Using the local strategy from passport-local-mongoose inside the user file

// use static serialize and deserialize of model for passport session support
passport.serializeUser(User.serializeUser());
passport.deserializeUser(User.deserializeUser());


//-------------------
// ROUTES
//-------------------

app.get("/", function(req, resp){
	resp.render("home");
})

app.get("/secret",isLoggedIn, function(req, res){
	console.log("About to be redirected to secret");
	res.render("secret");
})

//---------------------
//   AUTH ROUTES
//---------------------

//Show sign up form
app.get("/register", function(req, resp){
	resp.render("register");
});

//Handling user sign up
app.post("/register", function(req, resp){
	req.body.username
	req.body.password
	User.register(new User({username: req.body.username}), req.body.password, function(err, user){
	if(err){
		console.log("I got inside the error block");
		console.log(err);
		return resp.render("register");
	}
	passport.authenticate("local")(req, resp, function(){
		console.log("made it to secret");
		resp.redirect("/secret");
							
						  });
});
	
});


//==============
// LOGIN ROUTES
//==============


//GET
app.get("/login", function(req, resp){

	resp.render("login");
});

//===========
//POST
//MIDDLEWARE
//==========
// Compares user inputted password to the hashed version that we have
// stored inside of the database. 
app.post("/login", passport.authenticate("local", 
			{successRedirect: "/secret", 
			failureRedirect: "/login"}), function(req, resp){

							});
//==============
// LOGOUT ROUTES
//==============

app.get("/logout", function(req, resp){
	req.logout();
	resp.redirect("/");

})

function isLoggedIn(req, res, next){
	if(req.isAuthenticated()){
		return next();
	}
	console.log("Instead i landed here");
	res.redirect("/");
}


app.listen(3000, function(req, res)
{
	console.log("Authentication server has started");
})














