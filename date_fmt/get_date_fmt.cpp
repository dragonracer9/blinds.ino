// Description: Get the date from the user and format to date and time on the RTC module.
#include <stdio.h>
#include <string.h>

struct DateTime {
    int year;
    int month;
    int day;
    int dOW;
    int hour;
    int minute;
    int second;
};

const char* dayNames[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

int main(int argc, char const* argv[])
{
    char date[20];
    if (argc > 1) {
        strcpy(date, argv[1]);
    } else {
        printf("Enter the date in the format YYMMDDowHHMMSS\n");
        scanf("%s", date);
    }
    DateTime now;

    now.year = int(date[0] - '0') * 10 + int(date[1] - '0');
    now.month = int(date[2] - '0') * 10 + int(date[3] - '0');
    now.day = int(date[4] - '0') * 10 + int(date[5] - '0');
    now.dOW = int(date[6] - '0');
    now.hour = int(date[7] - '0') * 10 + int(date[8] - '0');
    now.minute = int(date[9] - '0') * 10 + int(date[10] - '0');
    now.second = int(date[11] - '0') * 10 + int(date[12] - '0');
    printf("Year: %d\nMonth: %d\nDay: %d\nDay of Week: %d (%s)\nHour: %d\nMinute: %d\nSecond: %d\n", now.year, now.month, now.day, now.dOW, dayNames[now.dOW], now.hour, now.minute, now.second);

    printf("----------------------\n");
    printf("formatted for RTC module\n");
    printf("----------------------\n");
    printf("rtc.setYear(%d);\n", now.year);
    printf("rtc.setMonth(%d);\n", now.month);
    printf("rtc.setDate(%d);\n", now.day);
    printf("rtc.setDoW(%d);\n", now.dOW);
    printf("rtc.setHour(%d);\n", now.hour);
    printf("rtc.setMinute(%d);\n", now.minute);
    printf("rtc.setSecond(%d);\n", now.second);
    
    return 0;
}
