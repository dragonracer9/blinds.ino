#if !defined(WAKE)
#define WAKE

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#endif

#include "defines.h"
#include "diagnostic.h"
#include "keypad_h.h"
#include "lcd.h"
#include "rtc.h"
#include <stdint.h>

void isr_wakeUp();

#endif // WAKE