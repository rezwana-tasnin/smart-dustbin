#include <Servo.h>

const int buzzerPin = 6;
const int trigPin = 10;
const int echoPin = 9;
const int servo1Pin = 3;
const int servo2Pin = 5;

long duration;
int distance;

bool isBeeped = false;

//
bool open = false;
int openTime = 0;
int minOpenTime = 1500;

Servo servo1;
Servo servo2;

void beep()
{
  if (!isBeeped)
  {
    isBeeped = true;
    digitalWrite(buzzerPin, HIGH); // Turn on the buzzer
    delay(50);
    digitalWrite(buzzerPin, LOW); // Turn off the buzzer
  }
}

void servoWrite(int value)
{
  servo1.write(value);
  servo2.write(value);
}

void setup()
{
  servo1.attach(servo1Pin);
  servo2.attach(servo2Pin);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);

  servoWrite(0);
  Serial.begin(9600);
}

void loop()
{
  // Clear the trigPin by setting it LOW
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Trigger the ultrasonic pulse
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the echoPin
  duration = pulseIn(echoPin, HIGH);

  // Calculate the distance
  distance = duration * 0.034 / 2;

  // Print the distance to the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);

  if (open)
  {
    openTime = openTime + 100;
  }

  if (!open && distance <= 40)
  {
    beep();
    open = true;
    servoWrite(90);
  }

  if (distance > 40 && openTime > minOpenTime)
  {
    open = false;
    openTime = 0;
    isBeeped = false;
    servoWrite(0);
  }

  delay(100);
}
