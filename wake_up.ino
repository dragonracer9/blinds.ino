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

#include <Wake.h>