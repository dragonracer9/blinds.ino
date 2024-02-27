/**
 * @file wake_up.ino
 * @author Vikram Damani (vdamani@ethz.ch)
 * @brief A simple script to raise my blinds in the morning so I can wake up to the sun
 *
 * This script is designed to be run on an Arduino Uno with a DS3231 RTC module and a servo motor.
 *
 * @version 0.1
 * @date 2024-02-06
 *
 * @copyright Copyright (c) 2024
 *
 */

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
#define SERVO_PIN 6

// Init the DS3231
DS3231 rtc;
// interrupt pin (on the arduino uno, interrupt pins are digital pins 2 and 3)
#define CLINT 52

// Define the data structures
struct Dates {
    byte year;
    byte month;
    byte date;
    byte dOW;
    byte hour;
    byte minute;
    byte second;
};

struct Alarm {
    byte alarmDay;
    byte alarmHour;
    byte alarmMinute;
    byte alarmSecond;
    byte alarmBits;
    bool alarmIsDay;
    bool alarmH12;
    bool alarmPM;
};

static Dates now;
static Alarm alarm;

volatile int tick = 0;

void get_date(byte& year, byte& month, byte& date, byte& dOW,
    byte& hour, byte& minute, byte& second)
{

    Serial.println("Please enter an x-terminated string of the form YYMMDDwHHMMSS");
    boolean gotString = false;
    char inChar;
    char data[20];

    byte j = 0;
    while (!gotString) {
        if (Serial.available()) {
            inChar = Serial.read();
            data[j] = inChar;
            j += 1;
            if (inChar == 'x') {
                gotString = true;
            }
        }
    }
    Serial.print("date entered: ");
    Serial.println(data);

    year = (byte)(data[0] - '0') * 10 + (byte)(data[1] - '0');
    month = (byte)(data[2] - '0') * 10 + (byte)(data[3] - '0');
    date = (byte)(data[4] - '0') * 10 + (byte)(data[5] - '0');
    dOW = (byte)(data[6] - '0'); // 0 is Sunday
    hour = (byte)(data[7] - '0') * 10 + (byte)(data[8] - '0');
    minute = (byte)(data[9] - '0') * 10 + (byte)(data[10] - '0');
    second = (byte)(data[11] - '0') * 10 + (byte)(data[12] - '0');
}

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
        } else {
            Serial.println("Servo not attached");
        }
    }
    servo.detach();

    rtc.setClockMode(false);

    if (Serial) {
        get_date(now.year, now.month, now.date, now.dOW, now.hour, now.minute, now.second);

        rtc.setYear(now.year);
        rtc.setMonth(now.month);
        rtc.setDate(now.date);
        rtc.setDoW(now.dOW);
        rtc.setHour(now.hour);
        rtc.setMinute(now.minute);
        rtc.setSecond(now.second);
    }

    // Set the alarm
    //--------------------------------
    alarm.alarmIsDay = true;
    alarm.alarmH12 = false; // use 24-hour time mode
    alarm.alarmPM = false;

    alarm.alarmDay = 5; // 1 is Sunday
    alarm.alarmHour = 7;
    alarm.alarmMinute = 45;
    alarm.alarmSecond = 0;
    alarm.alarmBits = 0b00001000; // Alarm 1 every day

    rtc.turnOffAlarm(1);
    rtc.turnOffAlarm(2);
    rtc.setA1Time(alarm.alarmDay, alarm.alarmHour, alarm.alarmMinute, alarm.alarmSecond,
        alarm.alarmBits, alarm.alarmIsDay, alarm.alarmH12, alarm.alarmPM);
    rtc.turnOnAlarm(1);

    if (rtc.checkIfAlarm(1)) { 
        Serial.println("Alarm 1 set"); // the following code is kinda messy but was only put in for debug purposes
        byte A1Day;
        byte A1Hour;
        byte A1Minute;
        byte A1Second;
        byte AlarmBits;
        bool A1Dy;
        bool A1h12;
        bool A1PM;

        rtc.getA1Time(A1Day, A1Hour, A1Minute, A1Second, AlarmBits, A1Dy, A1h12, A1PM);

        Serial.print("A1Day: ");
        Serial.println(A1Day);
        Serial.print("A1Hour: ");
        Serial.println(A1Hour);
        Serial.print("A1Minute: ");
        Serial.println(A1Minute);
        Serial.print("A1Second: ");
        Serial.println(A1Second);
        Serial.print("AlarmBits: ");
        Serial.println(AlarmBits);
        Serial.print("A1Dy: ");
        Serial.println(A1Dy, BIN);
        Serial.print("A1h12: ");
        Serial.println(A1h12);
        Serial.print("A1PM: ");
        Serial.println(A1PM);
    } else {
        Serial.println("Alarm 1 not set");
        byte A1Day;
        byte A1Hour;
        byte A1Minute;
        byte A1Second;
        byte AlarmBits;
        bool A1Dy;
        bool A1h12;
        bool A1PM;

        rtc.getA1Time(A1Day, A1Hour, A1Minute, A1Second, AlarmBits, A1Dy, A1h12, A1PM);

        Serial.print("A1Day: ");
        Serial.println(A1Day);
        Serial.print("A1Hour: ");
        Serial.println(A1Hour);
        Serial.print("A1Minute: ");
        Serial.println(A1Minute);
        Serial.print("A1Second: ");
        Serial.println(A1Second);
        Serial.print("AlarmBits: ");
        Serial.println(AlarmBits);
        Serial.print("A1Dy: ");
        Serial.println(A1Dy, BIN);
        Serial.print("A1h12: ");
        Serial.println(A1h12);
        Serial.print("A1PM: ");
        Serial.println(A1PM);
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