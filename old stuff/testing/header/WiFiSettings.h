/**
 * @file WiFiSettings.h
 * @author Florian Leuze (3308288) <st155013@stud.uni-stuttgart.de>
 * @date 2020.05.21
 * @brief WiFiSettings Class h file
 */

#ifndef WIFISETTINGS_H
#define WIFISETTINGS_H
#include <stdio.h>
#include <stdlib.h>

//includes n stuff...

/**
 *@brief Stores all Settings of the WiFi Connection 
 */
class WiFiSettings{
public:
    /**
    * @brief Constructor
    * @param char* s: ssid
    * @param char* p: password
    */
    WiFiSettings(char* s, char* p);
    /**
     * @brief Copy Constructor. 
     * @param orig - Reference to original Settings-type object
     */
    WiFiSettings(const WiFiSettings& orig);
    /**
     * Standard deconstructor.
     */
    virtual ~WiFiSettings();
    ///////////////////////////////////************************************************************/
    /**SETTERS AND GETTERS**///////////
    ///////////////////////////////////
    /**
     * @brief Returns the ssid of the connected network
     * @param char* ssid
     */
    char* getSsid();
    static const int port;/**< Port of the tcp server*/
private:
    bool connected; /**< true if connected, else false*/
    char* ssid;/**< ssid of the network*/
    char* pass;/**< password of the network, no getters or setters allowed*/
};

#endif /*WIFISETTINGS_H*/
