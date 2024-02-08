# Wake Up

## Description

Uses a servo and RTC on an Arduino to lift my blinds in the morning.

## Hardware

- sg90 (for now, until I replace my fried one).
- ZS-042 RTC (DS3231), alarm interrupt on arduino pin D2 (interrupt 0).

## Software

- Uses the [RTClib](https://github.com/NorthernWidget/DS3231/tree/master) (downloadable from within Arduino IDE)
- Wire.h
- Servo.h

Sets the time on the RTC over the arduino serial interface. Alarm is hardcoded.
