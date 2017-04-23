#ifndef MEASURERS_H
#define MEASURERS_H
#include <Arduino.h>

/*
ESTE ARCHIVO CONTIENE LAS FUNCIONES PARA LA MEDICION
DE VOLTAJE Y SEGUNDERO
*/

void set_analog(char pin);
double get_voltage(bool variant);
void set_timer(long int base);
long int operate_timer(bool variant);

#endif
