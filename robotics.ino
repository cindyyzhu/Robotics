#include <Servo.h>

Servo myServo;
int servoPin = 9;
int trigPin = 6;
int echoPin = 7;
int sweepDelay = 5;
int distanceThreshold = 10;
int angle = 0;
int direction = 10;

long getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  long distance = duration * 0.034 / 2;
  return distance;
}

void setup() {
  myServo.attach(servoPin);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  long distance = getDistance();
  Serial.println(distance);

  // Stop the servo if an object is within 10 cm
  if (distance <= distanceThreshold) {
    return;
  }

  // Move the servo
  angle += direction;

  // Reverse at 180°
  if (angle >= 180) {
    angle = 180;
    direction = -10;
  }

  // Reverse at 0°
  if (angle <= 0) {
    angle = 0;
    direction = 10;
  }

  myServo.write(angle);
  delay(sweepDelay);
}
