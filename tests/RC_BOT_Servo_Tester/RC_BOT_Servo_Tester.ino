#include <Servo.h>

#define ch4 4

Servo serv1;

//Left Stick Right/Left
int ch4Val;
int ch4Map;

void setup() {
  // Start serial monitor
  Serial.begin(115200);
  serv1.attach(7);
  serv1.write(90);
  pinMode(ch1,INPUT);
}

void loop() {
  ch4Val = pulseIn(ch1, HIGH);
  ch4Map = map(ch4Val,990,1990,0,180);
  if (ch4Map < 85 || ch4Map > 95) {
    serv1.write(ch4Map);
  }
  else {
    serv1.write(90);
  }
  Serial.println("Ch4: ");Serial.println(ch4Map);
  Serial.print("\n");
}
