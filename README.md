## Installation
```shell
 npm i
 touch secret.json
```
Then, edit the secret.json file with your token and your twitter's credits.
If you don't have any you can go to [Twitter Apps](https://apps.twitter.com/) and create an app.

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
you can also use apps like post man :
  [Postman](https://chrome.google.com/webstore/detail/postman/fhbjgbiflinjbdggehcddcbncdddomop)
Don't forget to set the same secret, in the secret.json and in the curl request !



##### French part

## Arduino

  Dans le dossier arduinoYun on retrouve le code pour la carte arduino yun et le capteur de distance : GP2Y0A41SK0F

  [Capteur HackSpark](https://hackspark.fr/fr/ir-distance-sensor-gp2y0a41sk0f-4-30cm-analog-output.html )
  ![schema](http://communityofrobots.com/sites/default/files/images/u1/sharp_ir_arduino_0.jpg "Schema")
  Pour les gens non famillier avec la yun , voir le site d'arduino qui explique très bien son fonctionement:

  [Arduino Yun](https://www.arduino.cc/en/Guide/ArduinoYun)

## Particle

  Le développement sur les cartes de particle s'effectue sur : https://build.particle.io/build
  On peut retrouver un bon getting started sur leur site :
    [Electron 3G](https://docs.particle.io/guide/getting-started/intro/electron/)
    [Photon](https://docs.particle.io/guide/getting-started/intro/photon/)

##TO DO
