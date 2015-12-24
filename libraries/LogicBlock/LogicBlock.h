#ifndef LogicBlock_H
#define LogicBlock_H

#include <Arduino.h> 
#include <CShiftPWM.h>

class LogicBlock {
  public:
    LogicBlock(int startPin, int numPins, int mode, int timeoutValue);
    ~LogicBlock();
    void cycle(); // This is the main function for handling the display of the mode
    void setMode(int m);
    int getMode();
    int getTimeout();
    void updateTimeout(int newTimeout);
    int nextMode();
    

  	int mode; // THIS SPECIFIES THE MODE THIS BLOCK OF LED'S SHOULD BE RUNNING IN AT ANY GIVEN TIME.
    int timeoutValue; // THIS IS THE TIMEOUT VALUE.  CHANGING MODES MAY REQUIRE THIS TO CHANGE
  	int startPin; // THE PIN THE BLOCK STARTS AT
  	int numPins; // 1(RADAR), 3(RGB), 4, 5
  	int pinValue[5];
  	
  	int pinPointer = 0; // This is for the racing lights modes;
  	int fadeValue = 50; // This stores the value for the pins as it's cycling through.
  	int fadeDirection = 0; // This stores if we're fading up or down in most modes.
    int randomPin = 0;
    int maxBrightness = 255;
};

#endif

