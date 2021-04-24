/**
 * @file main.cpp
 * @author Florian Leuze (3308288) <st155013@stud.uni-stuttgart.de>
 * @date 05.02.2019
 * @brief Main Function network analyzer. Mainly ochestrates the init and gui creation
 */
#include <iostream>
#include "../header/Settings.h"
#include "../header/WiFiSettings.h"

using namespace std;

int main(int argc, char *argv[]) { 
    std::cout << "test" << std::endl;
    Settings* s = new Settings();
    //char* message = "s/w/100-300,200-400,1000-1200/12.5,13,14/500-600,800-900/17,16.5/500-600,1000-1100/20.5,6//";
    //char* message = "s/d/1/100-200/20//";
    //char* message = "s/w/100-200,300-400/20,20.5/100-200/20/300-400/25/500-600/15.5/800-900/22/450-500,550-600/18,18.5/1100-1150,1150-1200,1200-1450/22,23.5,11.5//";
    char* message = "s/d/1/100-200,250-350/20,22//";
    std::cout << message[1] << std::endl;
    std::cout << "hahaha" << std::endl;
    std::cout << "Message: " << message << std::endl;
    std::cout << s->messageHandler(message)<< std::endl;
    message = "s/d/1/100-200,250-350/20,22//";
    std::cout << message[1] << std::endl;
    std::cout << "hahaha" << std::endl;
    std::cout << "Message: " << message << std::endl;
    std::cout << s->messageHandler(message)<< std::endl;
    s->getWeek();
    std::cout << "Testing get methods" << std::endl;
    char* ans = s->messageHandler((char*)"g/d/1//");
    std::cout << "Answer: " << ans  << std::endl;
    free((void*)ans);
    delete s;
    return 0;
}