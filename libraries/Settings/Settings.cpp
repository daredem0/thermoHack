/**
 * @file Settings.cpp
 * @author Florian Leuze (3308288) <st155013@stud.uni-stuttgart.de>
 * @date 2020.05.21
 * @brief Settings Class cpp file
 */

#include <Settings.h>

const int Settings::ANSWER_DAY = 9;
const int Settings::ANSWER_WEEK = 19;
constexpr char Settings::SEPERATOR;
constexpr char Settings::BLOCKSEP;
constexpr char Settings::UNTIL;
constexpr char Settings::TERMINATOR;
constexpr char Settings::ANSWER;
constexpr char Settings::WEEK;
constexpr char Settings::DAY;
const int Settings::OFFSET_DAY = 6;
constexpr char* Settings::ERROR;
constexpr char* Settings::NOERROR;

//CONSTRUCTORS/DECONSTRUCTORS/************************************************************/
Settings::Settings(){
    //fill the Day type array with correctly named weekdays (mon-sun, always three byte)
    for(int i = 0; i < LENGTH(day); ++i){
        day[i] = Day((char*)Day::nameLookup[i]);
        yield();
    }
    Serial.println("Settings object built");
}

Settings::Settings(const Settings& orig){
}

Settings::~Settings(){
}

///////////////////////////////////************************************************************/
/////**PUBLIC**////////////////////
///////////////////////////////////
char* Settings::messageHandler(char* command){
    //call the parser and print the return value. Actually this handler should just return the parsers return value as soon as this is finished. 
    //Should automatically be returned to the sender as an error or accept message
    return parser(command);
}

//only for debugging
char* Settings::get(char* command){
    return parser(command);
}

//only for debugging
char* Settings::getWeek(){
    for(int j = 0; j < LENGTH(day); ++j){
        Serial.println(day[j].getDay());
        std::cout << day[j].getDay() << std::endl;
        for(int i = 0; i < day[j].getHeatLength(); ++i){
            Serial.print("HeatBlock: ");
            Serial.println(i+1);
            Serial.print("Start: ");
            Serial.println(day[j].getHeat()[i].getStart());
            Serial.print("End: ");
            Serial.println(day[j].getHeat()[i].getEnd());
            Serial.print("Temp: ");
            Serial.println(day[j].getHeat()[i].getTemp());
            yield(); 
        } 
        Serial.println("");
        yield();
    }
    return (char*)"1";
}

//only for debugging
char* Settings::getDay(uint8_t d){
    Serial.print("Heatlength: ");
    Serial.println(day[d-1].getHeatLength());
    for(int i = 0; i < day[d-1].getHeatLength(); ++i){
        Serial.print("HeatBlock: ");
        Serial.println(i+1);
        Serial.print("Start: ");
        Serial.println(day[d-1].getHeat()[i].getStart());
        Serial.print("End: ");
        Serial.println(day[d-1].getHeat()[i].getEnd());
        Serial.print("Temp: ");
        Serial.println(day[d-1].getHeat()[i].getTemp());
        yield();
    }
    return (char*)"1";
}

