#ifndef DIGITS_H
#define DIGITS_H
#include <Arduino.h>


/*
 *  ESTE CONJUNTO DE FUNCIONES ESTAN TRABAJAR CON VALORES ENTEROS  MAX 9 DIGITOS.
 *  SE REDUCE UN DIGITO PARA EL MAXIMO EN CASO DE MOSTRAR UN NUMERO NEGATIVO EL CUAL
 *  SERA UTILIZADO PARA REPRESENTAR EL MAXIMO,
 *  EJEMPLO: SE CUENTA CON 5 DISPLAYS Y SE MOSTRARA COMO MAXIMO EL NUMERO 99999
 *  PERO EN EL CASO DEL MINIMO EL NUMERO SERA -9999 DEBIDO A QUE UN DISPLAY ES UTILIZADO
 *  PARA MOSTRAR QUE EL NUMERO QUE SE MUESTRA ES NEGATIVO
 */




void is_anodo(bool a_c);
int set_frequency(bool &variant);
void set_digitalout(char *pins);
void set_multiplexing(char *pins);
void separate_numbers(long int n);
void show_digits(char digit);
void show_number(long int n, double variant = 0.0);

#endif //DIGITS_H
