// path: src/drivers.h
/**
 * @brief
 *
 */

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#endif

#include "../include/Wake.h"
#include "../include/defines.h"
#include "../include/diagnostic.h"
#include "../include/keypad.h"
#include "../include/lcd.h"
#include "../include/alarm.h"

#include <DS3231.h>
#include <Servo.h>
#include <Wire.h>

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

void setup()
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
        get_date(now.year, now.month, now.date, now.dOW, now.hour, now.minute, now.second);
        rtc_set_date(rtc, );
    }

    // Set the alarm
    //--------------------------------
    rtc_set_alarm(alarm); // default values are what i want anyway

    rtc.turnOffAlarm(1);
    rtc.turnOffAlarm(2);
    rtc.setA1Time(alarm.alarmDay, alarm.alarmHour, alarm.alarmMinute, alarm.alarmSecond,
        alarm.alarmBits, alarm.alarmIsDay, alarm.alarmH12, alarm.alarmPM);
    rtc.turnOnAlarm(1);

    byte A1Day;
    byte A1Hour;
    byte A1Minute;
    byte A1Second;
    byte AlarmBits;
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