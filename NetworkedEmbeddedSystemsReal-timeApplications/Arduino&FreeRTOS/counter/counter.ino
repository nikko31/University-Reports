
/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  This example code is in the public domain.
 */

// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led[] = {13,12,11,10};

// the setup routine runs once when you press reset:
void setup() {
  // initialize the digital pin as an output.
  for(int i=0;i<4;i++){
    pinMode(led[i], OUTPUT);
  }
}

// the loop routine runs over and over again forever:
void loop() {
  for(int i=0;i<15;i++){
    showNum(i);
    delay(1000);
  }
}
void showNum(int counter){
    for(int i=0;i<4;i++){
      // bitRead gives information about whether certain bits should be 1.
      if(bitRead(counter,i)==1)
        digitalWrite(led[i], HIGH);   // turn the LED on (HIGH is the voltage level)
      else
        digitalWrite(led[i], LOW);    // turn the LED off by making the voltage LOW
  }
}
