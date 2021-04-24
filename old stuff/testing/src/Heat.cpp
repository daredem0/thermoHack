/**
 * @file Heat.cpp
 * @author Florian Leuze (3308288) <st155013@stud.uni-stuttgart.de>
 * @date 2020.05.21
 * @brief Heat Class source file
 */

#include "../header/Heat.h"

const float Heat::TMAX = 30.0;
const float Heat::TMIN = 4.5;


Heat::Heat(){
    
}

Heat::Heat(uint16_t start, uint16_t end, float temp):startTime(start), endTime(end), t(temp){
    
}
Heat::Heat(const Heat& orig){
    
}
Heat::~Heat(){
    
}


void Heat::setStart(uint16_t start){
    startTime = start;
}

void Heat::setEnd(uint16_t end){
    endTime = end;
}

void Heat::setTemp(float temp){
    t = temp;
}


uint16_t Heat::getStart(){
    return startTime;
}

uint16_t Heat::getEnd(){
    return endTime;
}

float Heat::getTemp(){
    return t;
}