#ifndef BUTTON_H
#define BUTTON_H
#include <Arduino.h>

/*
 * EN ESTE ARCHIVO SE OBTIENE INFORMACION
 * DEL BOTON PARA CONTROLAR EL FUNCIONAMIENTO DEL PROGRAMA
 */

void set_digital_inbutton(char pin);
void update_second();
bool change_mode();
bool change_variant();
#endif
