/**
 * @file WiFiSettings.cpp
 * @author Florian Leuze (3308288) <st155013@stud.uni-stuttgart.de>
 * @date 2020.05.21
 * @brief WiFiSettings Class cpp file
 */

#include "../header/WiFiSettings.h"
const int WiFiSettings::port = 23;

WiFiSettings::WiFiSettings(char* s, char* p):ssid(s),pass(p){
    
}

WiFiSettings::WiFiSettings(const WiFiSettings& orig){
}

WiFiSettings::~WiFiSettings(){
    if(ssid != NULL)
        free(ssid);
    if(pass != NULL)
        free(pass);
}

char* WiFiSettings::getSsid(){
    return ssid;
}