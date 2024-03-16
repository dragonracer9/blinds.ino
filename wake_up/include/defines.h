#if !defined(DEFINES)
#define DEFINES
#include <stdint.h>

#define SERVO_PIN 6

// interrupt pin (on the arduino due, EXTI are on  all digital pins)
#define CLINT 52

// Define the data structures
struct Dates {
    uint8_t year;
    uint8_t month;
    uint8_t date;
    uint8_t dOW;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
    void set_date(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t);
    void fmt_print();
};

struct Alarm {
    uint8_t alarmDay;
    uint8_t alarmHour;
    uint8_t alarmMinute;
    uint8_t alarmSecond;
    uint8_t alarmBits;
    bool alarmIsDay;
    bool alarmH12;
    bool alarmPM;
    void set_alarm(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, bool, bool, bool);
    void fmt_print();
};

#endif // DEFINES