///////////////////////////////////************************************************************/
/////**PRIVATE**///////////////////
///////////////////////////////////
char* Settings::parser(char* com){
    int writeMode, weekMode; 
    int pos = 5; //initialize position after the header of a daytype message (will be fixed inside dayparser if weekmode is true
    writeMode = com[0] == 'g' ? 0 : (com[0] == 's' ? 1 : -1); //check if the string starts with g for get or s for send, return set writemode to -1 in any other case
    if(com[1] != '/' || com[3] != '/') return ERROR; //check consistency of cstring
    weekMode = com[2] == 'd' ? 0 : (com[2] == 'w' ? 1 : -1);//check if after write/read indicator we find a setting for week or daymode (w/d), else set weekMode to -1
    if(writeMode == -1 || weekMode == -1) return ERROR; //check consistency of cstring
    /*writemode*/
    if(writeMode == 1){
        /*daymode*/
        if(weekMode == 0){
            //call the dayparser to extract information from the command string
            if(dayParser(com, weekMode, &pos) != 0)
                return ERROR;
            else
                return NOERROR;
        }
        /*weekmode*/
        else if(weekMode == 1){
            int temp = 0;
            //loop to iterate for the whole week, call dayparser each time
            for (int i = 0; i < LENGTH(day); ++i){
                temp = dayParser(com, weekMode, &pos,  i);
                if(temp != 0)
                    return ERROR;
                yield();
            }
            if(com[pos+1] != '/')
                return ERROR; 
            return NOERROR;
        }
    }
    /*readmode*/
    else if (writeMode == 0){
        if(weekMode == 0){
            /*daymode*/
            int d;
            if((com[pos-1] > 48 && com[pos-1] < 56) && com[pos] == '/' && weekMode != 1)
                d = (unsigned)(com[pos-1] - 48);
            else return ERROR;//check consistency of cstring
            if(com[pos+1] != '/') return ERROR;//check consistency of cstring
            size_t size_S, size_E, size_T;
            //set up header
            char* start = (char*) malloc(sizeof(char) * 5);
            char* end = (char*) malloc(sizeof(char) * 5);
            char* temp = (char*) malloc(sizeof(char)*6);
            size_t answerLen = OFFSET_DAY;
            size_t answerLen_old;
            char* answer = (char*) malloc(sizeof(char) * answerLen);
            answer[0] = ANSWER;
            answer[1] = SEPERATOR;
            answer[2] = DAY;
            answer[3] = SEPERATOR;
            answer[4] = (char) (d + 48);
            answer[5] = SEPERATOR;
            //insert timeslots
            for(int i = 0; i < day[d-1].getHeatLength(); ++i){
                size_S = intToChar(day[d-1].getHeat()[i].getStart(), start);
                size_E = intToChar(day[d-1].getHeat()[i].getEnd(), end);
                start = (char*)realloc((void*)start, size_S);
                end = (char*)realloc((void*)end, size_S);
                answerLen_old = answerLen;
                answerLen += size_S + size_E + 1;
                answer = (char*)realloc((void*)answer, answerLen);
                insertTime(answer, start, end, size_S, size_E, answerLen_old);
                if(day[d-1].getHeatLength() > 1){
                    answerLen += 1;
                }
                else if(i<day[d-1].getHeatLength()-1)
                    answer[answerLen-1] = BLOCKSEP;
                else
                    ++answerLen;
                yield();
            }
            //insert temperatures
            for(int i = 0; i < day[d-1].getHeatLength(); ++i){
                size_T = floatToChar(day[d-1].getHeat()[i].getTemp(), temp);
                temp = (char*) realloc((void*)temp, size_T);
                answerLen_old = answerLen;
                answerLen += size_T;
                answer = (char*)realloc((void*)answer, answerLen);
                insertTemp(answer, temp, size_T, answerLen_old);
                if(day[d-1].getHeatLength() > 1){
                    answerLen += 1;
                }
                else if(i<day[d-1].getHeatLength()-1)
                    answer[answerLen-1] = BLOCKSEP;
                else
                    ++answerLen;
                yield();
            }
            //insert termination
            answerLen += 2;
            answer = (char*) realloc((void*)answer, answerLen);
            answer[answerLen-2] = SEPERATOR;
            answer[answerLen-1] = TERMINATOR;
            //cleanup
            free(start);
            free(end);
            free(temp);
            return answer;
        }
    
    
    /*weekmode*/
    }
}

int Settings::dayParser(char* com, int weekMode, int* pos, uint8_t it){
    int d;
    uint16_t s, e;
    float t;
    int blocks_t, blocks_T;
    if(it < 1) *pos -= 2; //fix the position if we are in weekmode
    if((com[*pos-1] > 48 && com[*pos-1] < 56) && com[*pos] == '/' && weekMode != 1)
        d = (unsigned)(com[*pos-1] - 49); //evaluate if the position makes sense, if so and we are not in weekmode get the day out of the command string (s/d/x <-)
    else if(weekMode == 1 && com[*pos] == '/'){
        d = it; //if we are in weekmode and the position makes sense then get the day from the iterator
    }
    else{ //if nothing makes sense then gtfo
        return -1; //check consistency of cstring
    }
    //Standard value, to keep the command string simple if we find s/w/0 <- set everything to 0
    if(com[*pos+1] == '0'){
        s = e = 0;
        *pos += 2;
        if(com[*pos] != '/') return -1; //check consistency of cstring
        day[d].getHeat()[0].setTemp(Heat::TMIN); //set tmin
    }
    else{
        //check how many blocks we have
        blocks_t = findBlocks(com, *pos+1);
        for(int i = 0; i <= blocks_t; ++i){ //loop through each block
            *pos += getInt(com, (uint16_t)(*pos+1), &s);
            if(com[*pos+1] != '-') return -1; //check consistency of cstring
            *pos += 2+getInt(com, (uint16_t)(*pos+2), &e);
            if(com[*pos] != '/' && com[*pos] != ',') return -1; //check consistency of cstring
            day[d].setHeat(s, e, 0.0); //add the new heat block 
            yield();
        }
    }
    if(com[*pos] != '/')return -1;//check consistency of cstring
    if(com[*pos+1] == '/') return 0; //check for double / which is the finishing terminator
    else{
        blocks_T = findBlocks(com, *pos+1); //check for the amount of blocks, has to be the same as the amount of blocks we found in the time string
        if(blocks_t != blocks_T) return -1; //check consistency of cstring
        for(int i = 0; i <= blocks_T; ++i){
            *pos += getFloat(com, (uint16_t)(*pos+1), &t);
            if(com[*pos+1] != '/' && com[*pos+1] != ',') return -1; //check consistency of cstring
            day[d].getHeat()[i].setTemp(t); //add the temperature to the heat block
            *pos += 1;
            yield();
        }
    }
    return 0;
}

