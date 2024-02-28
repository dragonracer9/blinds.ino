#if !defined(DEFINES)
#define DEFINES

#define SERVO_PIN 6

// interrupt pin (on the arduino due, EXTI are on  all digital pins)
#define CLINT 52

// Define the data structures
struct Dates {
    byte year;
    byte month;
    byte date;
    byte dOW;
    byte hour;
    byte minute;
    byte second;
};

struct Alarm {
    byte alarmDay;
    byte alarmHour;
    byte alarmMinute;
    byte alarmSecond;
    byte alarmBits;
    bool alarmIsDay;
    bool alarmH12;
    bool alarmPM;
};


#endif // DEFINES
