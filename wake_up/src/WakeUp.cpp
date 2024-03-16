// path: src/drivers.h
/**
 * @brief
 *
 */

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#endif

#include "../include/WakeUp.h"

#include <DS3231.h>
#include <Keypad.h>
#include <Servo.h>
#include <Wire.h>
#include <stdint.h>

/* pin layout servo sg90
VCC(Red) - 5V
SIG(orange) - D9
GND(Brown) - GND
*/

// Servo motor
Servo servo;

// Init the DS3231
DS3231 rtc;

static Dates now;
static Alarm alarm;

volatile int tick = 0;

/**
 * @brief The interrupt service routine for the alarm
 *
 */
void isr_wakeUp()
{
    tick = 1;
}

int main()
{

    Serial.begin(9600);
    Wire.begin();
    while (!Serial)
        ;
    Serial.println("BOOTED");

    // Set the servo
    //--------------------------------
    servo.attach(SERVO_PIN);

    if (Serial) {
        if (servo.attached()) {
            Serial.println("Servo attached, running dioagnostic");
            servo_check(servo);
        } else {
            Serial.println("Servo not attached");
        }
    }
    servo.detach();

    rtc.setClockMode(false);

    if (Serial) {
        serial_get_date(now.year, now.month, now.date, now.dOW, now.hour, now.minute, now.second);
        rtc_set_date(rtc, now);
    }

    // Set the alarm
    //--------------------------------
    alarm.set_alarm(1, 7, 30, 0, 0b00001000, true, false, false);

    rtc.turnOffAlarm(1);
    rtc.turnOffAlarm(2);
    rtc.setA1Time(alarm.alarmDay, alarm.alarmHour, alarm.alarmMinute, alarm.alarmSecond,
        alarm.alarmBits, alarm.alarmIsDay, alarm.alarmH12, alarm.alarmPM);
    rtc.turnOnAlarm(1);

    uint8_t A1Day;
    uint8_t A1Hour;
    uint8_t A1Minute;
    uint8_t A1Second;
    uint8_t AlarmBits;
    bool A1Dy;
    bool A1h12;
    bool A1PM;

    if (rtc.checkIfAlarm(1)) {
        Serial.println("Alarm 1 set"); // the following code is kinda messy but was only put in for debug purposes
        rtc.getA1Time(A1Day, A1Hour, A1Minute, A1Second, AlarmBits, A1Dy, A1h12, A1PM);
        rtc_alarm_print_time(A1Day, A1Hour, A1Minute, A1Second, AlarmBits, A1Dy, A1h12, A1PM);
    } else {
        Serial.println("Alarm 1 not set");
        rtc.getA1Time(A1Day, A1Hour, A1Minute, A1Second, AlarmBits, A1Dy, A1h12, A1PM);
        rtc_alarm_print_time(A1Day, A1Hour, A1Minute, A1Second, AlarmBits, A1Dy, A1h12, A1PM);
    }

    // Set the interrupt
    //--------------------------------
    pinMode(CLINT, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(CLINT), isr_wakeUp, FALLING);

    // Use builtin LED to blink
    pinMode(LED_BUILTIN, OUTPUT);

    while (1) {
        loop();
    }
}

void loop()
{
    servo.attach(SERVO_PIN);
    // DateTime currentMoment = RTClib::now();
    // display the current date and time (debug)
    // Serial.print(currentMoment.year(), DEC);
    // Serial.print('/');
    // Serial.print(currentMoment.month(), DEC);
    // Serial.print('/');
    // Serial.print(currentMoment.day(), DEC);
    // Serial.print(" ");
    // Serial.print(currentMoment.hour(), DEC);
    // Serial.print(':');
    // Serial.print(currentMoment.minute(), DEC);
    // Serial.print(':');
    // Serial.print(currentMoment.second(), DEC);
    // Serial.println();

    // Serial.print(currentMoment.unixtime());

    // Serial.print("T="); // apparenty, this can do temperature
    // Serial.println(rtc.getTemperature(), 2);

    if (tick) {
        Serial.println("WAKE UP");
        digitalWrite(LED_BUILTIN, HIGH);

        Serial.println("28"); // Turn left high speed
        servo.write(28);
        delay(100);
        servo.detach(); // Stop
        delay(100);
        servo.attach(SERVO_PIN);
        Serial.println("0");
        servo.write(0);
        delay(1000);
        servo.detach();
        delay(1000);
        servo.attach(SERVO_PIN);

        digitalWrite(LED_BUILTIN, LOW);
        tick = 0;

        // re-attach servo
        // clear flag
        rtc.checkIfAlarm(1);
    }

    delay(1000);
}