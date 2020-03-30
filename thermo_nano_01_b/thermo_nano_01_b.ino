#define LENGTH(a) sizeof (a)/sizeof (a[0])
#define tmin 4.5
#define tmax 30
#define range 25.5

int incomingByte = 0; // for incoming serial data
float uL = 29.5;
float lL = 5;
//float range = uL-lL;
float stepSize = 0.5;

void setup() {
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
  digitalWrite(2, LOW);
  digitalWrite(4, LOW);
  Serial.println("Init Serial Interface");
}

float getTemp(int16_t *buff, int16_t dcount, uint16_t counter){
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

void serialFlush(){
  while(Serial.available() > 0) {
    char t = Serial.read();
  }
} 

void fixTemp(float *t){
  if((*t-tmin) < 0) *t = tmin;
  if((*t-tmax) > 0) *t = tmax;
}

void tDown(){
  digitalWrite(4, HIGH);
  digitalWrite(2, LOW);
  delay(1);
  digitalWrite(4, LOW);
  delay(1);
  digitalWrite(2, HIGH);
  delay(1);
  digitalWrite(4, HIGH);
  delay(1);
  digitalWrite(2, LOW);
  delay(50);
  /*digitalWrite(2, HIGH);
  digitalWrite(4, HIGH);
  delay(1);
  digitalWrite(4, LOW);
  delay(1);
  digitalWrite(2, LOW);
  delay(1);
  digitalWrite(4, HIGH);
  delay(1);
  digitalWrite(2, HIGH);
  delay(50);*/
}

void tUp(){
  digitalWrite(4, HIGH);
  digitalWrite(2, LOW);
  delay(1);
  digitalWrite(2, HIGH);
  delay(1);
  digitalWrite(4, LOW);
  delay(1);
  digitalWrite(2, LOW);
  delay(1);
  digitalWrite(4, HIGH);
  delay(50);
}

void res(){
  for(int i = 0; i < int(range/stepSize); ++i) tDown();
}

int isNumber(int i){
  if(i > 47 && i < 58) return 1;
  else if (i == 46 || i == 44) return 0;
  else return -1;
}

void loop() {
  float temp = 0;
  int16_t byteBuffer[4] = {48, 48, 48, 48};
  uint16_t counter = 0;
  uint16_t t = 0;
  int16_t dcount = -1;
  Serial.println("Send T to change temperature:");
  delay(1000);
  if(int(Serial.read()) == 84){
    Serial.read();
    Serial.println("Enter temperature:");
    while(Serial.available() <1) {}
    do{
      if(Serial.available() > 4){
        serialFlush();
        Serial.println("error");
        break;
      }
      t = Serial.read();
      if((t < 58 && t > 47) || t == 44 || t == 46){
        byteBuffer[counter] = t;
        if(t == 44 || t == 46)
          dcount = counter;
        ++counter;
      }
      delay(10);
    }while(t != 10);
  
    temp = getTemp(byteBuffer, dcount, counter);
    
    Serial.print("I found: ");
    Serial.println(temp, 1);
    Serial.print("I set: ");
    fixTemp(&temp);
    Serial.println(temp, 1);
    res();
    delay(100);
    for(int i = 0; i < int((temp - tmin)/stepSize); ++i){
      tUp();
    }
  }
}
