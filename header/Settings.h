/**
 * @file Settings.h
 * @author Florian Leuze (3308288) <st155013@stud.uni-stuttgart.de>
 * @date 2020.05.21
 * @brief Settings Class header file
 */

#ifndef SETTINGS_H
#define SETTINGS_H

#define LENGTH(a) sizeof (a)/sizeof (a[0])
#define ANSWER_DAY 10
#define ANSWER_WEEK 19
#define SEPERATOR '/'
#define UNTIL '-'
#define TERMINATOR '\0'
#define ANSWER 'a'
#define WEEK 'w'
#define DAY 'd'

#include "./Day.h"
#include <math.h>
#include <iostream>
#include <stdio.h>

class Settings{
public:
    Settings();
    Settings(const Settings& orig);
    virtual ~Settings();
    
    int set(char* command);
    int setWeek(char* command);
    int setDay(char* command);
    
    char* get(char* command);
    char* getWeek();
    char* getDay(uint8_t d);
private:
    Day day[7];
    
    char* parser(char* com);
    int getInt(char* com, uint16_t start, uint16_t* dest);
    int dayParser(char* com, int weekMode, int* pos, uint8_t it = 1);
    size_t intToChar(int val, char* number);
    int countDigits(int val);
    int insertTemp(char* dest, char* sourceA, char* sourceB, size_t size_A, size_t size_B, size_t start);
    int findBlocks(char* com, uint16_t start);
    int getFloat(char* com, uint16_t start, float* temp);
    float getTemp(int16_t *buff, int16_t dcount, uint16_t counter);
    size_t blockSize(char* com, uint16_t start);
};

#endif /*SETTGINGS_H*/
