#include <ESP8266WiFi.h>
#include <string>
#include <sstream>
#include <cstring>
#include <WiFiSettings.h>
#include <Heat.h>
#include <Day.h>
#include <Settings.h>

#define LENGTH(a) sizeof (a)/sizeof (a[0])
#define tmin 4.5
#define tmax 30
#define range 25.5
#define A 4
#define B 5

//Set up WiFi Stuff
const char *ssid = "Westonia";
const char *pass = "3lm4$p&#-89,5=ua68se?";
WiFiSettings* wifi_set;
Settings* s;

int incomingByte = 0; // for incoming serial data
float uL = 29.5;
float lL = 5;
//float range = uL-lL;
float stepSize = 0.5;
uint32_t del = 0;

void setup() {
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  Serial.println("Init Serial Interface");
  //init wifi settings object to do all the work, pass ssid and password
  wifi_set = new WiFiSettings((char*)ssid, (char*)pass);
  //init settings object
  //s = new Settings();
}

float getTemp(int16_t *buff, int16_t dcount, uint16_t counter){
  switch(dcount){
    case 0:
      return (buff[1] - 48) * 0.1;
    case 1:
      return buff[0] - 48 + (buff[2] - 48) * 0.1;
    case 2:
      return (buff[0] - 48) * 10 + buff[1] - 48 + (buff[3] - 48)*0.1;
    default:
      return (buff[0]-48) * pow(10,counter-1) + buff[1]-48;
  }
}

void serialFlush(){
  while(Serial.available() > 0) {
    char t = Serial.read();
    yield();
  }
} 

void fixTemp(float *t){
  if((*t-tmin) < 0) *t = tmin;
  if((*t-tmax) > 0) *t = tmax;
}

void tDown(){
  digitalWrite(B, HIGH);
  digitalWrite(A, LOW);
  delay(1);
  digitalWrite(B, LOW);
  delay(1);
  digitalWrite(A, HIGH);
  delay(1);
  digitalWrite(B, HIGH);
  delay(1);
  digitalWrite(A, LOW);
  delay(50);
}

void tUp(){
  digitalWrite(B, HIGH);
  digitalWrite(A, LOW);
  delay(1);
  digitalWrite(A, HIGH);
  delay(1);
  digitalWrite(B, LOW);
  delay(1);
  digitalWrite(A, LOW);
  delay(1);
  digitalWrite(B, HIGH);
  delay(50);
}

void res(){
  for(int i = 0; i < int(range/stepSize); ++i) {
    tDown();
    yield();
  }
}

int isNumber(int i){
  if(i > 47 && i < 58) return 1;
  else if (i == 46 || i == 44) return 0;
  else return -1;
}

void loop() {
  float temp = -1;
  int16_t byteBuffer[4] = {48, 48, 48, 48};
  uint16_t counter = 0;
  uint16_t t = 0;
  int16_t dcount = -1;
  wifi_set->checkForClients();
  ++del;
  if(del == 256){
    Serial.println("Send T to change temperature:");
    del = 0;
  }
  delay(15);
  
  if(int(Serial.read()) == 84){
    Serial.read();
    Serial.println("Enter temperature:");
    while(Serial.available() <1) {yield();}
    do{
      if(Serial.available() > 4){
        serialFlush();
        Serial.println("error");
        break;
      }
      t = Serial.read();
      if((t < 58 && t > 47) || t == 44 || t == 46){
        byteBuffer[counter] = t;
        if(t == 44 || t == 46)
          dcount = counter;
        ++counter;
      }
      delay(10);
    }while(t != 10);
  
    temp = getTemp(byteBuffer, dcount, counter);
  }
  else{
    uint8_t receiveBuffer[1000];
    int rec = wifi_set->echoReceivedData(receiveBuffer, sizeof(receiveBuffer), false);
    if(rec > 5){
      Serial.print("Length: ");
      Serial.println(rec);
      receiveBuffer[rec-1] = '\0';
      char* message = (char*) malloc(sizeof(char) * ((size_t)rec));
      memcpy((void*)message, (void*)receiveBuffer, rec);
      char* ans = s->messageHandler(message);
      wifi_set->getRemoteClient()->write(ans);
      s->getDay(1);
      Serial.print("Ans: ");
      Serial.println(ans);
      free(message);
    }
    /*    
    byteBuffer[0] = 48;
    byteBuffer[1] = 48;
    byteBuffer[2] = 48;
    byteBuffer[3] = 48;
    counter = 0;
    dcount = -1;
    uint8_t receiveBuffer[100];
    int rec = wifi_set->echoReceivedData(receiveBuffer, sizeof(receiveBuffer), false);
    if(rec > 0 && rec <=5){
      for(int i = 0; i < rec; ++i){
        if((receiveBuffer[i] < 58 && receiveBuffer[i] > 47) || receiveBuffer[i] == 44 || receiveBuffer[i] == 46){
          byteBuffer[counter] = receiveBuffer[i];
          if(receiveBuffer[i] == 44 || receiveBuffer[i] == 46)
            dcount = counter;
          ++counter;
        }
        yield();
      }
      temp = getTemp(byteBuffer, dcount, counter);
      if(wifi_set->getRemoteClient()->connected()){
        char str[16];
        snprintf(str, sizeof(str), "%.2f", temp);
        wifi_set->getRemoteClient()->write(str);
      }
    }*/
  }

  if(temp != -1){
    Serial.print("I found: ");
    Serial.println(temp, 1);
    Serial.print("I set: ");
    fixTemp(&temp);
    Serial.println(temp, 1);
    res();
    delay(100);
    for(int i = 0; i < int((temp - tmin)/stepSize); ++i){
      tUp();
      yield();
    }
  }
}
