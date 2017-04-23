#include "measurers.h"


unsigned long int second_counter = millis();

long int timer = 0;
char analog_pin ;

void set_analog(char pin)
{
  analog_pin = pin;
}

double get_voltage(bool variant)
{
  int temp = analogRead(analog_pin);
  //DEBUG
  Serial.print("Voltage   ");Serial.print(temp);Serial.print("   /   ");Serial.println(temp/1023.0*5);
  if(variant) return temp/1023.0*5; //255 SI EL MEDIDOR TIENE 8BITS Y 1023 PARA LOS DE 10BITS
  else return temp;
}

void set_timer(long int base)
{
  timer = base;
}

long int operate_timer(bool variant)
{
  if(abs(millis()-second_counter) >= 1000)
  {
    second_counter =  millis();
    //DEBUG
    Serial.print("Timer   ");Serial.println(timer);
    if(variant) return --timer;
    else return ++timer;
  }
  return timer;
}
