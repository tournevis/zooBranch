// This #include statement was automatically added by the Particle IDE.
#include "HttpClient/HttpClient.h"

#define ledPin  D7
#define distPin  A0

HttpClient http;

http_header_t headers[] = {
    { "Content-Type", "application/json" },
     { "Accept" , "application/json" },
      { "Accept" , "*/*"},
    { NULL, NULL } // NOTE: Always terminate headers will NULL
};

http_request_t request;
http_response_t response;

//Voici le tableau des caractères à tweeter, les majuscules sont remplacé par des emojis coté serveur. Il faudra peut être ajouter des espaces en fonction des tweets désirés
char myCharArray[38] = {'a', 'Z', 'z', 'e', 'r', 't', 'A', 'y', 'u', 'E', 'i', 'o', 'p', 'R', 'q', 's', 'T', 'd', 'f', 'Y', ' ', 'h', 'U', 'j', 'k', 'l', 'I', 'm', 'e', 'w', 'O', 'x', 'c', 'v', 'P', 'b', 'n'};

long timeSinceTweet;
long timeSinceData;
int lastDistSensor;
int birdDir;
/****** SETUP PART *******/

// NOTE: Ne pas oublier de changer le token cote serveur et coté arduino
String token = "azerty";

// NOTE: Ne pas oublier de changer l'URL
String url = "http://localhost:8080/api/tweet";

/********************/

String myTweet ;
int freqTweet = 1000;
bool starting;

//Ce tableau Sert à stocker les dix dernières données récoltés. On fait ensuite une moyenne pour savoir dans quel sens va l'oiseau .
int myIntArray[10] = {0};

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(distPin, INPUT);
  Serial.begin(9600);
  Serial.print("Starting" );
  timeSinceTweet = 0 ;
  timeSinceData = 0;
  lastDistSensor = 0;
  myTweet = "";
  birdDir = 0 ;
  /*** REQUEST SETUP ***/
    request.hostname = url;
    request.port = 8080;
    request.path = '/api/tweet';
}

void loop() {
  //On lit la valeur du cpateur
  int distSensor = analogRead(distPin);

  // On détecte le sens de déplacement de l'oiseau ou si il est reste au même endroit
  int med ;
  for(int i ; i< 8;i++){
     med += myIntArray[i];
     myIntArray[i+1] = myIntArray[i];
    }
    myIntArray[0] = distSensor;
   if (  (med /10) - distSensor > 10){
     Serial.println("forward");
     birdDir = 1 ;
   }else if (  (med /10) - distSensor < -10){
    birdDir = -1 ;
     Serial.println("Backward");
   }else{
     birdDir = 0 ;
   }

  /* Debounce pour ne pas écrire 40 caractère par secondes
    Pour comprendre le debounce :

    https://www.arduino.cc/en/Tutorial/Debounce
  */
  if ( distSensor != lastDistSensor &&  (millis() - timeSinceData) > freqTweet) {
    int myChar = map(distSensor, 0, 1023, 0, 59);
    myTweet += myCharArray[myChar] ;
    Serial.print("Dist : " );
    Serial.println(distSensor);
    timeSinceData = millis();
  }

  // Si il n'y a pas eu de tweet depuis 2 min et que la chaine de caractères est plus grande de 100 char, et si il n'est pas en train de mesurer
  if ((millis() - timeSinceTweet) > 120000 && myTweet.length() >= 100 && (millis() - timeSinceData) > 4 * freqTweet ) {
    //tweetPing(myTweet);
    Serial.print("Posting Disable, tweet : ");
     Serial.println(myTweet);
  }
  // Si le tweet Contient plus de 139 charactère et que le dernier tweet date de la dernière minute
  if ((millis() - timeSinceTweet) > 60000 &&  myTweet.length() >= 139 ) {
      Serial.print("Posting Disable, tweet : ");
     Serial.println(myTweet);
   // tweetPing(myTweet);
  }
  // Si il n'y a pas eu de tweet depuis 5 heures et qu'il y a plus de 30 charactères
  if ((millis() - timeSinceTweet) > 18000000 && myTweet.length() >= 30) {
      Serial.print("Posting Disable, tweet : ");
     Serial.println(myTweet);
    //tweetPing(myTweet);
  }

  lastDistSensor = distSensor;
  digitalWrite(ledPin, LOW);
  delay(100);

}
/* FONCTION POUR ENVOYER UNE REQUEST AU SERVEUR */
void tweetPing(String Tweet) {
    request.body = "{\"tweet\":" +  String( Tweet )+ ",\"token\":" + String( token) +"}";
    delay(100);
    Serial.println(Tweet);
    Serial.println("Posting");
    digitalWrite(ledPin, HIGH);
    http.post(request, response, headers);
     // Reset des pararmètres
    timeSinceTweet = millis();
    myTweet = "";
}
