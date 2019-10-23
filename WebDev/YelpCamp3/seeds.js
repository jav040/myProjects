var mongoose = require("mongoose");
var Campground = require("./models/campground");


//Define some data
var data = [

	{name: "pretend1", image: "https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcTIjixE9aeN3q9L64kJTAqcsEdiYgNy4wNb7VmlDd74LBallJc2&s", description: "description1"},

	{name: "pretend2", image: "https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcTIjixE9aeN3q9L64kJTAqcsEdiYgNy4wNb7VmlDd74LBallJc2&s", description: "description2"},


	{name: "pretend3", image: "https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcTIjixE9aeN3q9L64kJTAqcsEdiYgNy4wNb7VmlDd74LBallJc2&s", description: "description3"}

]



function seedDB(){
Campground.deleteMany({}, function(err){
		if(err){
			console.log(err);
		}	
		else{
		console.log("removed campgrounds");
	
		data.forEach(function(seed){
			Campground.create(seed, function(err, data){
				if(err)
				{
					console.log(err)
				}
				else
				{
					console.log("added CG!")
				}
			 }
			                 );
		                           }
	                    );
                }
				   }
);
}	
module.exports = seedDB;
