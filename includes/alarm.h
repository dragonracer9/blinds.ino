#ifndef ALARM
#define ALARM
#include "../includes/defines.h"

void alarm_print_time(byte, byte, byte, byte, byte, bool, bool, bool);
void set_alarm(Alarm, bool, bool, bool, byte, byte, byte, byte, byte);

#endif // !ALARM