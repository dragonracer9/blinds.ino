#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#endif

#include "../include/defines.h"
#include "../include/rtc.h"
#include <DS3231.h>
#include <stdint.h>

void rtc_set_date(DS3231& rtc, Dates& now)
{
    rtc.setYear(now.year);
    rtc.setMonth(now.month);
    rtc.setDate(now.date);
    rtc.setDoW(now.dOW);
    rtc.setHour(now.hour);
    rtc.setMinute(now.minute);
    rtc.setSecond(now.second);
}

void rtc_alarm_print_time(uint8_t A1Day, uint8_t A1Hour, uint8_t A1Minute,
    uint8_t A1Second, uint8_t AlarmBits, bool A1Dy,
    bool A1h12, bool A1PM)
{
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

