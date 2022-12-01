
  /* RC TANK By Austin Foster
        10.6.22 
*/
#include <Servo.h>
Servo serv1;
Servo serv2;
Servo serv3;
Servo serv4;

//Battery Voltage Variables
#define cellPin A0
const float refVolts = 4.75;
int cellVal;
float volts;

//CH2 R Front/Back  
#define ch2 12
int ch2Val;
int ch2Map;
int ch2MapInv;
//smoothing
int ch2MapSmooth;
int ch2MapPrev;
int ch2MapInvSmooth;
int ch2MapInvPrev;


//CH4 L Turn
#define ch4 13
int ch4Val;
int ch4Map;
int ch4MapTurn;
//smoothing
int ch4Smooth;
int ch4Prev;
int ch4TurnSmooth;
int ch4TurnPrev;

//CH1 
#define ch1 11
int ch1Val;
int ch1Map;
int ch1MapSmooth;
int ch1MapPrev;


void setup() {
  Serial.begin(115200);
  pinMode(ch4,INPUT);
  pinMode(ch2,INPUT);
  pinMode(ch1,INPUT);
  serv1.detach();
  serv2.detach();
  serv3.detach();
  serv4.detach();
}

void loop() {
  getPulses();
  getVoltage();
  runMaps();
}

void runMaps() {
  //Forward
  ch2Map = map(ch2Val,1040,1940,110,70);
  ch2MapInv = map(ch2Val,1040,1940,70,110);

  ch2MapSmooth = (ch2Map * 0.25) + (ch2MapPrev * 0.75);
  ch2MapPrev = ch2MapSmooth;
  
  ch2MapInvSmooth = (ch2MapInv * 0.25) + (ch2MapInvPrev * 0.75);
  ch2MapInvPrev = ch2MapInvSmooth;
  
  //ADDITIVE TURNING
  ch1Map = map(ch1Val,1940,1040,-50,50);

  ch1MapSmooth = (ch1Map * 0.3) + (ch1MapPrev * 0.7);
  ch1MapPrev = ch1MapSmooth;

  ch2MapSmooth = ch2MapSmooth - ch1MapSmooth;
  ch2MapInvSmooth = ch2MapInvSmooth - ch1MapSmooth;

  ch2MapSmooth = constrain(ch2MapSmooth,70,110);
  ch2MapInvSmooth = constrain(ch2MapInvSmooth,70,110);

  Serial.print("Ch2:");Serial.print(ch2MapSmooth);
  Serial.print("   Ch2 INV:");Serial.print(ch2MapInvSmooth);
  Serial.print("   Ch1:");Serial.print(ch1Map);

  if (ch2MapSmooth < 87 || ch2MapSmooth > 93 || ch1Map < -5 || ch1Map > 5) {
    serv1.attach(7);
    serv2.attach(8);
    serv3.attach(9);
    serv4.attach(10);
    serv1.write(ch2MapSmooth);
    serv2.write(ch2MapSmooth);
    serv3.write(ch2MapInvSmooth);
    serv4.write(ch2MapInvSmooth);
  }
  else {
    serv1.detach();
    serv2.detach();
    serv3.detach();
    serv4.detach();
  }
}



void getPulses() {
  ch2Val = pulseIn(ch2, HIGH);
  ch2Val = constrain(ch2Val,1040,1940);
  ch4Val = pulseIn(ch4, HIGH);
  ch4Val = constrain(ch4Val,1040,1940);
  ch1Val = pulseIn(ch1, HIGH);
  ch1Val = constrain(ch1Val,1040,1940);
}

void getVoltage() {
  cellVal = analogRead(cellPin);
  volts = ((cellVal / 1023.0) * refVolts);
  Serial.print("   |   Volts: ");Serial.println(volts);  
}
