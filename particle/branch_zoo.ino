// This #include statement was automatically added by the Particle IDE.
#include "HttpClient/HttpClient.h"

#define ledPin  D7
#define distPin  A0

HttpClient http;

http_header_t headers[] = {
    { "Content-Type", "application/json" },
      //{ "Accept" , "application/json" },
      { "Accept" , "*/*"},
    { NULL, NULL } // NOTE: Always terminate headers will NULL
};

http_request_t request;
http_response_t response;

char myCharArray[59] ;
long timeSinceTweet, timeSinceData;
int lastDistSensor;
String myTweet ;

int freqTweet = 500;

void setup() {

  pinMode(ledPin, OUTPUT);
  pinMode(distPin, INPUT);
  Serial.begin(9600);
  Serial.print("Starting" );
  timeSinceTweet = 0 ;
  timeSinceData = 0;
  lastDistSensor = 0;
  myTweet = "";

    request.hostname = "SETYOURTOKEN";
    request.port = 8080;
    request.path = "/api/tweet";

  for (int i = 0 ; i < 59 ; i++) {
    int j = i;
    j += 42;
    if (j < 46) {
      myCharArray[i] = j ;
    }
    j += 19;
    if ( j>= 65  && j < 91) {
      myCharArray[i] = j ;
    }
    j += 6;
    if ( j>= 97  && j < 122) {
      myCharArray[i] = j ;
    }
    if(i = 58){
      myCharArray[i] = 20;
      }
    Serial.println(myCharArray[i]);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  int distSensor = analogRead(distPin);
  if ( distSensor != lastDistSensor &&  (millis() - timeSinceData) > freqTweet) {
    int myChar = map(distSensor, 0, 1023, 0, 59);
    myTweet += myCharArray[myChar] ;
    Serial.print("Dist : " );
    Serial.println(distSensor);
    timeSinceData = millis();
    delay(10);
  }

  // Si il n'y a pas eu de tweet depuis 2 min et que la chaine de caractères est plus grande de 100 char, et si il n'est pas en train de mesurer
  if ((millis() - timeSinceTweet) > 120000 && myTweet.length() >= 100 && (millis() - timeSinceData) > 4 * freqTweet ) {
    tweetPing(myTweet);
  }
  // Si le tweet Contient plus de 139 charactère et que le dernier tweet date de la dernière minute
  if ((millis() - timeSinceTweet) > 60000 &&  myTweet.length() >= 139 ) {
    tweetPing(myTweet);
  }
  // Si il n'y a pas eu de tweet depuis 5 heures et qu'il y a plus de 30 charactères
  if ((millis() - timeSinceTweet) > 18000000 && myTweet.length() >= 30) {
    tweetPing(myTweet);
  }

  lastDistSensor = distSensor;
  digitalWrite(ledPin, LOW);
  delay(100);

}
void tweetPing(String Tweet) {
    request.body = "{\"tweet\":" + Tweet + ",\"token\":\"azerty\" }";
    delay(100);
    Serial.println("Posting");
    digitalWrite(ledPin, HIGH);
    http.post(request, response, headers);
    Serial.println(Tweet) ;
     // Reset des pararmètres
    timeSinceTweet = millis();
    myTweet = "";
}
