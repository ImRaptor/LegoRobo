/* 
 LegoRob
*/

#include <Servo.h>

Servo leftFootServ;
int leftFoot = 11;
int LFPos = 93;
Servo leftLegServ;
int leftLeg = 13;
int LLPos = 87;
Servo rightFootServ;
int rightFoot = 4;
int RFPos = 95;
Servo rightLegServ;
int RLPos = 90;
int rightLeg = 2;

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void movePart(Servo tarServ, int* pos, int amount);

void setup()
{
  leftFootServ.attach(leftFoot);
  leftLegServ.attach(leftLeg);
  rightFootServ.attach(rightFoot);
  rightLegServ.attach(rightLeg);

  leftLegServ.write(LLPos);
  rightFootServ.write(RFPos);
  rightLegServ.write(RLPos);
  leftFootServ.write(LFPos); 


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
          movePart(rightFootServ, &RFPos, 30);
        }
        else if (inputString[2] == 'd'){
          movePart(rightFootServ, &RFPos, -30);      
        }
      }
      else if (inputString[1] == 'l'){
        if (inputString[2] == 'u'){
          movePart(rightLegServ, &RLPos, 10);
        }
        else if (inputString[2] == 'd'){
          movePart(rightLegServ, &RLPos, -10);
        }
      }
    }
    else if (inputString[0] == 'l'){
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

void movePart(Servo tarServ, int* pos, int amount){
  //Serial.print("Here");
  int direct = 1;
  int adus = 0;
  if (amount < 0) {
    direct = -1;
  }
  for (int i = 0; i < abs(amount); i++){
    //Serial.print("\nRun:\n");
    adus = int(*pos)+(direct * i);
    //Serial.print("*pos: ");Serial.print(int(*pos));
    tarServ.write(adus);
    //Serial.print(adus);
    //Serial.write('\n');
    delay(20);
  }
  *pos = adus;
  //Serial.print("Done\n");
}
