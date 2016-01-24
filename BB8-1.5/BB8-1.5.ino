/*************************************************** 
  This is a sketch that controls the lights (and in the near future, audio) for the BB-8 Droid.
  Author : Steven Strong
  Last Modified : Today.
  THIS IS THE LATEST VERSION WITH SOME LEVEL OF SOUND SUPPORT
  SOUND MODULE USED: Adafruit Music Maker

  PROBLEMS: The LED animation freezes during sound playback.
    I'm pretty sure this is as a result of the interrupts being used
    by both the shiftpwm library and the mp3 shield.  I have no idea how to get around this yet.

    
 ****************************************************/
 
// include SPI, MP3 and SD libraries
#include <SPI.h>
#include <Adafruit_VS1053.h>
#include <SdFat.h>
SdFat SD;

#include <Thread.h>
#include <ThreadController.h>
#include <LogicBlock.h>

/***********************************************************
*AUDIO SHIELD SETUP 
***********************************************************/
#define SHIELD_RESET  -1      // VS1053 reset pin (unused!)
#define SHIELD_CS     7      // VS1053 chip select pin (output)
#define SHIELD_DCS    6      // VS1053 Data/command select pin (output)
#define CARDCS 4     // Card chip select pin
#define DREQ 3       // VS1053 Data request, ideally an Interrupt pin
Adafruit_VS1053_FilePlayer musicPlayer = Adafruit_VS1053_FilePlayer(SHIELD_RESET, SHIELD_CS, SHIELD_DCS, DREQ, CARDCS);


/***********************************************************
* LED BLOCKS SETUP
***********************************************************/
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
Thread audioThread = Thread(); // awww helll yeahhhh

// Random vars
int randomizerTimeout = random(3000,5000);

// AUDIO analysis - Reserved for future use.
//int sensorPin = 8;
//int sensorValue = 0;

// RGB VARS - Note, these pin references are to pins in the lighting rig, not the arduino.
  int PSIRedPin = 16;
  int PSIGreenPin = 17;
  int PSIBluePin = 18;


  // THIS IS NORMAL
//  int HoloRedPin = 19;
//  int HoloGreenPin = 20;
//  int HoloBluePin = 21;
// THIS IS FOR MY BOARD ONLY
  int HoloRedPin = 21;
  int HoloGreenPin = 22;
  int HoloBluePin = 23;

  
  int PSIColor = 1; // 0 - Blue; 1 - White
  int HoloRedTarget = 255;
  int HoloGreenTarget = 255;
  int HoloBlueTarget = 255;
  int HoloRed = 200;
  int HoloGreen = 200;
  int HoloBlue = 200;


// SHIFTPWM SETTINGS
  const int ShiftPWM_latchPin = 22; // YELLOW
// ATTEMPING TO FREE UP SPI FOR SD CARD READER
  #define SHIFTPWM_NOSPI
  const int ShiftPWM_dataPin = 24; // BLUE
  const int ShiftPWM_clockPin = 26; // GREEN 
  const bool ShiftPWM_invertOutputs = false; 
  const bool ShiftPWM_balanceLoad = false;
#include <ShiftPWM.h>   // include ShiftPWM.h after setting the pins!

// SHIFTPWM VARS
  unsigned char maxBrightness = 200;
  unsigned char pwmFrequency = 93;
  int numRegisters = 3;
  int numRGBleds = numRegisters*8/3;

void setup(){
  Serial.begin(9600);

// AUDIO CONFIG
  if (! musicPlayer.begin()) { // initialise the music player
     Serial.println(F("Couldn't find VS1053, do you have the right pins defined?"));
     while (1);
  }
  Serial.println(F("VS1053 found"));
  musicPlayer.sineTest(0x44, 500);    // Make a tone to indicate VS1053 is working
 
  if (!SD.begin(CARDCS)) {
    Serial.println(F("SD failed, or not present"));
    while (1);  // don't do anything more
  }
  Serial.println("SD OK!");
  musicPlayer.setVolume(40,40);
  musicPlayer.useInterrupt(VS1053_FILEPLAYER_TIMER0_INT);
// END AUDIO CONFIG

  
// SHIFT REGISTERS
  ShiftPWM.SetAmountOfRegisters(numRegisters);
  ShiftPWM.Start(pwmFrequency,maxBrightness);
 
  // SET UP ALL OF THE THREADS
  psiThread.setInterval(40);
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

  audioThread.setInterval(8000);
  audioThread.onRun(pickPlayAudio);

// ADD THREADS TO THREAD CONTROLLER
  controller.add(&psiThread);
  controller.add(&logic1Thread); 
  controller.add(&logic2Thread);
  controller.add(&logic3Thread);
  controller.add(&holoThread);
  controller.add(&radarThread);
  controller.add(&randomizerThread);
  controller.add(&audioThread);
}

void loop()
{ 
  
  controller.run();  // Check/run all threaded processes.
  
}

void pickPlayAudio(){
  String str;
  
  //Serial.println("playing audio file");
  int audioFileNumber = random(1,9);
  str = String(audioFileNumber);
  char filenamePrefix[]   = "BB8-";
  char filenameExtension[] = ".mp3";
  char fileNum[2];
  char combined[10] = {0};
  str.toCharArray(fileNum,2);
  
  strcat(combined, filenamePrefix);
  strcat(combined, fileNum );
  strcat(combined, filenameExtension);

  // FOR SOME REASON, THIS IS NOT RUNNING AS A BACKGROUND PROCESS.  INSTEAD, IT'S ACTING AS THOUGH IT SHOULD PLAY FULL FILE.
  
  if (!musicPlayer.playingMusic){
    if (! musicPlayer.startPlayingFile(combined))  {
    
//        Serial.print("Could not open file ");
 //       Serial.println(combined);
      
    } else {
             Serial.print("Opened ");
             while (musicPlayer.playingMusic){
              Serial.println("this is dumb");
             }
    }
    
  }
}

void updateHolo(){
 
  // does current color match target color?
  if (HoloRedTarget == HoloRed && HoloGreenTarget == HoloGreen && HoloBlueTarget == HoloBlue) {
   //Serial.println("New Holo Color");
    // pick a new target color 
      HoloRedTarget = random(30,150);
      HoloGreenTarget = random(30,150);
      HoloBlueTarget = random(30,150);
     
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

   if (musicPlayer.playingMusic){

  Serial.println("Changing colors");
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
   } else {
      // set blue
                ShiftPWM.SetOne(PSIRedPin,0); //(GREEN OFF) 
                ShiftPWM.SetOne(PSIGreenPin,0); //(RED OFF) 
                ShiftPWM.SetOne(PSIBluePin,255);
   }
  // reset random light change timer
  //PSITimeout = random(1000,9000);
  //psiThread.setInterval(PSITimeout);
 
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


