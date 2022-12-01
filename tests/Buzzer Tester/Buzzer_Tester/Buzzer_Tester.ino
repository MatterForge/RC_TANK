#define ch5 5
int ch5Val;

int buzzer = 12;

void setup() {
  Serial.begin(9600);
  pinMode(ch1,INPUT);
  pinMode(buzzer,OUTPUT);
}

void loop() {
  ch5Val = pulseIn(ch1, HIGH);
  Serial.println(ch5Val);
  if (ch5Val > 1200) {
    digitalWrite(buzzer,HIGH);
  }
  else {
    digitalWrite(buzzer,LOW);
  }
}
