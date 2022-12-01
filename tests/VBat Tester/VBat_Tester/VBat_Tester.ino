#define cellPin A0
const float refVolts = 4.9;
int cellVal;
float volts;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  cellVal = analogRead(cellPin);
  volts = ((cellVal / 1023.0) * refVolts);
  Serial.println(volts);
}
