#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#endif

#include "../include/defines.h"
#include <DS3231.h>
#include <stdint.h>

void Dates::set_date(uint8_t y, uint8_t m, uint8_t d, uint8_t DoW,
    uint8_t h, uint8_t min, uint8_t sec)
{
    year = y;
    minute = m;
    date = d;
    dOW = DoW;
    hour = h;
    minute = min;
    second = sec;
}

void Alarm::set_alarm(uint8_t day = 1, uint8_t hour = 7, uint8_t min = 30,
    uint8_t sec = 0, uint8_t bits = 0b00001000,
    bool isDay = true, bool h12 = false, bool PM = false)
{
    alarmIsDay = isDay;
    alarmH12 = h12; // use 24-hour time mode
    alarmPM = PM;

    alarmDay = day; // 1 is Sunday
    alarmHour = hour;
    alarmMinute = min;
    alarmSecond = sec;
    alarmBits = bits; // Alarm 1 every day
}

void Alarm::fmt_print()
{
    Serial.print("A1Day: ");
    Serial.println(alarmDay);
    Serial.print("A1Hour: ");
    Serial.println(alarmHour);
    Serial.print("A1Minute: ");
    Serial.println(alarmMinute);
    Serial.print("A1Second: ");
    Serial.println(alarmSecond);
    Serial.print("AlarmBits: ");
    Serial.println(alarmBits);
    Serial.print("A1isDy: ");
    Serial.println(alarmIsDay);
    Serial.print("A1h12: ");
    Serial.println(alarmH12);
    Serial.print("A1PM: ");
    Serial.println(alarmPM);
}