#include "button.h"


unsigned long int last_second = millis();
unsigned long int time_past = 0;

char in_button;

bool triggered = false;
bool state_button = false; // OFF



void set_digital_inbutton(char pin)
{
  in_button = pin;
  pinMode(pin, INPUT);
}

void update_second()
{
  if(!(digitalRead(in_button) && state_button))
  {
    if(!digitalRead(in_button) && state_button)
    {
      triggered = true;
      time_past = abs(millis() - last_second);
      //DEBUG
      //Serial.print("Time past   ");Serial.println(time_past);
    }
    state_button = digitalRead(in_button);
    last_second = millis();
  }
}

bool change_mode()
{
  if(time_past >= 500 && triggered)
  {
    triggered = false;
    time_past = 0;
    return true;
  }
  return false;
}

bool change_variant()
{
  if(time_past >= 10 && time_past < 500 &&triggered)
  {
    triggered = false;
    time_past = 0;
    return true;
  }
  return false;
}
