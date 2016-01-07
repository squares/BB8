// BB-8 Lighting code - Version 1.0

#include <Thread.h>
#include <ThreadController.h>
#include <LogicBlock.h>

// INITIALIZE ALL BLOCKS OF LEDS USING THE LOGICBLOCK OBJECT (startpin, numpins, mode, timeout)
LogicBlock logic1(0,4,0,100); // BLUE LOGIC PANEL
LogicBlock logic2(4,5,0,50); // WHITE LOGIC PANEL 1
LogicBlock logic3(11,5,0,5); // WHITE LOGIC PANEL 2
LogicBlock radar(9,1,0,20);

// SET UP THREADS FOR EACH OF THE BLOCKS
ThreadController controller = ThreadController(); // This will hold pointers to all of the threads

Thread psiThread = Thread();
Thread holoThread = Thread();
Thread logic1Thread = Thread(); // TOP WHITE LOGIC
Thread logic2Thread = Thread(); // BOTTOM WHITE LOGIC
Thread logic3Thread = Thread(); // BLUE LOGIC
Thread radarThread = Thread();
Thread randomizerThread = Thread(); // Controls random display in one of the clusters

// Random vars
int randomizerTimeout = random(3000,5000);

// AUDIO analysis - Reserved for future use.
int sensorPin = 8;
int sensorValue = 0;

// RGB VARS - Note, these pin references are to pins in the lighting rig, not the arduino.
  int PSIRedPin = 16;
  int PSIGreenPin = 17;
  int PSIBluePin = 18;
  
  int HoloRedPin = 19;
  int HoloGreenPin = 20;
  int HoloBluePin = 21;

  int PSITimeout = random(1000,9000);
  int PSIColor = 1; // 0 - Blue; 1 - White
  int HoloRedTarget = 255;
  int HoloGreenTarget = 255;
  int HoloBlueTarget = 255;
  int HoloRed = 200;
  int HoloGreen = 200;
  int HoloBlue = 200;


// SHIFTPWM SETTINGS
  const int ShiftPWM_latchPin=22; // YELLOW
// ATTEMPING TO FREE UP SPI FOR SD CARD READER
  #define SHIFTPWM_NOSPI
  const int ShiftPWM_dataPin = 24; // BLUE
  const int ShiftPWM_clockPin = 26; // GREEN 
  const bool ShiftPWM_invertOutputs = false; 
  const bool ShiftPWM_balanceLoad = false;
#include <ShiftPWM.h>   // include ShiftPWM.h after setting the pins!

// SHIFTPWM VARS
  unsigned char maxBrightness = 200;
  unsigned char pwmFrequency = 75;
  int numRegisters = 3;
  int numRGBleds = numRegisters*8/3;

void setup(){
  Serial.begin(9600);

  ShiftPWM.SetAmountOfRegisters(numRegisters);
  ShiftPWM.Start(pwmFrequency,maxBrightness);

  // SET UP ALL OF THE THREADS
  psiThread.setInterval(PSITimeout);
  psiThread.onRun(PSIColorChange);
  
  holoThread.setInterval(5);
  holoThread.onRun(updateHolo);
 
  logic1Thread.setInterval(logic1.getTimeout());
  logic1Thread.onRun(logic1Cycle);

  logic2Thread.setInterval(logic2.getTimeout());
  logic2Thread.onRun(logic2Cycle);
 
  logic3Thread.setInterval(logic3.getTimeout());
  logic3Thread.onRun(logic3Cycle);

  radarThread.setInterval(radar.getTimeout());
  radarThread.onRun(radarCycle);

  randomizerThread.setInterval(5000);
  randomizerThread.onRun(randomizer);

// ADD THREADS TO THREAD CONTROLLER
  controller.add(&psiThread);
  controller.add(&logic1Thread); 
  controller.add(&logic2Thread);
  controller.add(&logic3Thread);
  controller.add(&holoThread);
  controller.add(&radarThread);
  controller.add(&randomizerThread);
  
}

void loop()
{ 
  // get Audio Sensor value, and adjust PSI color accordingly.

  controller.run();  // Check/run all threaded processes.

}



void updateHolo(){
 
  // does current color match target color?
  if (HoloRedTarget == HoloRed && HoloGreenTarget == HoloGreen && HoloBlueTarget == HoloBlue) {
   //Serial.println("New Holo Color");
    // pick a new target color 
      HoloRedTarget = random(50,255);
      HoloGreenTarget = random(50,100);
      HoloBlueTarget = random(50,255);
     
  } else {
    if (HoloRed < HoloRedTarget) { 
        HoloRed++;
    } else if (HoloRed > HoloRedTarget) {
        HoloRed--;
    }
    if (HoloGreen < HoloGreenTarget) { 
        HoloGreen++;
    } else if (HoloGreen > HoloGreenTarget) {
        HoloGreen--;
    }
    if (HoloBlue < HoloBlueTarget) { 
        HoloBlue++;
    } else if (HoloBlue > HoloBlueTarget) {
        HoloBlue--;
    }
  }
  // HoloRed
                ShiftPWM.SetOne(HoloRedPin,HoloRed);
                ShiftPWM.SetOne(HoloGreenPin,HoloGreen);
                ShiftPWM.SetOne(HoloBluePin,HoloBlue);
               
}

void PSIColorChange(){
  
  //Serial.println("Changing colors");
  switch(PSIColor) {
      case 1 :  
               // Serial.println("going white");
                ShiftPWM.SetOne(PSIRedPin,255);
                ShiftPWM.SetOne(PSIGreenPin,255);
                ShiftPWM.SetOne(PSIBluePin,255);
                PSIColor = 2;
                break;
      default : //Serial.println("going blue");
                ShiftPWM.SetOne(PSIRedPin,0); //(GREEN OFF) 
                ShiftPWM.SetOne(PSIGreenPin,0); //(RED OFF) 
                ShiftPWM.SetOne(PSIBluePin,255);
                PSIColor = 1;
                break;
  }
  // reset random light change timer
  PSITimeout = random(1000,9000);
  psiThread.setInterval(PSITimeout);
 
}


// Functions for the threads to call for the cycles 
void logic1Cycle(){
  logic1.cycle();
  for(int p=0; p<4; p++){
    ShiftPWM.SetOne(logic1.startPin + p, logic1.pinValue[p]);  
  }
  logic1Thread.setInterval(logic1.timeoutValue);
}
void logic2Cycle(){
  logic2.cycle();
  for(int p=0; p<5; p++){
    ShiftPWM.SetOne(logic2.startPin+p, logic2.pinValue[p]);  
  }
  logic2Thread.setInterval(logic2.timeoutValue);

}
void logic3Cycle(){
  logic3.cycle();
  for(int p=0; p<5; p++){
    ShiftPWM.SetOne(logic3.startPin+p, logic3.pinValue[p]);  
  }
  logic3Thread.setInterval(logic3.timeoutValue);
}
void radarCycle(){
  radar.cycle();
  for(int p=0; p<1; p++){
    ShiftPWM.SetOne(radar.startPin + p, radar.pinValue[p]);  
  }
}

void resetAllToPulsing() {
  logic1.setMode(0);
  logic2.setMode(0);
  logic3.setMode(0);
  radar.setMode(0);
}

void randomizer(){
  
  logic1.setMode(random(0,3));
    logic2.setMode(random(0,3));
      logic3.setMode(random(0,3));
  randomizerTimeout = random(3000,5000);
}


