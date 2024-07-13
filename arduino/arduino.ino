#include <Servo.h>

const int ECHO_PIN = 9;
const int TRIG_PIN = 10;

const int BUZZER_PIN = 6;

const int SERVO_1_PIN = 3;
const int SERVO_2_PIN = 5;
const int SERVO_ACTIVE_ANGLE = 90;

const int LOOP_DELAY = 100;
const int CLOSE_DELAY = 1500;

int distance;
long duration;
const int MIN_DISTANCE = 40;

Servo servo1;
Servo servo2;

bool beeped = false;
void beep()
{
  if (!beeped)
  {
    beeped = true;
    digitalWrite(BUZZER_PIN, HIGH); // Turn on the buzzer
    delay(50);
    digitalWrite(BUZZER_PIN, LOW); // Turn off the buzzer
  }
}

void servoWrite(int value)
{
  servo1.write(value);
  servo2.write(value);
}

void setup()
{
  servo1.attach(SERVO_1_PIN);
  servo2.attach(SERVO_2_PIN);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  servoWrite(0);
  Serial.begin(9600);
}

void loop()
{
  // Clear the TRIG_PIN by setting it LOW
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  // Trigger the ultrasonic pulse
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Read the ECHO_PIN
  duration = pulseIn(ECHO_PIN, HIGH);

  // Calculate the distance in cm
  // 0.034: This is a conversion factor to convert the time (duration) into distance. Specifically, the speed of sound in air is approximately 343 meters per second, or 0.034 centimeters per microsecond.
  // 2: Since the duration measures the time for the sound wave to travel to the object and back, we divide by 2 to get the one-way distance from the sensor to the object.
  distance = duration * 0.034 / 2;

  // Beep and open the lid
  if (distance <= MIN_DISTANCE)
  {
    beep();
    servoWrite(SERVO_ACTIVE_ANGLE);
    delay(CLOSE_DELAY);
  }
  else
  {
    beeped = false;
    servoWrite(0);
  }

  // Continue the loop after delay
  delay(LOOP_DELAY);
}
