// Path: includes/serial.h
#ifndef DIAGNOSTIC_H
#define DIAGNOSTIC_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#endif

#include <Servo.h> 
#include <stdint.h>

void servo_check(Servo&);

#endif // DIAGNOSTIC_H