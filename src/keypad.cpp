#include "../include/keypad.h"

void get_date(byte& year, byte& month, byte& date, byte& dOW,
    byte& hour, byte& minute, byte& second)
{

    Serial.println("Please enter an x-terminated string of the form YYMMDDwHHMMSS");
    boolean gotString = false;
    char inChar;
    char data[20];

    byte j = 0;
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

    year = (byte)(data[0] - '0') * 10 + (byte)(data[1] - '0');
    month = (byte)(data[2] - '0') * 10 + (byte)(data[3] - '0');
    date = (byte)(data[4] - '0') * 10 + (byte)(data[5] - '0');
    dOW = (byte)(data[6] - '0'); // 0 is Sunday
    hour = (byte)(data[7] - '0') * 10 + (byte)(data[8] - '0');
    minute = (byte)(data[9] - '0') * 10 + (byte)(data[10] - '0');
    second = (byte)(data[11] - '0') * 10 + (byte)(data[12] - '0');
}
