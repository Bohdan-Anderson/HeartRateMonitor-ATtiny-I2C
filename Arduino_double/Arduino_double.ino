// Wire Master Reader
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Reads data from an I2C/TWI slave device
// Refer to the "Wire Slave Sender" example for use with this

// Created 29 March 2006

// This example code is in the public domain.

//SDA = analog 4,   SCL = analog 5

#include <Wire.h>

void setup()
{
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
  Serial.println("on");
}

void loop(){
 writeI2c(4);
 //writeI2c(5);
 

  delay(400);
}

void writeI2c(int board){
  Wire.requestFrom(board, 2);    // request 16 bytes from slave device #38
  
  Serial.print("From attiny ");
  Serial.print(board);
  Serial.print(" ");  
  while (Wire.available())
  { 
    int c = Wire.read(); // receive a byte as character
    Serial.print(c);         // print the character
    Serial.print(",");
  }
//  Serial.write(252); 
  Serial.println(" end");    
}
