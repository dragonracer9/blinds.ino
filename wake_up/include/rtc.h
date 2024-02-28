#ifndef ALARM
#define ALARM
#include "defines.h"
#include <DS3231.h>
#include <stdint.h>

void rtc_alarm_print_time(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, bool, bool, bool);
void rtc_set_date(DS3231&, Dates&);

#endif // !ALARM