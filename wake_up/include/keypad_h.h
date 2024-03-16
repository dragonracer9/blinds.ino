#if !defined(KEYPAD_H)
#define KEYPAD_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#endif

#include <Keypad.h>
#include <stdint.h>

void get_date(uint8_t&, uint8_t&, uint8_t&, uint8_t&, uint8_t&, uint8_t&, uint8_t&);

#endif // KEYPAD_H
