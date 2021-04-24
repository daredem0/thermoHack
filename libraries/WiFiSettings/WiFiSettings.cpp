/**
 * @file WiFiSettings.cpp
 * @author Florian Leuze (3308288) <st155013@stud.uni-stuttgart.de>
 * @date 2020.05.21
 * @brief WiFiSettings Class cpp file
 */

#include <WiFiSettings.h>
const int WiFiSettings::port = 32;

WiFiSettings::WiFiSettings(char* s, char* p):ssid(s),pass(p){
    WiFi.begin(ssid, pass);
    Serial.println("Connecting to: ");
    Serial.println(ssid);
    while(WiFi.status() != WL_CONNECTED){
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    ip = WiFi.localIP();
    Serial.println(ip);
    Server = new WiFiServer(port);
    Server->begin();
    Serial.print("Port: ");
    Serial.println(port);
}

WiFiSettings::WiFiSettings(const WiFiSettings& orig){
}

WiFiSettings::~WiFiSettings(){
    if(ssid != NULL)
        free(ssid);
    if(pass != NULL)
        free(pass);
    delete Server;
}

char* WiFiSettings::getSsid(){
    return ssid;
}

WiFiServer* WiFiSettings::getServer(){
    return Server;
}

WiFiClient* WiFiSettings::getRemoteClient(){
    return &RemoteClient;
}

void WiFiSettings::connectClient(){
    RemoteClient = Server->available();
}

void WiFiSettings::checkForClients(){
    if(Server->hasClient()){
        if(RemoteClient.connected()){
            Serial.println("Connection rejected");
            Server->available().stop();
        }
        else{
            Serial.println("Connection accepted");
            RemoteClient = Server->available();
            RemoteClient.write(ssid);
            Serial.print("I sent: ");
            Serial.println(ssid);
            delay(10);
            char str[4];
            snprintf(str, sizeof(str), "%i", ip[0]);
            RemoteClient.write(str);
            Serial.print("I sent: ");
            Serial.println(str);
            delay(10);
            snprintf(str, sizeof(str), "%i", ip[1]);
            RemoteClient.write(str);
            Serial.print("I sent: ");
            Serial.println(str);
            delay(10);
            snprintf(str, sizeof(str), "%i", ip[2]);
            RemoteClient.write(str);
            Serial.print("I sent: ");
            Serial.println(str);
            delay(10);
            snprintf(str, sizeof(str), "%i", ip[3]);
            RemoteClient.write(str);
            Serial.print("I sent: ");
            Serial.println(str);
            delay(10);
            snprintf(str, sizeof(str), "%i", port);
            RemoteClient.write(str);
            Serial.print("I sent: ");
            Serial.println(str);
        }
    }
}


int WiFiSettings::echoReceivedData(uint8_t* receiveBuffer, size_t s, bool b){
   int received = 0;
   while(RemoteClient.connected() && RemoteClient.available()){
        received = RemoteClient.read(receiveBuffer, s);
        if(b == true)
            RemoteClient.write(receiveBuffer, received);
        Serial.print("Received: ");
        for(int i = 0; i < received; ++i){
            if(receiveBuffer[i] != 10)
                Serial.println((char)receiveBuffer[i]);
            yield();
        }
   }    
   return (received > 1 || receiveBuffer[0]!=10) ? received : 0;
}



























