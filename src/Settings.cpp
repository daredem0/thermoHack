/**
 * @file Settings.cpp
 * @author Florian Leuze (3308288) <st155013@stud.uni-stuttgart.de>
 * @date 2020.05.21
 * @brief Settings Class cpp file
 */

#include "../header/Settings.h"

Settings::Settings(){
    for(int i = 0; i < LENGTH(day); ++i){
        day[i] = Day((char*)Day::nameLookup[i]);
    }
    std::cout << "settings object built" << std::endl;  
}

Settings::Settings(const Settings& orig){
}

Settings::~Settings(){
}
    
/*PUBLIC*/
int Settings::set(char* command){
    std::cout << parser(command) << std::endl;
    return 0;
}
int Settings::setWeek(char* command){
    parser(command);
    std::cout << "Setting seems to have worked" << std::endl;
    return 0;
}
int Settings::setDay(char* command){
    parser(command);
    return 0;
}

char* Settings::get(char* command){
    return parser(command);
}
    
char* Settings::getWeek(){
    for(int i = 0; i < LENGTH(day); ++i){
        std::cout << "Day: " << day[i].getDay() << ":" << std::endl;
        //std::cout << "Start: " << day[i].getStart() << std::endl;
        //std::cout << "End: " << day[i].getEnd() << std::endl;   
    }
    return (char*)"1";
}
char* Settings::getDay(uint8_t d){
    for(int i = 0; i < day[d].getHeatLength(); ++i){
        std::cout << "HeatBlock " << i+1 << std::endl;
        std::cout << "Start: " << day[d].getHeat()[i].getStart() << std::endl;
        std::cout << "End: " << day[d].getHeat()[i].getEnd() << std::endl;
        std::cout << "Temp: " << day[d].getHeat()[i].getTemp() << std::endl;
        
    }
    return (char*)"1";
}

/*PRIVATE*/
int Settings::getInt(char* com, uint16_t start, uint16_t* dest){
    uint8_t length;
    *dest = 0;
    int a = 0;
    for(length = 0; com[start+length] != '-' && com[start+length] != '/' && com[start+length] != ',' && length < 5; ++length){}      
    for(int i = 0; i < length; ++i){
        if(com[start+i] != '-' && com[start+i] != '/' && com[start+i] != ','){
            *dest += (com[start+i]-48) * pow(10, length - 1 - i);
         }
        else
            break;
    }
    return length;
}

int Settings::findBlocks(char* com, uint16_t start){
    int counter = 0;
    for(int i = 0; com[start + i] != '/'; ++i){
        if(com[start+i] == ',') ++counter;
    }
    return counter;
}

size_t Settings::blockSize(char* com, uint16_t start){
    int i;
    for(i = 0; com[start + i] != ',' && com[start+i] != '/'; ++i){
    }
    return i;
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
        if((com[start+i] < 58 && com[start+i] > 47) || com[start+i] == 44 || com[start+i] == 46){
            byteBuffer[counter] = com[start+i];
            if(com[start+i] == 44 || com[start+i] == 46)
                dcount = counter;
            ++counter;
        }
        //yield();
      }
      *temp = getTemp(byteBuffer, dcount, counter);
    }
    return rec;
}

int Settings::dayParser(char* com, int weekMode, int* pos, uint8_t it){
    int d;
    uint16_t s, e;
    float t;
    int blocks_t, blocks_T;
    if(it < 1) *pos -= 2;
    if((com[*pos-1] > 48 && com[*pos-1] < 56) && com[*pos] == '/' && weekMode != 1)
        d = (unsigned)(com[*pos-1] - 48);
    else if(weekMode == 1 && com[*pos] == '/'){
        d = it;
    }
    else{
        return -1; //check consistency of cstring
    }
    //Standard value
    if(com[*pos+1] == '0'){
        s = e = 0;
        *pos += 2;
        if(com[*pos] != '/') return -1; //check consistency of cstring
    }
    else{
        //check how many blocks we have
        blocks_t = findBlocks(com, *pos+1);
        for(int i = 0; i <= blocks_t; ++i){
            *pos += getInt(com, (uint16_t)(*pos+1), &s);
            if(com[*pos+1] != '-') return -1; //check consistency of cstring
            *pos += 2+getInt(com, (uint16_t)(*pos+2), &e);
            if(com[*pos] != '/' && com[*pos] != ',') return -1; //check consistency of cstring
            day[d].setHeat(s, e, 0.0);
        }
    }
    if(com[*pos] != '/')return -1;
    if(com[*pos+1] == '/') return 0;
    else{
        blocks_T = findBlocks(com, *pos+1);
        if(blocks_t != blocks_T) return -1; //check consistency of cstring
        for(int i = 0; i <= blocks_T; ++i){
            *pos += getFloat(com, (uint16_t)(*pos+1), &t);
            std::cout << "Temp: " << t << std::endl;
            if(com[*pos+1] != '/' && com[*pos+1] != ',') return -1; //check consistency of cstring
            day[d].getHeat()[i].setTemp(t);
            *pos += 1;
        }
        
    }
    return 0;
}

