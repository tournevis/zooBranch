#define ledPin  13
#define distPin  A0
#include <Process.h>
#include <Bridge.h>
Process process;

char myCharArray[37] = {'a', 'Z', 'z', 'e', 'r', 't', 'A', 'y', 'u', 'E', 'i', 'o', 'p', 'R', 'q', 's', 'T', 'd', 'f', 'Y', ' ', 'h', 'U', 'j', 'k', 'l', 'I', 'm', 'e', 'w', 'O', 'x', 'c', 'v', 'P', 'b', 'n'};
long timeSinceTweet, timeSinceData;
int lastDistSensor;
String key = "token=azerty";
String url = "http://5.196.7.169:8000/api/tweet";
String myTweet ;
int freqTweet = 1000;
bool starting;

int myIntArray[10] = { 0, 0, 0, 0, 0};

void setup() {
  Bridge.begin();
  pinMode(ledPin, OUTPUT);
  pinMode(distPin, INPUT);
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB
  }
  starting = true;
  Serial.print("Starting" );
  timeSinceTweet = 0 ;
  timeSinceData = 0;
  lastDistSensor = 0;
  myTweet = "";
}

void loop() {
  if (starting) {
    delay(1);
    starting = false;
  } else {
    // put your main code here, to run repeatedly:
    int distSensor = analogRead(distPin);
    int med ;
    for(int i ; i< 8;i++){
       med += myIntArray[i];
       myIntArray[i+1] = myIntArray[i];
      }
      myIntArray[0] = distSensor;
     if (  (med /10) - distSensor > 10){
       Serial.println("forward");
      }
      if (  (med /10) - distSensor < 10){
       Serial.println("Backward");
      }
    if ( distSensor != lastDistSensor &&  (millis() - timeSinceData) > freqTweet) {
      int myChar = map(distSensor, 0, 524, 0, 37);
      if (myTweet.length() < 120 && myChar < 37  && myTweet[myTweet.length() - 2] != myCharArray[myChar]) {
        myTweet += myCharArray[myChar] ;
      }
      Serial.print("Dist : " );
      Serial.println(distSensor);
      Serial.print("myTweet : " );
      Serial.println(myTweet);
      timeSinceData = millis();
      delay(10);
    }
    if ( myTweet.length() >= 20 ) {
      tweetPing(myTweet);
    }

    // Si il n'y a pas eu de tweet depuis 2 min et que la chaine de caractères est plus grande de 100 char, et si il n'est pas en train de mesurer
    if ((millis() - timeSinceTweet) > 120000 && myTweet.length() >= 100 ) {
      tweetPing(myTweet);
    }
    // Si le tweet Contient plus de 139 charactère et que le dernier tweet date de la dernière minute
    if ((millis() - timeSinceTweet) > 60000 &&  myTweet.length() >= 130 ) {
      tweetPing(myTweet);
    }
    // Si il n'y a pas eu de tweet depuis 5 heures et qu'il y a plus de 30 charactères
    if ((millis() - timeSinceTweet) > 18000000 && myTweet.length() >= 30) {
      tweetPing(myTweet);
    }

    lastDistSensor = distSensor;
    digitalWrite(ledPin, LOW);
  }
  delay(100);

}
void tweetPing(String Tweet) {
  digitalWrite(ledPin, HIGH);
  Process p;
  String curlCmd;
  curlCmd = "curl " ;
  curlCmd += "-X POST -d \"";
  curlCmd += key;
  curlCmd += "&tweet=" ;
  curlCmd += Tweet;
  curlCmd += "\" " ;
  curlCmd += url;
  p.runShellCommand(curlCmd);
  Serial.println("Posting");
  delay(4000);
  Serial.println(curlCmd);
  Serial.println(Tweet) ;
  myTweet = "";
  // Reset des pararmètres
  timeSinceTweet = millis();

}
