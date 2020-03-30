/**
 * @file Heat.h
 * @author Florian Leuze (3308288) <st155013@stud.uni-stuttgart.de>
 * @date 2020.05.21
 * @brief Heat Class header file
 */

#ifndef HEAT_H
#define HEAT_H
#define tmax 30
#define tmin 4.5
#include <string.h>
#include <stdint.h>
#include <iostream>

class Heat{
public:
    Heat();
    Heat(uint16_t start, uint16_t end, float temp);
    Heat(const Heat& orig);
    virtual ~Heat();
   
    int setStart(uint16_t start);
    int setEnd(uint16_t end);
    int setTemp(float temp);
    
    uint16_t getStart();
    uint16_t getEnd();
    float getTemp();
private:
    uint16_t startTime;
    uint16_t endTime;
    float t;
};

#endif/*HEAT_H*/