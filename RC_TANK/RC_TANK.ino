
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
int ch5Val;
#define ch6 6
int ch6Val;

int right[3] = {38,40,42};
int left[3] = {32,34,36};
int backLeft = 30;
int backRight = 28;

// pinMode(left[0], OUTPUT);
// pinMode(left[1], OUTPUT);
// pinMode(left[2], OUTPUT);
// pinMode(right[0], OUTPUT);
// pinMode(right[1], OUTPUT);
// pinMode(right[2], OUTPUT);
// pinMode(backLeft, OUTPUT);
// pinMode(backRight, OUTPUT);


void setup() {
  Serial.begin(115200);
  pinMode(ch1,INPUT);
  pinMode(ch2,INPUT);
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
  Serial.print("Volts: ");Serial.println(volts); 
  if(ch5Val > 1700) {
    runMaps();
    Serial.print("Ch2:");Serial.print(ch2MapSmooth);
    Serial.print("Ch2 Inv:");Serial.println(ch2MapInvSmooth);
    Serial.print("Ch1:");Serial.print(ch1Val);
    Serial.print("Ch5:");Serial.print(ch5Val);
    Serial.print("Ch6:");Serial.println(ch6Val);
  }
  else{
    //lights blink
  }
  // Serial.print("Ch2:");Serial.print(ch2MapSmooth);
  // Serial.print("Ch2 Inv:");Serial.print(ch2MapInvSmooth);
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
  ch5Val = pulseIn(ch5, HIGH);
  ch5Val = constrain(ch5Val,1040,1940);
  ch6Val = pulseIn(ch6, HIGH);
  ch6Val = constrain(ch6Val,1040,1940);
}

void getVoltage() {
  cellVal = analogRead(cellPin);
  volts = ((cellVal / 1023.0) * refVolts); 
}

void leftOn() {
  digitalWrite(left[0], HIGH);
  digitalWrite(left[1], HIGH);
  digitalWrite(left[2], HIGH);
};
void leftOff() {
  digitalWrite(left[0], LOW);
  digitalWrite(left[1], LOW);
  digitalWrite(left[2], LOW);
};
void rightOn() {
  digitalWrite(right[0], HIGH);
  digitalWrite(right[1], HIGH);
  digitalWrite(right[2], HIGH);
};
void rightOff() {
  digitalWrite(right[0], LOW);
  digitalWrite(right[1], LOW);
  digitalWrite(right[2], LOW);
};
void backLeftOn() {
  digitalWrite(backLeft, HIGH);
};
void backLeftOff() {
  digitalWrite(backLeft, LOW);
};
void backRightOn() {
  digitalWrite(backRight, HIGH);
};
void backRightOff() {
  digitalWrite(backRight, LOW);
};
void lightsOn() {
  digitalWrite(left[0], HIGH);
  digitalWrite(left[1], HIGH);
  digitalWrite(left[2], HIGH);
  digitalWrite(right[0], HIGH);
  digitalWrite(right[1], HIGH);
  digitalWrite(right[2], HIGH);
  digitalWrite(backLeft, HIGH);
  digitalWrite(backRight, HIGH);
};
void lightsOff() {
  digitalWrite(left[0], LOW);
  digitalWrite(left[1], LOW);
  digitalWrite(left[2], LOW);
  digitalWrite(right[0], LOW);
  digitalWrite(right[1], LOW);
  digitalWrite(right[2], LOW);
  digitalWrite(backLeft, LOW);
  digitalWrite(backRight, LOW);
};







