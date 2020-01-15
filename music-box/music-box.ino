#include <Arduino.h>

#define impulsOut A0
#define finalOut A1

int impulsTime = 1000;
int inputs[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
int amountOfInputs = 10; // amount of inputs = amount of inputs - 1
boolean inputMode = HIGH; // pullUp
boolean outputMode = HIGH; // normal open pin

boolean lastStateInputs[] = {};

void impulsFunc();
boolean readyFunc();

void setup() {
  for(int i = 0; i < amountOfInputs; i++){
    pinMode(inputs[i], INPUT);
    digitalWrite(inputs[i], HIGH);
    lastStateInputs[i] = digitalRead(inputs[i]);
  }
  pinMode(impulsOut, OUTPUT);
  pinMode(finalOut, OUTPUT);
  digitalWrite(impulsOut, outputMode);
  digitalWrite(finalOut, outputMode);
}

void loop() {
  while(readyFunc()){
    digitalWrite(finalOut, !outputMode);
    readyFunc();
    delay(50);
  }
  digitalWrite(finalOut, outputMode);
  impulsFunc();
  delay(50);
}

void impulsFunc(){
  int stateInputs[] = {};
  boolean change;
  for(int i = 0; i < amountOfInputs; i++){
    stateInputs[i] = digitalRead(inputs[i]);
    change = (lastStateInputs[i] && !stateInputs[i] && !change) ? true : false;
  }
  for(int i = 0; i < amountOfInputs; i++){
    lastStateInputs[i] = stateInputs[i];
  }
  if(change){
    digitalWrite(impulsOut, !outputMode);
    delay(impulsTime);
    digitalWrite(impulsOut, outputMode);
  }
}

boolean readyFunc(){
  boolean tmpVal;
  for(int i = 0; i < amountOfInputs; i++){
    tmpVal = !digitalRead(inputs[i]) ? true : false;
    if(!tmpVal) break;
  }
  return tmpVal;
}
