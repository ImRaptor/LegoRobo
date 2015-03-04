/* 
 LegoRobo
*/

#include <Servo.h>
#define leftFootPin 11
#define LFPos  94
#define leftLegPin  9
#define LLPos 85
#define rightFootPin 4
#define RFPos 99
#define RLPos 82
#define rightLegPin 2

Servo leftFoot, leftLeg, rightFoot, rightLeg;
String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void movePart(Servo tarServ, int amount);

void setup()
{
  // Connect servos to pins
  leftFoot.attach(leftFootPin);
  leftLeg.attach(leftLegPin);
  rightFoot.attach(rightFootPin);
  rightLeg.attach(rightLegPin);

  // Set servo position
  leftLeg.write(LLPos);
  rightFoot.write(RFPos);
  rightLeg.write(RLPos);
  leftFoot.write(LFPos); 


  Serial.begin(9600);
  inputString.reserve(200);
}

void loop() 
{
  if (stringComplete) {
    // Which leg?
    if (inputString[0] == 'r'){
      // Which segment
      if (inputString[1] == 'f'){
        // Up or Down
        if (inputString[2] == 'u'){
          movePart(rightFoot, 30);
        }
        else if (inputString[2] == 'd'){
          movePart(rightFoot, -30);      
        }
      }
      else if (inputString[1] == 'l'){
        if (inputString[2] == 'u'){
          movePart(rightLeg, 10);
        }
        else if (inputString[2] == 'd'){
          movePart(rightLeg, -10);
        }
      }
    }
    else if (inputString[0] == 'l'){
      if (inputString[1] == 'f'){
        if (inputString[2] == 'u'){
          movePart(leftFoot, -30);
        }
        else if (inputString[2] == 'd'){
          movePart(leftFoot, 30);
        }
      }
      else if(inputString[1] == 'l'){
        if (inputString[2] == 'u'){
          movePart(leftLeg, -10);
        }
        else if (inputString[2] == 'd'){
          movePart(leftLeg, 10);
        }
      }
    }
    else if (inputString[0] == 'm'){
      for (byte i = 0; i < 5; i++){
        forwardStep();
        //leftStep();
      }
      movePart(leftLeg, -15);
      //Serial.print("LL:");
      //Serial.print(leftLeg.read());
      //Serial.print('\n');
    }
    
    stringComplete = false; 
    inputString = "";
  }
}

void serialEvent() {
   while (Serial.available()) {
     char inChar = (char)Serial.read();
     inputString += inChar;
     if (inChar == '\n'){
       stringComplete = true;
     }
   }
}

void movePart(Servo tarServ, int amount){
  int direct = 1;
  if (amount < 0){
    direct = -1;
  }
  int hold = tarServ.read();
  for (int i = 0; i <= abs(amount); i++){
    tarServ.write(hold+(byte(i)*direct));
    //Serial.print(i);
    //Serial.print(':');
    //Serial.print(amount);
    //Serial.print('\n');
    delay(20);
  }
  //Serial.print(tarServ.read());
  //Serial.print('\n');
  //Serial.print("Done\n");
}

void forwardStep(){
  movePart(rightFoot, 10);     // RF +10 RL +00 LF +00 LL +00
  movePart(leftFoot, 10);      // RF +10 RL +00 LF +10 LL +00
  movePart(rightFoot, 20);     // RF +30 RL +00 LF +10 LL +00
  movePart(leftFoot, -10);     // RF +30 RL +00 LF +00 LL +00
  movePart(rightLeg, -15);     // RF +30 RL -15 LF +00 LL +00
  if (leftLeg.read() != LLPos){
    movePart(leftLeg, -15);
  }
  movePart(rightFoot, -30);    // RF +00 RL -15 LF +00 LL +00
  movePart(leftFoot, -10);     // RF +00 RL -15 LF -10 LL +00
  movePart(rightFoot, -10);    // RF -10 RL -15 LF -10 LL +00
  movePart(leftFoot, -20);     // RF -10 RL -15 LF -30 LL +00
  movePart(rightFoot, 10);     // RF +00 RL -15 LF -30 LL +00
  movePart(rightLeg, 15);      // RF +00 RL +00 LF -30 LL +00
  movePart(leftLeg, 15);       // RF +00 RL +00 LF -30 LL +15
  movePart(leftFoot, 30);      // RF +00 RL +00 LF +00 LL +15
  //movePart(leftLeg, -15);      // RF +00 RL +00 LF +00 LL +00
}

/**
* Unused
void leftStep(){
  movePart(leftFoot, -10);      
  movePart(rightFoot, -10);     
  movePart(leftFoot, -20);      
  movePart(rightFoot, 10);    
  movePart(leftLeg, 15);      
  movePart(leftFoot, 30);     
  movePart(rightFoot, 10);    
  movePart(leftFoot, 10);     
  movePart(rightFoot, 20);    
  movePart(leftFoot, -10);     
  movePart(leftLeg, -15);      
  movePart(rightLeg, -15);     
  movePart(rightFoot, -30);    
  movePart(rightLeg, 15);    
}**/
