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

void dance();
void forwardStep();
void movePart(Servo tarServ, int amount, int direct=1, int spd=2);
void rightTilt();
void shakeLeg(Servo oneFoot, Servo twoFoot, Servo oneLeg, Servo twoLeg, int direct=1);

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
    if (inputString[0] == 'm'){
      for (byte i = 0; i < 5; i++){
        forwardStep();
        //leftStep();
      }
      movePart(leftLeg, -15);
      //Serial.print("LL:");
      //Serial.print(leftLeg.read());
      //Serial.print('\n');
    }
    else if (inputString[0] == 'd'){
      dance();
    }
    else if (inputString[0] == 't'){
      for (int i = 0; i <10 ; i++){
        rightTilt();
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

void dance(){
 shakeLeg(rightFoot, leftFoot, rightLeg, leftLeg, 1);
 shakeLeg(leftFoot, rightFoot, leftLeg, rightLeg, -1);
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

void movePart(Servo tarServ, int amount,int direct, int spd){
  if (amount < 0){
    direct = -1*direct;
  }
  int hold = tarServ.read();
  for (int i = 0; i <= abs(amount); i=i+spd){
    tarServ.write(hold+(byte(i)*direct));
    //Serial.print(spd);
    //Serial.print(':');
    //Serial.print(amount);
    //Serial.print('\n');
    delay(20);
  }
  //Serial.print(tarServ.read());
  //Serial.print('\n');
  //Serial.print("Done\n");
}

void rightTilt(){
  int lpos = leftFoot.read();
  int rpos = rightFoot.read();
  for (int i = 0; i<= 5; ++i){
    //Serial.print(lpos);
    //Serial.print(' ');
    lpos -= byte(5);
    rpos += byte(5);
    rightFoot.write(rpos);
    leftFoot.write(lpos);
    delay(20);
  }
  for (int i = 5; i>= 0; --i){
    lpos += byte(5);
    rpos -= byte(5);
    rightFoot.write(rpos);
    leftFoot.write(lpos);
    delay(20);
  }
  //Serial.print('\n');
}

void shakeLeg(Servo oneFoot, Servo twoFoot, Servo oneLeg, Servo twoLeg, int direct){
  // Lift foot
  movePart(oneFoot, 9, direct, 3);
  movePart(twoFoot, 9, direct, 3);
  movePart(oneFoot, 21, direct, 3);
  movePart(twoFoot, -9, direct, 3);
  // Shake Leg
  movePart(twoLeg, 30, direct, 3);
  movePart(twoLeg, -60, direct, 3);
  movePart(twoLeg, 30, direct, 3);
  // Back to centre
  movePart(oneFoot, -30, direct, 3);
}
