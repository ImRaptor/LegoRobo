/* 
 LegoRobo
*/

#include <Servo.h>

Servo leftFoot, leftLeg, rightFoot, rightLeg;

int leftFootPin = 11;
int LFPos = 94;
int leftLegPin = 9;
int LLPos = 87;
int rightFootPin = 4;
int RFPos = 99;
int RLPos = 85;
int rightLegPin = 2;


String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void movePart(Servo tarServ, int* pos, int amount);

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
      for (int i = 0; i < 6; i++){
        rightStep();
      }
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
  for (int i = 0; i < abs(amount); i++){
    tarServ.write(hold+(i*direct));
    delay(20);
  }
  Serial.print(tarServ.read());
  Serial.print('\n');
  //Serial.print("Done\n");
}

void rightStep(){
  movePart(rightFoot,10);      // RF +10 RL +00 LF +00 LL +00
  movePart(leftFoot,10);       // RF +10 RL +00 LF +10 LL +00
  movePart(rightFoot, 20);     // RF +30 RL +00 LF +10 LL +00
  movePart(leftFoot,-10);      // RF +30 RL +00 LF +00 LL +00
  movePart(rightLeg, -15);     // RF +30 RL -15 LF +00 LL +00
  movePart(rightFoot, -30);    // RF +00 RL -15 LF +00 LL +00
  movePart(leftFoot, -10);     // RF +00 RL -15 LF -10 LL +00
  movePart(rightFoot, -10);    
  movePart(leftFoot, -20);
  movePart(rightFoot, 10);
  movePart(rightLeg, 15);
  movePart(leftLeg, 15);
  movePart(leftFoot, 30);
}