int Settings::getInt(char* com, uint16_t start, uint16_t* dest){
    uint8_t length;
    *dest = 0;
    int a = 0;
    for(length = 0; com[start+length] != '-' && com[start+length] != '/' && com[start+length] != ',' && length < 5; ++length){yield();}      
    for(int i = 0; i < length; ++i){
        yield();
        if(com[start+i] != '-' && com[start+i] != '/' && com[start+i] != ','){
            *dest += (com[start+i]-48) * pow(10, length - 1 - i);
         }
        else
            break;
    }
    return length;
}

size_t Settings::intToChar(int val, char* number){ /*Carefull, adds /0*/
    int count = countDigits(val);
    snprintf(number, sizeof(char) * (size_t)count + 1, "%i", val);
    return (sizeof(char) * (size_t)count);
}

size_t Settings::floatToChar(float val, char* number){ /*Carefull, adds /0*/
    int count = snprintf(number, sizeof(char) * 5, "%.1f", val);
    return (sizeof(char) * (size_t)count);
}

int Settings::countDigits(int val){
    int i;
    int base = 10;
    for (i = 1; base <= val; ++i){
        base *= 10;
        yield();
    }
    return i;
}

int Settings::insertTime(char* dest, char* source_A, char* source_B, size_t size_A, size_t size_B, size_t start){
    dest[start + size_A] = '-';
    memcpy((void*)(dest+start), source_A, size_A);
    memcpy((void*)(dest + start + 1 + size_A), source_B, size_B);
    dest[start + size_A + size_B + 1] = SEPERATOR;
}

int Settings::insertTemp(char* dest, char* source_T, size_t size_T, size_t start){
    memcpy((void*)(dest+start), source_T, size_T);
    dest[start + size_T] = SEPERATOR;
}

int Settings::getFloat(char* com, uint16_t start, float* temp){
    *temp = -1;
    int16_t byteBuffer[4] = {48, 48, 48, 48};
    uint16_t counter = 0;
    uint16_t t = 0;
    int16_t dcount = -1;
    byteBuffer[0] = 48;
    byteBuffer[1] = 48;
    byteBuffer[2] = 48;
    byteBuffer[3] = 48;
    counter = 0;
    dcount = -1;
    //uint8_t receiveBuffer[30];
    int rec = blockSize(com, start);
    if(rec > 0 && rec <=5){
      for(int i = 0; i < rec; ++i){
        //if((com[start+i] < 58 && com[start+i] > 47) || com[start+i] == 44 || com[start+i] == 46){
        if((com[start+i] < 58 && com[start+i] > 47) || com[start+i] == 46){
            byteBuffer[counter] = com[start+i];
            //if(com[start+i] == 44 || com[start+i] == 46)
            if(com[start+i] == 46)
                dcount = counter;
            ++counter; //exchange that for i later
        }
        yield();
      }
      *temp = getTemp(byteBuffer, dcount, counter);
    }
    return rec;
}

float Settings::getTemp(int16_t *buff, int16_t dcount, uint16_t counter){
  switch(dcount){
    case 0:
      return (buff[1] - 48) * 0.1;
    case 1:
      return buff[0] - 48 + (buff[2] - 48) * 0.1;
    case 2:
      return (buff[0] - 48) * 10 + buff[1] - 48 + (buff[3] - 48)*0.1;
    default:
      return (buff[0]-48) * pow(10,counter-1) + buff[1]-48;
  }
}

int Settings::findBlocks(char* com, uint16_t start){
    int counter = 0;
    for(int i = 0; com[start + i] != '/'; ++i){
        if(com[start+i] == ',') ++counter;
        yield();
    }
    return counter;
}

size_t Settings::blockSize(char* com, uint16_t start){
    int i;
    for(i = 0; com[start + i] != ',' && com[start+i] != '/'; ++i){
        yield();
    }
    return i;
}
