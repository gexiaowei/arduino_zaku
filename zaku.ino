#include <Servo.h>
#define PIN_SERVO 6
#define MIN_ANGLE 20
#define MAX_ANGLE 150
#define MIN_HIGHLIGHT 10
#define MAX_HIGHLIGHT 250
#define PIN_LED_RED 9
#define PIN_LED_GREEN 10
#define PIN_LED_BLUE 11

Servo servo_eye;
int target_angle = MIN_ANGLE;
int target_highlight = MIN_HIGHLIGHT;
int dirction = 2;

void setup() {
  // put your setup code here, to run once:
  pinMode(PIN_LED_BLUE, OUTPUT);
  servo_eye.attach(PIN_SERVO);

}

void loop() {
  // put your main code here, to run repeatedly:
  target_angle += dirction;
  target_highlight += (dirction * 4);
  if (target_angle > MAX_ANGLE || target_angle < MIN_ANGLE) {
    dirction = -dirction;
  }
  target_angle = min(MAX_ANGLE, max(MIN_ANGLE, target_angle));
  target_highlight = min(MAX_HIGHLIGHT, max(MIN_HIGHLIGHT, target_highlight));
  analogWrite(PIN_LED_BLUE, target_highlight);
  servo_eye.write(target_angle);
  delay(100);
}
