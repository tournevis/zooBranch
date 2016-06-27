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

char myCharArray[37] = {a, Z, z, e, r, t, A, y, u, E, i, o, p, R, q, s, T, d, f, Y,  , h, U, j, k, l, I, m, e, w, O, x, c, v, P, b, n};
long timeSinceTweet, timeSinceData;
int lastDistSensor;
String key = "azerty";
String url = "http://localhost:8080/api/tweet";
String myTweet ;
int freqTweet = 1000;
bool starting;

int myIntArray[10] = { 0, 0, 0, 0, 0};
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
    request.hostname = url;
    request.port = 8080;
    request.path = "/api/tweet";
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
    request.body = "{\"tweet\":" +  String( Tweet )+ ",\"token\":" + String( token) +"}";
    delay(100);
    Serial.println("Posting");
    digitalWrite(ledPin, HIGH);
    http.post(request, response, headers);
    if( response ){
      Serial.println(Tweet) ;
    }else{
      Serial.println("Error :") ;
      Serial.println(response)
    }
     // Reset des pararmètres
    timeSinceTweet = millis();
    myTweet = "";
}
