#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#endif

#include "../include/diagnostic.h"
#include "../include/defines.h"
#include <stdint.h>
#include <Servo.h>

void servo_check(Servo& servo)
{
    Serial.println("0");
    servo.write(0);
    delay(1000);
    servo.detach(); // Stop. You can use deatch function or use write(x), as x is the middle of 0-180 which is 90, but some lack of precision may change this value
    delay(1000);
    servo.attach(SERVO_PIN); // Always use attach function after detach to re-connect your servo with the board
    Serial.println("28"); // Turn left high speed
    servo.write(28);
    delay(1000);
    servo.detach(); // Stop
    delay(1000);
    servo.attach(SERVO_PIN);
    Serial.println("0");
    servo.write(0);
    delay(1000);
    servo.detach();
    delay(1000);
    servo.attach(SERVO_PIN);
}