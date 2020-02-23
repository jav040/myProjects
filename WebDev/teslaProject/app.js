const express = require("express");
const app = express();
const port = 3000
var path = require("path");


var bodyParser = require("body-parser");

app.use(express.static(path.join(__dirname, '/public')));

app.set("view engine", "ejs");


var accessToken;

var request = require('request').defaults({
    headers: {
        "x-tesla-user-agent": "TeslaApp/3.4.4-350/fad4a582e/android/8.1.0",
        "user-agent": "Mozilla/5.0 (Linux; Android 8.1.0; Pixel XL Build/OPM4.171019.021.D1; wv) AppleWebKit/537.36 (KHTML, like Gecko) Version/4.0 Chrome/68.0.3440.91 Mobile Safari/537.36"}
	});




app.get("/", function(req, resp){

   /* GET ACCESS TOKEN */
     request({
       url: 'https://owner-api.teslamotors.com/oauth/token',
       method: 'POST',
       json: true,
       gzip: true,
       body: {
         "grant_type": 'password',
         "client_id": '81527cff06843c8634fdc09e8ac0abefb46ac849f38fe1e431c2ef2106796384',
         "client_secret":'c7257eb71a564034f9419ee651c7d0e5f7aa6bfbd18bafb5c5c033b093bb2fa3',
         "email": 'jav040@ucsd.edu',
         "password": 'tesla123'
       },
      }, function(err, res, body) {
       console.log("about to print the response status code:");
       console.log(res.statusCode);
       console.log("About to print the body:");
       console.log(body);
       accessToken = body.access_token;
       console.log("variable form access token is: " + accessToken);
     
     
     
            /* GET THE VEHICLE ID NUMBER */
            request({
            url: 'https://owner-api.teslamotors.com/api/1/vehicles',
            method: 'GET',
            headers: { "Authorization": "Bearer " + accessToken, "Content-Type": "application/json; charset=utf-8" } 
           
           }, function(err, res, body) {
            console.log("about to print the access token for ID get call: " + accessToken);
            console.log("about to print the response status code(2):");
            console.log(res.statusCode);
            console.log("About to print the body(2):");
            console.log(body);
	    console.log(typeof(body));
            parsedBody = JSON.parse(body);
	    console.log("now the type of parsedBody is: " + typeof(parsedBody));
	    var vehicleID = parsedBody.response[0].id;
	    console.log("the vehicle_id is: " + vehicleID);
	    resp.render('index', {hi: accessToken} );
	      
	    console.log("the type of vehicleID specifically is: " + typeof(vehicleID));

	    var vehicleIDString = vehicleID.toString();
	    console.log("This should be a string right? " + typeof(vehicleIDString) );
	    var finalURL = 'https://owner-api.teslamotors.com/api/1/vehicles/' + vehicleIDString + '/vehicle_data';
	    console.log("final url is: " + finalURL);
	    console.log("For a sanity check, the access token is: " + accessToken);
	    console.log("the type of the final URL is: " + typeof(finalURL));	
		
			/*	Get Vehicle Data	*/
			request({
					
				method: 'GET',
				url: 'https://owner-api.teslamotors.com/api/1/vehicles/' + vehicleIDString + '/vehicle_data',
            			headers: { "Authorization": "Bearer " + accessToken, "Content-Type": "application/json; charset=utf-8" } 

			}, 
				function(err, res, body){    
					
				console.log("the last status code is: " + res.statusCode);
				console.trace();

			});

			



	



   
     
      });//END VEHICLE ID NUMBER REQUEST
     
     
     });//END ACCESS TOKEN REQUEST

});




/* HIT ANY ENDPOINT WE WANT */







app.listen(port, () => {console.log('Example app listening on port ${port}!') } )
