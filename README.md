## Installation
```shell
 npm i
 touch secret.json
```
Then edit the secret.json file with your credit.
You can build the secret.json like this :
```json
{
  "token": "azerty",
  "twitCred":[
    "my_consumer_key",         
    "my_consumer_secret",   
    "my_access_token",         
    "my_access_token_secret"
  ]
}
```
## Launch
```javascript
 node server.js
```

#### If you want to try it out on localhost, Open terminal copy paste this !
```
  curl -X POST -d "token=MYTOKENHERE&tweet=HelloWorld" http://localhost:8080/api/tweet
```
Don't forget to set the same secret, in the secret.json and in the curl request !
