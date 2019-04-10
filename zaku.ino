#include <Servo.h>
#define PIN_SERVO 6
#define MIN_ANGLE 20
#define MAX_ANGLE 150
#define MIN_HIGHLIGHT 10
#define MAX_HIGHLIGHT 250
#define PIN_LED_RED 9
#define PIN_LED_GREEN 10
#define PIN_LED_BLUE 11
#define PIN_BUTTON 5

Servo servo_eye;
int target_angle = 90;
int target_highlight = MIN_HIGHLIGHT;
int dirction_angle = 2;
int dirction_highlight = 1;
int mode = 1;

void setup() {
  Serial.begin(9600);
  pinMode(PIN_LED_RED, OUTPUT);
  pinMode(PIN_LED_GREEN, OUTPUT);
  pinMode(PIN_LED_BLUE, OUTPUT);
  pinMode(PIN_BUTTON, INPUT);
  servo_eye.attach(PIN_SERVO);

}

void loop() {
  if (digitalRead(PIN_BUTTON) == HIGH) {
    changeMode();
    Serial.println("change mode:");
    Serial.println(mode);
  }
  switch (mode) {
    case 1:
      rotate();
      highlight(PIN_LED_BLUE);
      break;
    case 2:
      resetServo();
      breathing(PIN_LED_BLUE);
      break;
    default:
      break;
  }
  delay(100);
}

void rotate() {
  target_angle += dirction_angle;
  if (target_angle > MAX_ANGLE || target_angle < MIN_ANGLE) {
    dirction_angle = -dirction_angle;
  }
  target_angle = min(MAX_ANGLE, max(MIN_ANGLE, target_angle));
  servo_eye.write(target_angle);

}

void breathing(int pin) {
  target_highlight += dirction_highlight;
  if (target_highlight > MAX_HIGHLIGHT || target_highlight < MIN_HIGHLIGHT) {
    dirction_highlight = -dirction_highlight;
  }
  Serial.println(target_highlight);
  target_highlight = min(MAX_HIGHLIGHT, max(MIN_HIGHLIGHT, target_highlight));
  analogWrite(pin, target_highlight);
}

void resetServo() {
  target_angle = 90;
  servo_eye.write(target_angle);
}

void highlight(int pin) {
  analogWrite(pin, MAX_HIGHLIGHT);
}

void changeMode() {
  mode = (mode + 1) % 3;
}
