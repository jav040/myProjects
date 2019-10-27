var mongoose = require("mongoose");
var Campground = require("./models/campground");
var Comment = require("./models/comment");

//Define some data
var data = [

	{name: "pretend1", image: "https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcTIjixE9aeN3q9L64kJTAqcsEdiYgNy4wNb7VmlDd74LBallJc2&s", description: "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. "},

	{name: "pretend2", image: "https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcTIjixE9aeN3q9L64kJTAqcsEdiYgNy4wNb7VmlDd74LBallJc2&s", description: "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. "},


	{name: "pretend3", image: "https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcTIjixE9aeN3q9L64kJTAqcsEdiYgNy4wNb7VmlDd74LBallJc2&s", description: "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. "}

]



function seedDB(){
Campground.deleteMany({}, function(err){
		if(err){
			console.log(err);
		}	
		console.log("removed campgrounds");
		data.forEach(function(seed){
			Campground.create(seed, function(err, campground){
				if(err)
				{
					console.log(err)
				}
				else
				{
					console.log("added CG!")
					Comment.create({text: "Uniform comment", author: "jorge"}, function(err, comment){
				if(err){console.log(err)}
				else{
					campground.comments.push(comment);
					campground.save();
					console.log("NEW COMMENTO");
									
				}
					
			       }

						      );
				}
			 }
			                 );
		                           }
	                    );
                
				   }
);
}	
module.exports = seedDB;
