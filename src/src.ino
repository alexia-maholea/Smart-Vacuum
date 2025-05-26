#define Trig 12
#define Echo 13
#define SwitchPin A0  
#define FanPin 10      // MOSFET
#define VibrationPin A2
#define LedPin A1

const int in21 = 2;  // IN1
const int in22 = 3;  // IN2
const int in23 = 4;  // IN3
const int in24 = 5;  // IN4

int thresholdVib = 1;

unsigned long ledOnUntil = 0; // pentru timer LED

void setup() 
{  
  Serial.begin(9600);

  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
  pinMode(SwitchPin, INPUT_PULLUP);
  pinMode(FanPin, OUTPUT);
  pinMode(LedPin, OUTPUT);

  pinMode(in21, OUTPUT);
  pinMode(in22, OUTPUT);
  pinMode(in23, OUTPUT);
  pinMode(in24, OUTPUT);

  digitalWrite(FanPin, LOW);
  digitalWrite(LedPin, LOW);

  Serial.println("Asteapta start...");
} 

void loop() 
{
  if (digitalRead(SwitchPin) == LOW)  // robot ON
  {
    digitalWrite(FanPin, HIGH);

    int vibratie = analogRead(VibrationPin);
    Serial.print("Vibratie: ");
    Serial.println(vibratie);

    if (vibratie > thresholdVib) {
      ledOnUntil = millis() + 1500;
      Serial.println("LED aprins.");
    }

    if (millis() < ledOnUntil) {
      digitalWrite(LedPin, HIGH);
    } else {
      digitalWrite(LedPin, LOW);
    }

    // senzor ultrasonic
    digitalWrite(Trig, LOW);
    delayMicroseconds(2);
    digitalWrite(Trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(Trig, LOW);
    unsigned int impulseTime = pulseIn(Echo, HIGH);
    unsigned int distance_sm = impulseTime / 58;

    Serial.print("Distanta: ");
    Serial.print(distance_sm);
    Serial.println(" cm");

    if (distance_sm > 25) 
    {     
      Serial.println("Merg inainte");
      digitalWrite(in21, LOW);
      digitalWrite(in22, HIGH);
      digitalWrite(in23, HIGH);
      digitalWrite(in24, LOW);
    }  
    else 
    {   
      Serial.println("Obstacol! Intoarcere...");
      digitalWrite(in21, HIGH);
      digitalWrite(in22, LOW);
      digitalWrite(in23, HIGH);
      digitalWrite(in24, LOW);
      delay(1100); 
    }   
  }
  else
  {
    // robot OFF
    digitalWrite(FanPin, LOW);
    digitalWrite(LedPin, LOW);

    digitalWrite(in21, LOW);
    digitalWrite(in22, LOW);
    digitalWrite(in23, LOW);
    digitalWrite(in24, LOW);

    Serial.println("Switch OFF");
  }

  delay(100); 
}
