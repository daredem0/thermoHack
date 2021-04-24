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
/**
 *@brief Stores heating blocks (time and temperature) and offers interfaces to receive and store
 */
class Day{
public:
    //CONSTRUCTORS/DECONSTRUCTORS/************************************************************/
    /**
    * @brief Standard constructor. 
    */
    Day();
    /**
    * @brief Constructor
    * @param char* n: name to be stored in name member ("mon", "tue", ..., "suns")
    */
    Day(char* n);
    /**
    * @brief Constructor
    * @param uint8_t n: name to be stored in name member (1...7), gets name automatically from lookup table, preferred
    */
    Day(uint8_t n);
    /**
     * @brief Copy Constructor. 
     * @param orig - Reference to original Day-type object
     */
    Day(const Day& orig);
    /**
     * Standard deconstructor.
     */
    virtual ~Day();
    ///////////////////////////////////************************************************************/
    /**SETTERS AND GETTERS**///////////
    ///////////////////////////////////
    /**
     * @brief Sets a complete heat block
     * @param uint16_t start: Start time
     * @param uint16_t end: End time
     * @param float temp: temperature
     */    
    void setHeat(uint16_t start, uint16_t end, float temp);
    /**
     * @brief Sets the day name
     * @param char* n: name like "mon", "tue", ..., "sun"
     */   
    void setDay(char* n);
    /**
     * @brief Sets the day name
     * @param uint8_t n: name like (1...7), uses lookup table
     */  
    void setDay(uint8_t n);
    /**
     * @brief Gives a pointer to the heat array
     * @return Heat* type pointer to heat Array
     */
    Heat* getHeat();
    /**
     * @brief Gives length of heat array
     * @return size_t length of heat array
     */
    size_t getHeatLength();
    /**
     * @brief Gives name of weekday
     * @return char* "mon", "tue", ..., "sun"
     */
    char* getDay();
    static constexpr char nameLookup[7][4] = {"mon", "tue", "wed", "thu", "fri", "sat", "sun"}; /**< lookup table for weekdays*/
private:
    Heat* heat; /**< Array to store heat objects. Is allocated in setHeat method*/
    size_t heatLength;/**< Stores the length of the heat array*/
    char* name; /**< name of the stored day*/
};

#endif /*DAY_H*/
