#define LENGTH(a) sizeof (a)/sizeof (a[0])
#define tmin 5
#define tmax 29.5

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:

  Serial.println("Set Temperature");
}

void loop() {
  uint16_t counter = 0;
  uint16_t byteBuffer[4] = {48,48,48,48};
  if(Serial.available()>0){
    while(1){
      char a = Serial.read();
      Serial.print("Run: ");
      Serial.println(counter, DEC);
      Serial.println(a, DEC);
      if(a == 10){
        break;
      }
      byteBuffer[counter] = a;
      counter++;
      delay(5);
    }
  }
}
