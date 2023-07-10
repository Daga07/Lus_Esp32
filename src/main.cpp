#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

uint32_t delayMS;
#define sensor_agua 2
#define sensor_motor 4
#define dths 15 
#define DHTTYPE DHT11   
DHT_Unified dht(dths, DHTTYPE);


 //float apagado = 2000;// (86400000/4);
 //int ensendido = 3000;//(420000);
// float level = 0;
//float niveltiempo = 3000;
// int expression = 3;
 unsigned long dthpreviosmili= 0;
 unsigned long dthcurrenmilli= 0;
 const long  humedad = 1000;

 unsigned long nivelpreviosmili= 0;
 unsigned long nivelcurrenmilli= 0;
 const long  nivel = 2000;

 unsigned long reletpreviosmili= 0;
 unsigned long reletcurrenmilli= 0;
 const long  relet = 9000;
 int ensender_motor = 4000;

 void setup(){
  Serial.begin(115200);
  dht.begin();
  pinMode(dths,OUTPUT); 
  pinMode(sensor_agua,OUTPUT);
  pinMode(sensor_motor,OUTPUT);
 } 
 void loop(){
   float level;

  dthcurrenmilli = millis();
  if(dthcurrenmilli - dthpreviosmili >= humedad){
    dthpreviosmili = dthcurrenmilli;
    sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
  }
  else {
    Serial.print(F("Temperature: "));
    Serial.print(event.temperature);
    Serial.println(F("°C"));
  }
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
  }
  else {
    Serial.print(F("Humidity: "));
    Serial.print(event.relative_humidity);
    Serial.println(F("%"));
  }
    Serial.println("-------------------");
 }

 
   nivelcurrenmilli = millis();
  if(nivelcurrenmilli - nivelpreviosmili >= nivel){
    nivelpreviosmili = nivelcurrenmilli;
    level  = analogRead(sensor_agua);
    Serial.print("Nivel de agua: ");
    Serial.println(level);
    Serial.println("-------------------");
 }

     reletcurrenmilli = millis();
    digitalWrite(sensor_motor,HIGH);  
  if(reletcurrenmilli - reletpreviosmili >= relet){
    reletpreviosmili = reletcurrenmilli;
 
   digitalWrite(sensor_motor, LOW);
   Serial.println("Motor encendido");
   delay(ensender_motor);
 
  Serial.println("-------------------");
  }
 }
 
  // Espera de 2 segundos entre cada lectura

  //------------- DTH11 -------------------
  /*sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
  }
  else {
    Serial.print(F("Temperature: "));
    Serial.print(event.temperature);
    Serial.println(F("°C"));
  }
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
  }
  else {
    Serial.print(F("Humidity: "));
    Serial.print(event.relative_humidity);
    Serial.println(F("%"));
  }

 
  //------------- MOTOR ---------------
  digitalWrite(4,HIGH);// EnCiende el motor
  Serial.println("Motor apagado ");
  delay(apagado);// Espera Milisegundos
  //Serial.println(suma);
  digitalWrite(4, LOW);// Apaga el motor
  Serial.println("Motor encendido");
  delay(ensendido);//Espera Milisegundos
  */





   /* level = analogRead(2);
    Serial.print("Nivel de agua: ");
    Serial.println(level);
  
    return level;
*/

 

