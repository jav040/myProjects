var express = require("express");
var app = express();
var bodyParser = require("body-parser");
var mongoose = require("mongoose");
var passport = require("passport");
var Campground = require("./models/campground");
var seedDB = require("./seeds");
var Comment = require("./models/comment");
var path = require('path');
var LocalStrategy = require("passport-local");
var User = require("./models/user");
var passport = require("passport");

seedDB();

mongoose.connect("mongodb://localhost/yelp_camp");
app.set("view engine", "ejs");
app.use('/static', express.static(path.join(__dirname, 'public')))
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



app.use(function(req, resp, next){ 
	resp.locals.currentUser = req.user;
	next();

})




app.get("/", function(req, res){
	res.render("landing");
});




/*----------   INDEX	-------	*/
app.get("/campgrounds", function(req, res){
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
app.get("/campgrounds/:id/comments/new", isLoggedIn ,function(req, resp){
						//Find campground by ID
					   Campground.findById(req.params.id, function(err, campground){
  if(err){console.log(err)}
  else{resp.render("comments/new", {campground: campground});}

}
					   );	
})

app.post("/campgrounds/:id/comments", isLoggedIn, function(req, resp){
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

//Show register form
app.get("/register", function(req, resp){

	resp.render("register");
})

//Handle the sign up
app.post("/register", function(req, resp){
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
app.get("/login", function(req, resp){
	resp.render("login");
});

//Handle the login logic
// This logic presumes that the user exists already (i.e. has already registered)
app.post("/login", passport.authenticate("local", 
{successRedirect: "/campgrounds",
 failureRedirect: "/login"


}), 

	function(req, resp){

	resp.send("logic happens here");
})



//LOGOUT ROUTE
app.get("/logout", function(req, resp){

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






app.listen(3000, function(req, res){
	console.log("YelpCamp server has started");

});
