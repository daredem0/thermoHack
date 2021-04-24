/**
 * @file Heat.h
 * @author Florian Leuze (3308288) <st155013@stud.uni-stuttgart.de>
 * @date 2020.05.21
 * @brief Heat Class header file
 */

#ifndef HEAT_H
#define HEAT_H
#include <string.h>
#include <stdint.h>
#include <iostream>

/**
 *@brief Stores all valkues of a single heat block which contains start time, end time and temperature
 */
class Heat{
public:
    //CONSTRUCTORS/DECONSTRUCTORS/************************************************************/
    /**
    * @brief Fills the Day type array with correctly named weekdays (mon-sun, always three byte).
    */
    Heat();
    /**
    * @brief Constructor
    * @param uint16_t start: starttime in minutes
     * @param uint16_t end: endtime in minutes
     * @param float temp: temp 
    */
    Heat(uint16_t start, uint16_t end, float temp);
    /**
     * @brief Copy Constructor. 
     * @param orig - Reference to original Settings-type object
     */
    Heat(const Heat& orig);
    /**
     * Standard deconstructor.
     */
    virtual ~Heat();
    ///////////////////////////////////************************************************************/
    /**SETTERS AND GETTERS**///////////
    ///////////////////////////////////
    /**
    * @brief Sets a start time
    * @param uint16_t start: starttime in minutes
    */
    void setStart(uint16_t start);
    /**
    * @brief Sets a end time
    * @param uint16_t end: endtime in minutes
    */
    void setEnd(uint16_t end);
    /**
    * @brief Sets a temperature
    * @param float temp: temp in degrees
    */
    void setTemp(float temp);
    
    /**
    * @brief Getter for start time
    * @return uint16_t starttime in minutes
    */
    uint16_t getStart();
    /**
    * @brief Getter for end time
    * @return uint16_t endtime in minutes
    */
    uint16_t getEnd();/**
    * @brief Getter for temp
    * @return float temp in degrees
    */
    float getTemp();
    static const float TMAX;/**< maximal temperature*/
    static const float TMIN;/**< minimal temperature*/
private:
    uint16_t startTime;/**< starttime*/
    uint16_t endTime;/**< endtime*/
    float t;/**< temperature*/
};

#endif/*HEAT_H*/