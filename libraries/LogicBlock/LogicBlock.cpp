#include "LogicBlock.h"

#include "CShiftPWM.h"


//<<constructor>>
LogicBlock::LogicBlock(int sP, int nP, int m, int tV){
	
	this->numPins = nP;
	this->startPin = sP;
	this->mode = m;
	this->timeoutValue = tV;
  
}

//<< destructor >>
LogicBlock::~LogicBlock(){/*nothing to destruct?*/}

void LogicBlock::cycle(){

	if(this->mode == 0){
		updateTimeout(5);
      if(this->fadeValue < 255 && this->fadeDirection == 0){
        this->fadeValue++;
      }
      if(fadeValue == 255){
        this->fadeDirection = 1;
      }
      // Fade out all outputs
      if(fadeValue > 0 && fadeDirection == 1){
        this->fadeValue--;
      }
      if(fadeValue == 50){
        this->fadeDirection = 0;
      }
      // SET ALL PINS IN THIS BLOCK TO THE FADEVALUE
	  for(int z=0; z<5; z++){
	  	this->pinValue[z] = fadeValue;      
      }

   }
   else if (this->mode == 1){
	  updateTimeout(300);
	  	for(int z=0; z<5; z++){
	  		this->pinValue[z] = random(0,255);      
	  	}
      
   }
    else if (this->mode == 2){
	    updateTimeout(1000);
	// EVERYTHING OFF  
		for(int z=0; z<5; z++){
	  		this->pinValue[z] = 0;      
	  	}

   } else if (this->mode == 3){
	   // RACING UP
	   updateTimeout(200);
	   
	   	// set all to zero... put one high in order.
	   	for(int z=0; z<5; z++){
	  		this->pinValue[z] = 0;      
	  	}
	  	pinValue[this->pinPointer] = 255;
	  	this->pinPointer++;
	  	if (this->pinPointer > this->numPins){
		  	this->pinPointer = 0;
	  	}
	
   }    
    else {
	   // do nothing
   }
    
}
void LogicBlock::setMode(int m){
	this->mode = m;
}

int LogicBlock::getTimeout(){
	return this->timeoutValue;
}

void LogicBlock::updateTimeout(int newTimeout){
	this->timeoutValue = newTimeout;
}

