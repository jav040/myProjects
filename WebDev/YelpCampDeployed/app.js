var express = require("express");
var app = express();
var bodyParser = require("body-parser");
var mongoose = require("mongoose");
var passport = require("passport");
var methodOverride = require("method-override");
var Campground = require("./models/campground");
var seedDB = require("./seeds");
var Comment = require("./models/comment");
var path = require('path');
var LocalStrategy = require("passport-local");
var User = require("./models/user");
var passport = require("passport");

var commentRoutes    = require("./routes/comments"),
    campgroundRoutes = require("./routes/campgrounds"),
    indexRoutes      = require("./routes/index")
    


//seedDB();

mongoose.connect("mongodb://localhost/yelp_camp", {useFindAndModify: false});
app.set("view engine", "ejs");
app.use('/static', express.static(path.join(__dirname, 'public')))
app.use(bodyParser.urlencoded({extended: true}));
app.use(methodOverride("_method"));




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


app.use(indexRoutes);
app.use("/campgrounds", campgroundRoutes);
app.use("/campgrounds/:id/comments" , commentRoutes);

app.listen(3000, function(req, res){
	console.log("YelpCamp server has started");

});
