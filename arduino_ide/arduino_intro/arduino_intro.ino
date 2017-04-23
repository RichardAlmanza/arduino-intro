#include "digits.h"
#include "button.h"
#include "measurers.h"

char modes = 0;

bool variants = false;

void setup() {
	// put your setup code here, to run once:
	//DEBUG
	Serial.begin(9600);
	is_anodo(true);
	set_digitalout(new char[8]{2,3,4,5,6,7,8,9});
  set_multiplexing(new char[5]{4,10,11,12,13});
  set_digital_inbutton(A3);
	set_analog(A0);
}

void loop() {
	// put your main code here, to run repeatedly:
	update_second();
  if(change_mode())
  {
    modes++;
    variants = false;
    if(modes > 2) modes = 0;
    else if(modes == 2) set_timer(0);
  }
  if(change_variant()) variants = !variants;
  switch(modes)
  {
    case 0:
      show_number(set_frequency(variants),0.0);
      break;
    case 1:
			if(variants) show_number(0,get_voltage(variants));
			else show_number(get_voltage(variants),0.0);
			break;
    case 2:
      show_number(operate_timer(variants),0.0);
      break;
  }
}
