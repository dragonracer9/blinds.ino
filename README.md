# Wake Up

## Description

Uses a servo and RTC on an Arduino to lift my blinds in the morning.

## Contents

* [Summary](#summary)
* [Hardware](#hardware)
* [Software](#software)

<hr>

## Summary

Clone this repository to wherever, then install the relevant libraries in your Arduino IDE.

The wiring to the Arduino UNO is as follows:

* servo:\
    VCC(Red) - 5V\
    SIG(orange) - D9\
    GND(Brown) - GND

    100 $\mu F$ capacitor over VCC to GND to smooth power draw

* RTC:\
    VCC - 5V\
    GND - GND\
    SDA - SDA\
    SCL - SCL\
    SQW - D2

(I dont wanna pay 8 bucks for Fritzing)

## Hardware

- sg90 (for now, until I replace my fried one).
- ZS-042 RTC (DS3231), alarm interrupt on arduino pin D2 (interrupt 0).

## Software

- Uses the [RTClib](https://github.com/NorthernWidget/DS3231/tree/master) (downloadable from within Arduino IDE)
- Wire.h
- Servo.h

Sets the time on the RTC over the arduino serial interface. Alarm is hardcoded.
