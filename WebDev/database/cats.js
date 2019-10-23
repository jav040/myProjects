var mongoose = require("mongoose");
mongoose.connect("mongodb://localhost/cat_app");

var catSchema = new mongoose.Schema({
	name: String,
	age: Number,
	temperament: String


});

var Cat = mongoose.model("Cat", catSchema);

/*
var george = new Cat({
	name: "George", 
	age: 11,
	temperament: "Grouchy"
});

*/

/*
var george = new Cat({
	name: "Garfield", 
	age: 11,
	temperament: "Lazy"
});
*/
/*
george.save(function(err, cat){

	if(err){
		console.log("SOMETHING WENT WRONG");
	}else{
		console.log("JUST SAVED A CAT TO THE DATABASe:");
		console.log(cat);
	}
});
*/


/* A NEW METHOD CALLED CREATE, WHICH COMBINES THE ABOVE 'NEW' AND 'SAVE' PROCEDURES */

Cat.create({
	name: "Snow White",
	age: 15,
	temperatment: "nice"
}, function(err, cat){
	if(err){
		console.log(err);
	}
	else
	{
		console.log(cat);
	}

});



Cat.find({}, function(err, cats){
	if(err){
		console.log("OH NO, ERROR!");
		console.log(err);
	}
	else{
		console.log("ALL THE CATS");
		console.log(cats);
	}

});

//Adding a new cat to the database

//Retrieve all cats from the database, and console.log each one. 