int Settings::countDigits(int val){
    int i;
    int base = 10;
    for (i = 1; base <= val; ++i){
        base *= 10;
    }
    return i;
}

size_t Settings::intToChar(int val, char* number){ /*Carefull, adds /0*/
    int count = countDigits(val);
    std::cout << "In int to char" << " val: " << val << " Count: " << count << std::endl;
    std::cout << "malloc ok " << std::endl;
    snprintf(number, sizeof(char) * (size_t)count + 1, "%i", val);
    std::cout << "Generated: " << number << std::endl;
    return (sizeof(char) * (size_t)count);
}

int Settings::insertTemp(char* dest, char* source_A, char* source_B, size_t size_A, size_t size_B, size_t start){
    dest[start + size_A] = '-';
    memcpy((void*)(dest + start), source_A, size_A);
    memcpy((void*)(dest + start + 1 + size_A), source_B, size_B);
    dest[start + size_A + size_B + 1] = SEPERATOR;
}

char* Settings::parser(char* com){
    int writeMode, weekMode; 
    int pos = 5;
    char* err = "error";
    writeMode = com[0] == 'g' ? 0 : (com[0] == 's' ? 1 : -1);
    if(com[1] != '/' || com[3] != '/') return err; //check consistency of cstring
    weekMode = com[2] == 'd' ? 0 : (com[2] == 'w' ? 1 : -1);
    if(writeMode == -1 || weekMode == -1) return err; //check consistency of cstring
    /*writemode*/
    if(writeMode == 1){
        /*daymode*/
        if(weekMode == 0){
            char* test = (char*)dayParser(com, weekMode, &pos);
            return (char*)"0";
        }
        /*weekmode*/
        else if(weekMode == 1){
            int temp = 0;
            for (int i = 0; i < LENGTH(day); ++i){
                temp = dayParser(com, weekMode, &pos,  i);
            }
            temp = com[pos+1] == '/' ? 0 : -1;
            //return (char*)temp;
            return "ok";
        }
    }
    /*readmode*/
    else if (writeMode == 0){
        if(weekMode == 0){
            /*daymode*/
            int d = 0;
            size_t size_S, size_E;
            char* start = (char*) malloc(sizeof(char) * 5);
            char* end = (char*) malloc(sizeof(char) * 5);
            char* answer;
            if((com[pos-1] > 48 && com[pos-1] < 56) && com[pos] == '/' && weekMode != 1)
                d = (unsigned)(com[pos-1] - 48);
            else return err;//check consistency of cstring
            if(com[pos+1] != '/') return err;//check consistency of cstring
            //size_S = intToChar(day[d-1].getStart(), start);
            //size_E = intToChar(day[d-1].getEnd(), end);
            realloc((void*)start, size_S);
            realloc((void*)end, size_S);
            size_t answerLen = sizeof(char) * (size_E + size_S + ANSWER_DAY);
            std::cout << "len: " << answerLen << std::endl;
            answer = (char*) malloc(answerLen);
            answer[0] = ANSWER;
            answer[1] = SEPERATOR;
            answer[2] = DAY;
            answer[3] = SEPERATOR;
            answer[4] = (char) (d + 48);
            answer[5] = SEPERATOR;
            insertTemp(answer, start, end, size_S, size_E, 6);
            answer[answerLen-2] = SEPERATOR;
            answer[answerLen-1] = TERMINATOR;
            free(start);
            free(end);
            return answer;
        }
    
    
    /*weekmode*/
    }
}
