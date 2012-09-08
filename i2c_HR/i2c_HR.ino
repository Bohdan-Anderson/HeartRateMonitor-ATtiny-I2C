
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

byte saving[]= {
  1,2,3,4,5,6,7,8};
byte sending[]= {
  1,2,3,4,5,6,7,8};
byte counterT = 0;

boolean hot = false;
int previous = 0;
long start = 0;
int ND = 0;
int wait = 0;

byte a;
///////////////////////////////////////
///////////// a request ///////////////
///////////////////////////////////////
void requestEvent()
{ 
  if(counterT == 0){
    for(a = 0; a < 8; ++a){
      sending[a] = saving[a];
    }
    long temp = millis();
    resetSaving(temp);
  }        

  TinyWireS.send(sending[counterT]);  

  ++counterT;
  if(counterT >= 8){
    counterT = 0;
  }

}


///////////////////////////////////////
///////////// main loop //////////////
///////////////////////////////////////
void loop()
{
  int input = analogRead(2);  
  if(input > 1000 && hot == false && wait == 0){
    hot = true;
    digitalWrite(3,HIGH);
    addToSaving(millis());
    wait = 1000;
  }
  else if(input < 1000 && hot == true) {
    hot = false;
    digitalWrite(3,LOW);
  }

  if( wait > 0){
    --wait;
  }
  TinyWireS_stop_check();  
}

///////////////////////////////////////
/////////// specific to hear rate /////
///////////////////////////////////////

//// the start point of this cycle and previous beat
//// are used to determin in which byte slot should the current beat be saved
void addToSaving(long current){ 
  int fz = current - start + ND;
  
  if(fz < 250){
    saving[0] = fz;
  } 
  else if (fz < 500){
    saving[1] = fz-250;
  } 
  else if (fz < 750){
    saving[2] = fz - 500;
  } 
  else if (fz < 1000){
    saving[3] = fz - 750;
  } 
  else if (fz < 1250){
    saving[4] = fz - 1000;
  } 
  else if (fz < 1500){
    saving[5] = fz - 1250;
  } 
  else if (fz < 1750){
    saving[6] = fz - 1500;
  }  
  else {
    saving[7] = 251;
  }
  
  previous = fz;  
}

void resetSaving(long time){
  ND = time - start - previous;
  start = time;
  //previous = 0;
  for(a = 0; a < 8; ++a){
    saving[a] = 0;    
  }  
}




