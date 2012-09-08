import processing.serial.*;
Serial myPort;  

int counter =0;
void setup(){
  size(500,100);
  myPort = new Serial(this,  Serial.list()[0], 9600);  
}

void draw(){
  if ( myPort.available() > 0) {  // If data is available,
    int temp = myPort.read();
    if(temp <=250){
      print(temp);
      print(" ");      
    } else if(temp == 252){
      println("");
    }    
  }    
     
  if (counter == width/10){
    background(255);
    counter = 0;
  }
}
