/**
 * @file Day.h
 * @author Florian Leuze (3308288) <st155013@stud.uni-stuttgart.de>
 * @date 2020.05.21
 * @brief Day Class header file
 */

#ifndef DAY_H
#define DAY_H
#define LENGTH(a) sizeof (a)/sizeof (a[0])

#include "../header/Heat.h"

class Day{
public:
    Day();
    Day(char* n);
    Day(uint8_t n);
    Day(const Day& orig);
    virtual ~Day();
    
    void setHeat(uint16_t start, uint16_t end, float temp);
    void setDay(char* n);
    void setDay(uint8_t n);
    
    Heat* getHeat();
    size_t getHeatLength();
    char* getDay();
    static constexpr char nameLookup[7][4] = {"mon", "tue", "wed", "thu", "fri", "sat", "sun"};
private:
    Heat* heat;
    size_t heatLength;
    char* name;
};
#endif /*DAY_H*/
