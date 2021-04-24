/**
 * @file Settings.h
 * @author Florian Leuze (3308288) <st155013@stud.uni-stuttgart.de>
 * @date 2020.05.21
 * @brief Settings Class header file
 */

#ifndef SETTINGS_H
#define SETTINGS_H

#define LENGTH(a) sizeof (a)/sizeof (a[0])
/*#define ANSWER_DAY 9
#define ANSWER_WEEK 19
#define SEPERATOR '/'
#define BLOCKSEP ','
#define UNTIL '-'
#define TERMINATOR '\0'
#define ANSWER 'a'
#define WEEK 'w'
#define DAY 'd'
#define OFFSET_DAY 6*/

#include <Day.h>
#include <math.h>
#include <iostream>
#include <stdio.h>

/**
 *@brief Stores all Settings of the heater like heating time, temperature and week programs
 */
class Settings{
public:
    //CONSTRUCTORS/DECONSTRUCTORS/************************************************************/
    /**
    * @brief Fills the Day type array with correctly named weekdays (mon-sun, always three byte).
    */
    Settings();
    /**
     * @brief Copy Constructor. 
     * @param orig - Reference to original Settings-type object
     */
    Settings(const Settings& orig);
    /**
     * Standard deconstructor.
     */
    virtual ~Settings();
    ///////////////////////////////////************************************************************/
    /**SETTERS AND GETTERS**///////////
    ///////////////////////////////////
    /**
     * @brief Takes a command string and calls methods to extract information. Stores information in day type objects.
     * @param char* command: command string in type like: >> s(g)/d(w)/1/min-min,min2-min2,.../t1,t2,...// or s/w/min-min,t/min,min/t//
     */
    char* messageHandler(char* command);
    
    
    /**
     * @brief For debugging
     * @param char* command: command string in type like: >> s(g)/d(w)/1/min-min,min2-min2,.../t1,t2,...// or s/w/min-min,t/min,min/t//
     */
    char* get(char* command);
    /**
     * @brief For debugging
     */
    char* getWeek();
    /**
     * @brief For debugging
     * @param uint8_t d: integer representing the day (1...7)
     */
    char* getDay(uint8_t d);
    static const int ANSWER_DAY; /**< Offset for day, depracted*/
    static const int ANSWER_WEEK;/**< Offset for week*/
    static constexpr char SEPERATOR = '/';/**< Separator between each major block in the message*/
    static constexpr char BLOCKSEP = ','; /**< Separator between each timeblock/temperature block*/
    static constexpr char UNTIL =  '-';/**< Separator between each time value in a single time block*/
    static constexpr char TERMINATOR = '\0';/**< Standard cstring terminator*/
    static constexpr char ANSWER = 'a'; /**< indicator for an answer*/
    static constexpr char WEEK = 'w'; /**< indicator for a week*/
    static constexpr char DAY = 'd'; /**< indicator for a day*/
    static const int OFFSET_DAY; /**< Offset day*/
    static constexpr char* ERROR = "a/1//";/**< Error in message answer message*/
    static constexpr char* NOERROR = "a/0//";/**< No Error in message answer message*/
private:
    Day day[7];  /**< Stores the values for each day*/
    /**
     * @brief Extracts the header information of the command string (weekmode, send or get mode, aso and calles methods to extract information)
     * @param char* command: command string in type like: >> s(g)/d(w)/1/min-min,min2-min2,.../t1,t2,...// or s/w/min-min,t/min,min/t//
     */
    char* parser(char* com);
    /**
     * @brief Extracts information from the command string and stores it in day type objects
     * @param char* command: command string in type like: >> s(g)/d(w)/1/min-min,min2-min2,.../t1,t2,...// or s/w/min-min,t/min,min/t//
     * @param int weekMode: 1 for true, 0 for false
     * @param int* pos: start position in command string (should be after /)
     * @param uint8_t it: iterator, don't set this in day mode, else put the iterator of an outer loop. dayParser will take this as weekday, should be 1-7
     * @return int: -1 for inconsistent string, 0 for everything ok
     */
    int dayParser(char* com, int weekMode, int* pos, uint8_t it = 2);
    /**
     * @brief Extracts an integer value from the command string between / and - or , or /
     * @param char* command: command string in type like: >> s(g)/d(w)/1/min-min,min2-min2,.../t1,t2,...// or s/w/min-min,t/min,min/t//
     * @param uint16_t start: start position in command string (should be after /)
     * @param uint16_t* dest: destination where to write the integer value
     * @return int: length of the extracted value
     */
    int getInt(char* com, uint16_t start, uint16_t* dest);
    /**
     * @brief Allocates memory for a cstring to store the generated bytes, converts an integer into a cstring. Attention, you are responsible to free the memory later on.
     * @param int val: Integer value that is to be converted.
     * @param char* number: destination, ideally pointer char type pointer to NULL
     * @return size_t: size of the allocated cstring.
     */
    size_t intToChar(int val, char* number);
    /**
     * @brief Allocates memory for a cstring to store the generated bytes, converts an float into a cstring. Attention, you are responsible to free the memory later on.
     * @param float val: float value that is to be converted.
     * @param char* number: destination, ideally pointer char type pointer to NULL
     * @return size_t: size of the allocated cstring.
     */
    size_t floatToChar(float val, char* number);
    /**
     * @brief Counts the digits of an integer number
     * @param int val: Integer that needs to be counted.
     * @return int: Returns the number of digits
     */
    int countDigits(int val);
    /**
     * @brief Inserts two times with - as Separator (like this: xxx-yyy) in between into an existing cstring starting at a definite starting point. Relies on memcpy. This function is not error proof. Know what youre doing
     * @param char* dest: destination string
     * @param char* source_A: xxx time
     * @param char* source_B: yyy time
     * @param size_t size_A: length of source_A
     * @param size_t size_B: length of source_B
     * @param size_t start: start point of insertion
     * @return size_t: -1 for error, 0 for okay (not yet implemented)
     */
    int insertTime(char* dest, char* source_A, char* source_B, size_t size_A, size_t size_B, size_t start);
    /**
     * @brief Inserts two temperatures with - as Separator (like this: xxx-yyy) in between into an existing cstring starting at a definite starting point. Relies on memcpy. This function is not error proof. Know what youre doing
     * @param char* dest: destination string
     * @param char* source_T: temperature
     * @param size_t size_T: length of source_T
     * @param size_t start: start point of insertion
     * @return size_t: -1 for error, 0 for okay (not yet implemented)
     */
    int insertTemp(char* dest, char* source_T, size_t size_T, size_t start);
    /**
     * @brief Extracts a float number out of the command string (for the temperature value). Recognises the decimal point
     * @param char* command: command string in type like: >> s(g)/d(w)/1/min-min,min2-min2,.../t1,t2,...// or s/w/min-min,t/min,min/t//
     * @param uint16_t start: start point of parsing
     * @param float* temp: takes a float type pointer where it will store the value
     * @return int: amount of digits the float number took in the command string (for positioning)
     */
    int getFloat(char* com, uint16_t start, float* temp);
    /**
     * @brief Generates a float value from an int16_t byte buffer, the count of digits before decimal point, and the amount of digits
     * @param int16_t buff: byte buffer containing the values in ASCII
     * @param int16_t dcout: count of digits before decimal point
     * @param uint16_t counter: amount of bytes
     * @return float: generated float value
     */
    float getTemp(int16_t *buff, int16_t dcount, uint16_t counter);
    /**
     * @brief Finds out how many blocks there are inside the string. For example a string like: /100-200,300-400/12,13// is considered to have two blocks
     * @param char* command: command string in type like: >> s(g)/d(w)/1/min-min,min2-min2,.../t1,t2,...// or s/w/min-min,t/min,min/t//
     * @param uint16_t start: start point of parsing
     * @return int: amount of blocks - 1 (basically it counts the commas...)
     */
    int findBlocks(char* com, uint16_t start);
    /**
     * @brief Extracts the size of a block in the command string
     * @param char* command: command string in type like: >> s(g)/d(w)/1/min-min,min2-min2,.../t1,t2,...// or s/w/min-min,t/min,min/t//
     * @param uint16_t start: start point of parsing
     * @return size_t: size of the first block after start
     */
    size_t blockSize(char* com, uint16_t start);
};

#endif /*SETTGINGS_H*/
