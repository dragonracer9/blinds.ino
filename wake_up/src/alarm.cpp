#include "../include/alarm.h"
#include "../include/defines.h"
#include <DS3231.h>

void rtc_set_alarm(Alarm alarm,
    bool isDay = true,
    bool h12 = false,
    bool PM = false,
    uint8_t  day = 1,
    uint8_t  hour = 7,
    uint8_t  min = 30,
    uint8_t  sec = 0,
    uint8_t  bits = 0b00001000)
{
    alarm.alarmIsDay = isDay;
    alarm.alarmH12 = h12; // use 24-hour time mode
    alarm.alarmPM = PM;

    alarm.alarmDay = day; // 1 is Sunday
    alarm.alarmHour = hour;
    alarm.alarmMinute = min;
    alarm.alarmSecond = sec;
    alarm.alarmBits = bits; // Alarm 1 every day
}

void rtc_alarm_print_time(uint8_t  A1Day,
    uint8_t  A1Hour,
    uint8_t  A1Minute,
    uint8_t  A1Second,
    uint8_t  AlarmBits,
    bool A1Dy,
    bool A1h12,
    bool A1PM)
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

void rtc_set_date(DS3231& rtc, )
{
    rtc.setYear(now.year);
    rtc.setMonth(now.month);
    rtc.setDate(now.date);
    rtc.setDoW(now.dOW);
    rtc.setHour(now.hour);
    rtc.setMinute(now.minute);
    rtc.setSecond(now.second);
}