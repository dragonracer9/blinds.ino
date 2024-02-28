#if !defined(DEFINES)
#define DEFINES

#define SERVO_PIN 6

// interrupt pin (on the arduino due, EXTI are on  all digital pins)
#define CLINT 52

// Define the data structures
struct Dates {
    uint8_t  year;
    uint8_t  month;
    uint8_t  date;
    uint8_t  dOW;
    uint8_t  hour;
    uint8_t  minute;
    uint8_t  second;
};

struct Alarm {
    uint8_t  alarmDay;
    uint8_t  alarmHour;
    uint8_t  alarmMinute;
    uint8_t  alarmSecond;
    uint8_t  alarmBits;
    bool alarmIsDay;
    bool alarmH12;
    bool alarmPM;
};


#endif // DEFINES
