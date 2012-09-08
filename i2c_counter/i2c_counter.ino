
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

double counter = 0;
boolean on = true;

volatile byte reg_position;

void requestEvent()
{ 
    TinyWireS.send(44);
//  TinyWireS.send(i2c_regs[reg_position]);
  // Increment the reg position on each read, and loop back to zero
  //reg_position = (reg_position+1) % sizeof(i2c_regs);
}


void setup()
{
  pinMode(3, OUTPUT);

  TinyWireS.begin(I2C_SLAVE_ADDRESS);

  TinyWireS.onRequest(requestEvent);

  digitalWrite(3, HIGH);
}

void loop()
{
  counter++;
  if(counter > 2000){
    counter = 0;
    if( on == true){
      on = false;
      digitalWrite(3, LOW);      
    } 
    else {
      on = true;
      digitalWrite(3, HIGH);
    }
  }
  TinyWireS_stop_check();
}

