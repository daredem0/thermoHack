/**
 * @file Day.cpp
 * @author Florian Leuze (3308288) <st155013@stud.uni-stuttgart.de>
 * @date 2020.05.21
 * @brief Day Class source file
 */

#include "../header/Day.h"
Day::Day(){
    
}

Day::Day(char* n){
    name = (char*) malloc(sizeof(char)*4);
    strcpy(name, n);
    heat = NULL;
    heatLength = 0;
}

Day::Day(uint8_t n){
    name = (char*) malloc(sizeof(char)*4);
    strcpy(name, (char*)nameLookup[n-1]); 
    heat = NULL;
    heatLength = 0;
}

Day::Day(const Day& orig){
    name = NULL;
    name = (char*) malloc(sizeof(char)*4);
    memcpy((void*)name, (void*)orig.name, sizeof(name));
}

Day::~Day(){
    if(name != NULL){
        //free(name);
        name = NULL;
    }
    if(heat != NULL){
        free(heat);
        heat = NULL;
    }
}

void Day::setHeat(uint16_t start, uint16_t end, float temp){
    if(heat == NULL){
        heat = (Heat*) malloc(sizeof(Heat*));
        heatLength = 1;
    }
    else{
        heat = (Heat*)realloc(heat, (heatLength+1)*sizeof(Heat));
        heatLength += 1;
    }
    heat[heatLength-1] = Heat(start, end, temp);
}

void Day::setDay(char* n){
    strcpy(name, n);
}
void Day::setDay(uint8_t n){
    strcpy(name, (char*)nameLookup[n-1]); 
}

Heat* Day::getHeat(){
    return heat;
}

size_t Day::getHeatLength(){
    return heatLength;
}

char* Day::getDay(){
    return name;
}
constexpr char Day::nameLookup[7][4];