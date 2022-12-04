
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
#define ch2 8
int ch2Val;
int ch2Map;
int ch2MapInv;
//smoothing
int ch2MapSmooth;
int ch2MapPrev;
int ch2MapInvSmooth;
int ch2MapInvPrev;
//CH1 
#define ch1 9
int ch1Val;
int ch1Map;
int ch1MapSmooth;
int ch1MapPrev;
#define ch5 7
#define ch6 6

void setup() {
  Serial.begin(115200);
  pinMode(ch2,INPUT);
  pinMode(ch1,INPUT);
  pinMode(ch5,INPUT);
  pinMode(ch6,INPUT);
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
  ch2Map = map(ch2Val,985,1995,110,70);
  ch2MapInv = map(ch2Val,985,1995,70,110);

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
  Serial.print("Ch2:");Serial.print(ch2MapInvSmooth);

  if (ch2MapSmooth < 87 || ch2MapSmooth > 90 || ch1Map < -5 || ch1Map > 5) {
    serv1.attach(10);
    serv2.attach(11);
    serv3.attach(12);
    serv4.attach(13);
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
  ch2Val = constrain(ch2Val,985,1995);
  ch1Val = pulseIn(ch1, HIGH);
  ch1Val = constrain(ch1Val,1040,1940);
}

void getVoltage() {
  cellVal = analogRead(cellPin);
  volts = ((cellVal / 1023.0) * refVolts);
  Serial.print("   |   Volts: ");Serial.println(volts);  
}
