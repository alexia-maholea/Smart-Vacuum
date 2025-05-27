#define Trig 12
#define Echo 13
#define SwitchPin A0  
#define FanPin 10         // MOSFET
#define VibrationPin A2
#define LedPin A1

const int in1 = 2;         // IN1 – dir motor A
const int in2 = 3;         // IN2 – dir motor A
const int in3 = 4;         // IN3 – dir motor B
const int in4 = 7;         // IN4 – dir motor B
const int enA = 5;         // ENA – viteza motor A (PWM)
const int enB = 6;         // ENB – viteza motor B (PWM)

int thresholdVib = 1;
unsigned long ledOnUntil = 0;  // pentru led

void setup() 
{
    Serial.begin(9600);
   pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
  pinMode(SwitchPin, INPUT_PULLUP);
  pinMode(FanPin, OUTPUT);
  pinMode(LedPin, OUTPUT);
  
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  
  digitalWrite(FanPin, LOW);
  digitalWrite(LedPin, LOW);
  
  Serial.println("Wait for start...");
}

void loop() 
{
  if (digitalRead(SwitchPin) == LOW)  // robot ON
  {
    digitalWrite(FanPin, HIGH);
    
    // Detectare vibrații
    int vibration = analogRead(VibrationPin);
    Serial.print("Vibration felt: ");
    Serial.println(vibration);
    
    if (vibratie > thresholdVib) {
      ledOnUntil = millis() + 1500;
      Serial.println("LED aprins.");
    }
    
    if (millis() < ledOnUntil) {
      digitalWrite(LedPin, HIGH);
    } else {
      digitalWrite(LedPin, LOW);
    }
    
    // masurare distanta
    digitalWrite(Trig, LOW);
    delayMicroseconds(2);
    digitalWrite(Trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(Trig, LOW);
    unsigned int impulseTime = pulseIn(Echo, HIGH);
    unsigned int distance_cm = impulseTime / 58;
    
    Serial.print("Distance: ");
    Serial.print(distance_cm);
    Serial.println(" cm");
    
    if (distance_cm > 20) 
    {
          Serial.println("Go forward!");
      digitalWrite(in1, HIGH);  // motor A
      digitalWrite(in2, LOW);   // motor A
      digitalWrite(in3, HIGH);  // motor B
      digitalWrite(in4, LOW);   // motor B
      analogWrite(enA, 10);  // viteza motor A
      analogWrite(enB, 10);  // viteza motor B
    }
      else 
    {
         Serial.println("Something is blocking the way! Turning back...");
      digitalWrite(in1, HIGH);  // motor A forwards
      digitalWrite(in2, LOW);   // motor A forwards  
      digitalWrite(in3, LOW);   // motor B backwards
      digitalWrite(in4, HIGH);  // motor B backwards
      analogWrite(enA, 150);    //  rotation speed
      analogWrite(enB, 150);    //  rotation speed
      delay(1100);
     }
     
    }
  else
  {
    // robot OFF
    digitalWrite(FanPin, LOW);
    digitalWrite(LedPin, LOW);
    
    analogWrite(enA, 0);
    analogWrite(enB, 0);
    
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    
    Serial.println("Switch OFF");
  }
  
  delay(100);
}