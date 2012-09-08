
#define I2C_SLAVE_ADDRESS 0x4 // the 7-bit address (remember to change this when adapting this example)
#include <TinyWireS.h>

// The default buffer size, Can't recall the scope of defines right now
#ifndef TWI_RX_BUFFER_SIZE
#define TWI_RX_BUFFER_SIZE ( 16 )
#endif


volatile uint8_t i2c_regs[] =
{
  0xDE, 
  0xAD, 
  0xBE, 
  0xEF, 
};

volatile byte reg_position;

///////////////////////////////////////
///////////// setup ///////////////////
///////////////////////////////////////
void setup()
{
  pinMode(4,INPUT); //real 4  
  pinMode(3, OUTPUT); //real 2

  TinyWireS.begin(I2C_SLAVE_ADDRESS);

  TinyWireS.onRequest(requestEvent);

  digitalWrite(3, HIGH);
}


///////////////////////////////////////
///////////// variables  //////////////
///////////////////////////////////////

//deal with output
long current = 0;
long previous = 0;
byte big = 0;
byte small = 0;
boolean changed = true;
boolean firstbyte = true;

///deal with input
boolean hot = false;
int wait = 0;

byte a;
///////////////////////////////////////
///////////// a request ///////////////
///////////////////////////////////////
void requestEvent() //the problem with is that it sends one byte at a time so we need to keep track of which bytes we've sent
{ 
  if(changed == true){ //this is to not send the same data more than once    
    if(firstbyte == true){     // on the first byte we do the math
      big = byte((current-previous)/250);
      small = (current-previous) - (big * 250);    
      firstbyte = false;      //so next time though we send the next byte    
      TinyWireS.send(big);
    } 
    else {
      TinyWireS.send(small);  //we already have it done from the previous run thorugh
      firstbyte = true;
      changed = false;  
    }
  }
  else {
        TinyWireS.send(byte(251));
  }
}


///////////////////////////////////////
///////////// main loop //////////////
///////////////////////////////////////
void loop()
{
  int input = analogRead(2);  

  //we detect if theres input, 
  //if it's not already been measured, 
  //and a cool down because it double beats for each beat  
  if(input > 1000 && hot == false && wait == 0){ 
    hot = true;
    digitalWrite(3,HIGH);
    previous = current;
    current = millis();
    wait = 1000; //wait out period
    changed = true;
  }
  else if(input < 1000 && hot == true) {
    hot = false;
    digitalWrite(3,LOW);
  }

  //cool down mechanism
  if( wait > 0){
    --wait;
  }
  TinyWireS_stop_check();  
}

///////////////////////////////////////
/////////// specific to hear rate /////
//////////////////////////////////////








