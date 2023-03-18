#include <Arduino.h>

/**
 * @brief esta es la funcion de configuracion del dispositivo
 * @brief daniel gallo
 * */

void setup() {
  pinMode(2,OUTPUT); // coloco el pin 2 como salida
}

/**
 * @brief Esta funcion es un bucle inifinito que corresponde al main()
*/
void loop() {
  digitalWrite(2,HIGH);// EnCiende el LED
  delay(500);// Espera Milisegundos
  digitalWrite(2,LOW);// Apaga el LED
  delay(500);//Espera Milisegundos
}