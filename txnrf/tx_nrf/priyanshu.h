#ifndef PRIYANSHU_H
#define PRIYANSHU_H
#include <Arduino.h>

#define RES 0.001075
#define VOLT_PIN A0
#define R1 1000
#define R2 10000
#define CURRENT_PIN A1
#define BAT_WAR 10.00
#define LED_WAR_PIN  2


short voltage(char[2],int,int);
short current(char[2],short);
void low_battery_check(short);
void blinkled(int);
#endif
