#include "../include/keypad.h"

void get_date(uint8_t & year, uint8_t & month, uint8_t & date, uint8_t & dOW,
    uint8_t & hour, uint8_t & minute, uint8_t & second)
{

    Serial.println("Please enter an x-terminated string of the form YYMMDDwHHMMSS");
    boolean gotString = false;
    char inChar;
    char data[20];

    uint8_t  j = 0;
    while (!gotString) {
        if (Serial.available()) {
            inChar = Serial.read();
            data[j] = inChar;
            j += 1;
            if (inChar == 'x') {
                gotString = true;
            }
        }
    }
    Serial.print("date entered: ");
    Serial.println(data);

    year = (uint8_t )(data[0] - '0') * 10 + (uint8_t )(data[1] - '0');
    month = (uint8_t )(data[2] - '0') * 10 + (uint8_t )(data[3] - '0');
    date = (uint8_t )(data[4] - '0') * 10 + (uint8_t )(data[5] - '0');
    dOW = (uint8_t )(data[6] - '0'); // 0 is Sunday
    hour = (uint8_t )(data[7] - '0') * 10 + (uint8_t )(data[8] - '0');
    minute = (uint8_t )(data[9] - '0') * 10 + (uint8_t )(data[10] - '0');
    second = (uint8_t )(data[11] - '0') * 10 + (uint8_t )(data[12] - '0');
}
