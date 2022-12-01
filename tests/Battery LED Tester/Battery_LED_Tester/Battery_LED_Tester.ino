#define LED1 23
#define LED2 25
#define LED3 27
#define LED4 29
#define LED5 31
#define LED6 33


//Switch C | Channel 5
#define ch5 5
int ch5Val;




void setup() {
  Serial.begin(9600);
  pinMode(ch1,INPUT);
  ledSetup();
}

void loop() {
  ch5Val = pulseIn(ch1, HIGH);
  Serial.println(ch5Val);
  if (ch5Val < 1200) {
    ledLow();
  }
  else if (ch5Val > 1200 && ch5Val < 1700) {
    ledMid();
  }
  else {
    ledHigh();
  }
}

void ledLow() {
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  digitalWrite(LED5, LOW);
  digitalWrite(LED6, LOW);
  
}

void ledMid() {
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, HIGH);
  digitalWrite(LED4, HIGH);  
  digitalWrite(LED5, LOW);
  digitalWrite(LED6, LOW);
}

void ledHigh() {
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, HIGH);
  digitalWrite(LED4, HIGH);
  digitalWrite(LED5, HIGH);
  digitalWrite(LED6, HIGH);
}


void ledSetup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  pinMode(LED6, OUTPUT);
}
