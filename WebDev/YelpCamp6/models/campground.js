var mongoose = require("mongoose");

//SCHEMA SETUP
var campgroundSchema = new mongoose.Schema({
	name: String,
	image: String,
	description: String,
	comments: [
		{
			type: mongoose.Schema.Types.ObjectId,
			ref : "Comment" //Here should go the name of the model

		}
	]
});

//Now compile this into a model, so we can have a bunch of methods
var Campground = mongoose.model("Campground", campgroundSchema);

module.exports = mongoose.model("Campground", campgroundSchema);
