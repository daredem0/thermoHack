void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  float temp = 0;
  int i = 10;
  int counter = 0;
  int t = 0;
  Serial.println("Say something");
  while(Serial.available() < 1){};
  while(true){
    t = Serial.read();
    if(t < 57 && t > 47) {
      temp = (t == 10) ? temp : temp * pow(i,counter) + (t-48);
    //Serial.println(counter, DEC);
    ++counter;
    }
    else if(t == 10){
      break;
    }
    else if(t == 46 || t == 44){
      Serial.println(temp, DEC);
      temp += (Serial.read()-48)*0.1;
      //Serial.println(counter, DEC);
      ++counter;
        
    }
  }
  Serial.println(temp, DEC);
}
