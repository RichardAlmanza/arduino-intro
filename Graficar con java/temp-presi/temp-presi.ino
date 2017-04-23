#include <Wire.h>
#include <Adafruit_BMP085.h>

Adafruit_BMP085 bmp;

long tiempo;

void setup() {
  Serial.begin(9600);
  pinMode(9,OUTPUT);  //trig
  pinMode(8,INPUT);    //echo
  
  if (!bmp.begin()) {
	Serial.println("Error, no se encuentra el sensor, verificar conexiones");
	while (1) {}
  }
  
}
  
void loop() {
    Serial.print(bmp.readTemperature());
    Serial.print(";");
    Serial.print(bmp.readPressure());
    Serial.print(";");
    
    digitalWrite(9,LOW);  //trig
    delayMicroseconds(5);
    digitalWrite(9,HIGH);
    delayMicroseconds(10);
    tiempo=pulseIn(8,HIGH);  //Microsegundos
    //Velocidad del sonido 340 m/s ó 0,034 cm/microsegundo
    //Volumen de la geringa
    //V=(Vi - (distancia calculada-distancia del sensor al objeto)*PI*r^2)
    Serial.print(50-int(0.017*tiempo-5.48)*PI*(1.6)*(1.6));
    Serial.println();
    
    delay(100);
}
