#include <Servo.h>

const int ECHO_PIN = 9;
const int TRIG_PIN = 10;

const int BUZZER_PIN = 6;

const int SERVO_1_PIN = 3;
const int SERVO_2_PIN = 5;
const int SERVO_ACTIVE_ANGLE = 90; // degree

const int LOOP_DELAY = 100;   // ms
const int CLOSE_DELAY = 1500; // ms

int distance;
long duration;
const int MIN_DISTANCE = 40; // cm

Servo servo1;
Servo servo2;

bool beeped = false;
void beep()
{
  // beep once while opening lid
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
  // Attach the servo motors
  servo1.attach(SERVO_1_PIN);
  servo2.attach(SERVO_2_PIN);

  // Reset the servo to initial position
  servoWrite(0);

  // Attach ultrasonic and buzzer
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);

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
  // Close the lid
  else
  {
    beeped = false;
    servoWrite(0);
  }

  // Continue the loop after delay
  delay(LOOP_DELAY);
}
