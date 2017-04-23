#include "digits.h"

unsigned char *digits_display7seg = new unsigned char[11]
{
  0b11111100,//#0 IGUAL QUE ==> {HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,LOW,LOW}
  0b01100000,//#1 DISPLAY 7 SEGMENTOS, VALORES EN A,B,C,D,E,F,G,H
  0b11011010,//#2
  0b11110010,//#3
  0b01100110,//#4
  0b10110110,//#5
  0b10111110,//#6
  0b11100000,//#7
  0b11111110,//#8
  0b11110110,//#9
  0b00000010 //#10 ESTE REPRESENTA EL MENOS EN LOS NUMEROS NEGATIVOS
};

char *digital_pins = NULL;
char *multiplexing_pins = NULL;
char *number = NULL;

char counter = 1; // DECIDE CUAL DIGITO SERA EL ACTIVO
bool anodoc = 0; //TENDRA LA INFORMACION SI ES ANODO O CATODO COMUN

float frequency = 50; // LA FRECUENCIA EN HERTZ (Hz)
unsigned long int uptime;// MEDIDO EN MICROSEGUNDOS || ES EL TIEMPO ACTIVO PARA CADA DIGITO

unsigned long int last_uptime_digit = micros();

unsigned long int limit = 10;

void is_anodo(bool a_c)
{
  anodoc = a_c;
}

int set_frequency(bool &variant)
{
  if(variant)
  {
    variant = false;
    frequency += 10;
    if(frequency > 240) frequency = 10;
    uptime = 1000000 / (frequency * *multiplexing_pins);
    //DEBUG
    Serial.print("Frequency  ");Serial.print(frequency);Serial.print("   /   ");Serial.println(uptime);
  }
  return frequency;
}

void set_digitalout(char *pins)//char[8] {segA, segB, segC, segD, segE, segF, segG, segH} ||SERAN DE SALIDA, OUTPUT
{
  digital_pins = pins;
  if(anodoc)
  {
    for(char i = 0; i < 11; i++)
    {
      *(digits_display7seg+i) = ~*(digits_display7seg+i);
    }

  }

  for (char i = 0; i < 8; i++)
  {
    pinMode(*(pins + i), OUTPUT);
  }
}


void set_multiplexing(char *pins)  //{n,pin1,pin2...}EN ORDEN SEGUN CADA DISPLAY, LA UNIDADES VAN PRIMERO QUE LAS DECENAS  Y N ES LA CANTIDAD DISPLAYS
{
  multiplexing_pins = pins;
  uptime = 1000000 / (frequency * *multiplexing_pins);
  limit = long(pow(10,*pins));
  number = new char[*pins];
  for(char i = 0; i < *pins; i++)
  {
    *(number+i) = -1;
    pinMode(*(pins+i+1), OUTPUT); // PINS SELECCIONADOS
    digitalWrite(*(pins+i+1), !anodoc); // PINS DESACTIVADOS || PARA APAGAR HIGH SI ES CATODO COMUN
  }
}


void separate_numbers(long int n)
{
  bool is_negative = n < 0;
  n = abs(n) % limit;
  //Serial.print(n);
  *(number+*multiplexing_pins-1) =  long(n / pow(10,*multiplexing_pins-1))%10;
  if(*(number+*multiplexing_pins-1) == 0) *(number+*multiplexing_pins-1) = -1;
  for(char i = *multiplexing_pins-2; i >=0; i--)
  {
    *(number+i) = long(n / pow(10,i))%10;
    if(*(number+i) == 0 && *(number+i+1) == -1) *(number+i) = -1;
  }
  if(*number == -1) *number = 0;
  if(is_negative)
  {
    for(char i = 0; i < *multiplexing_pins; i++)
    {
      if(*(number+i) == -1)
      {
        is_negative = false; // AQUI CAMBIA SU PROPOSITO || is_negative  QUEDARA CON EL VALOR TRUE SI n ES NEGATIVO Y NO SE ENCONTRO CAMPO VACIO PARA COLOCAR EL SIGNO MENOS (-)
        *(number+i) = 10;
        break;
      }
    }
    if(is_negative) *(number+*multiplexing_pins-1) = 10; //COMPRUEBA CON EL NUEVO PROPOSITO
  }
  //DEBUG
/*
  Serial.print("separate_number   ");
  for(char i = *multiplexing_pins - 1 ; i >= 0; i--)
  {
    Serial.print(int(*(number+i)));Serial.print('|');
  }
  Serial.println();
*/
}


void show_digits(char digit)
{
  if(digit != -1)
  {
    for (char i = 0; i < 8; i++)
    {
      digitalWrite(*(digital_pins + i), bitRead(*(digits_display7seg + digit), 7-i));
    }
  }else{
    for (char i = 0; i < 8; i++)
    {
      digitalWrite(*(digital_pins + i), anodoc);
    }
  }
}


void show_number(long int n, double variant) //ESTA FUNCION ES LA QUE SE ENCARGA DE MOSTRAR EL NUMERO CON MULTIPLEXADO
{
  if(abs(micros() - last_uptime_digit) >= uptime)
  {
    last_uptime_digit = micros();
    digitalWrite(*(multiplexing_pins+counter), !anodoc); // APAGA EL DIGITO ANTERIOR
    counter++;
    if(counter > *multiplexing_pins)
    {
      counter = 1;
      if(variant != 0.0) n = variant * limit / 10;
      separate_numbers(n);
    }
    digitalWrite(*(multiplexing_pins+counter), anodoc); // ENCIENDE EL SIGUIENTE DIGITO
    show_digits(*(number + counter - 1)); // SELECCIONA LOS SEGMENTOS INDICADOS PARA EL NUMERO CORRESPONDIENTE
    if(variant != 0.0)
    {
      if(*(number + counter - 1) == -1) show_digits(0);
      if(counter == *multiplexing_pins) digitalWrite(*(digital_pins + 7), !anodoc);
    }
  }

}
