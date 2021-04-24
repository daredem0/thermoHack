#define LENGTH(a) sizeof (a)/sizeof (a[0])
#define tmin 4.5
#define tmax 30

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:

  Serial.println("Set Temperature");
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

void loop() {
  // put your main code here, to run repeatedly:
  float temp = 0;
  int16_t byteBuffer[4] = {48, 48, 48, 48};
  uint16_t counter = 0;
  uint16_t t = 0;
  int16_t dcount = -1;
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
}
