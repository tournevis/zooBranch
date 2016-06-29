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


  Pour les gens non familier avec la yun, voir le site d'Arduino qui explique très bien son fonctionement:

  [Arduino Yun](https://www.arduino.cc/en/Guide/ArduinoYun)

## Particle

  Le développement sur les cartes de particle s'effectue sur : https://build.particle.io/build
  On peut retrouver un bon getting started sur leur site :

  [Electron 3G](https://docs.particle.io/guide/getting-started/intro/electron/)

  [Photon](https://docs.particle.io/guide/getting-started/intro/photon/)
  Auparavant on va installer l'outils de commande Particle à l'aide npm :

  ```bash
  sudo npm install -g particle-cli
  particle cloud login
  ```

  Si il y a des problèmes voir la [Documentation](https://github.com/spark/particle-cli)


  Pour flasher la carte, ne pas utiliser le compilateur en ligne de Particle, tout simplement pour évité d'utiliser des datas sur notre abonnement.
  Pour uploader le code dans la carte via usb plusieurs solutions:


 1. Telecherger l'image en .bin en cliquand sur l'icone de download à coté du titre de notre application :

      ![ide](https://docs.particle.io/assets/images/ide-main.png "ide")

      Il faut ensuite passer la carte en mode DFU ( clignotement jaune ) pour se faire :

       a. Maintenir le boutton de RESET et celui de MODE enfoncés

       b. Relâcher le button RESET en restant appuyé sur le button MODE

       c. Attendre que la LED clignote en violet, puis en jaune, tout en restant appuyer sur MODE.

       d. Une fois que ça clignote en jaune, relâcher MODE et uploader le code !

      Pour plus d'infos sur les modes de l'éléctron  : [Les Modes](https://docs.particle.io/guide/getting-started/modes/electron/)
      Pour uploader l'image télécharger on se sert de l'outils de commande particle dans le terminal :
      ```bash
      particle flash --usb myImage.bin
      ```     

  2. Si l'on n'utilise pas l'environnement de développement particle, on se sert du compilateur dans le cloud pour compiler son image

  Passez la carte en mode DFU comme expliquer dans la première solution, puis executez les commandes suivantes

   ```bash
   particle compile photon mySketch.ino --saveTo firmware.bin
   particle flash --usb firmware..bin
   ```     

   En local, attention à bien inclure les librairies, comme HTTP dans le cas présent cf : [Documentation](https://github.com/spark/particle-cli)

  Et enfin pour acceder à notre Serial, et voir ce qu'il se passe on lance la commande :
  ```bash
  particle serial monitor
  ```


##TO DO

  - Implémenter les actions voulu lors des déplacement de l'oiseau ( la détection est faite, mais pour l'instant rien n'a été décidé avec)
  - Uploader le code sur la carte avec les bon liens serveur
  - Ajuster les valeurs en fonction du nouveau capteur
  - Coté Serveur, pensez à mettre les crédits Twitter de prod. Et décommenté le post de twit à la ligne 60

  - Couper du bois :)
  
  - Une moulte bonne alternance à toi !

## Questions ?
 [Ping Me](https://twitter.com/Arth_Rob)
