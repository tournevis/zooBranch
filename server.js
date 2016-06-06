var express     = require('express');
var app         = express();
var bodyParser  = require('body-parser');
var Twit        = require('twit');
var secret      = require("./secret.json");

var T = new Twit({
  consumer_key:         secret.twitCred[0]
, consumer_secret:      secret.twitCred[1]
, access_token:         secret.twitCred[2]
, access_token_secret:  secret.twitCred[3]
});

var port = process.env.PORT || 8080; // used to create, sign, and verify tokens

app.listen(port);
console.log('Magic happens at http://localhost:' + port);

// use body parser so we can get info from POST and/or URL parameters
app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());

// USER SETUP
app.get('/', function(req,res){
  return res.json({ success: true, message: 'Welcome to my arduino Yun Tweet Api ' });
});
// API ROUTES -------------------
// we'll get to these in a second
var apiRoutes = express.Router();

apiRoutes.post('/tweet', function(req,res){
    var myTweet = req.body.tweet ;
    var myToken = req.body.token ;
    if( myTweet != "" && myToken == secret.token){
      T.post('statuses/update', { status: "🐦" + myTweet }, function(err, data, response) {
        console.log(data);
      });
      return res.status(200).send({
          success: true,
          message: 'Tweet Sent !'
      });
    }else{
      return res.status(400).send({
          success: false,
          message: 'Wrong Token !'
      });
    }
});
// apply the routes to our application with the prefix /api

app.use('/api', apiRoutes);
