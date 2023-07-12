#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <WiFi.h>
#include <FirebaseESP32.h>

uint32_t delayMS;
#define sensor_agua 21
#define sensor_motor 4
#define dths 2
#define DHTTYPE DHT11   
DHT_Unified dht(dths, DHTTYPE);



#define FIREBASE_HOST "tower-garden-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "h4oZhjYR0M38YcH7kPvRljWnGn6SEJKubiCKbmi1"
FirebaseData tower_garden;
String ruta ="tower-garden";// difinimos ruta de firebase

const char * ssid = "daga07";
const char * password = "Daga0777";

float h;
float t;






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

  
  WiFi.begin(ssid, password);
  delay(3000);
 
  Serial.print("Se esta conectando a la red wifi denominada");
  Serial.println(ssid);
  
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.println(".");
  }
  Serial.println("");
  Serial.println("Wifi connected");
  Serial.println("IP address:");
  Serial.println(WiFi.localIP());

  // Conexion a Firebase
  Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  //Temperatura y Humedad
 Serial.println(F("DTH text"));
  dht.begin();
  if (isnan(h) || isnan(t)){
    Serial.println(F("Falla en la lectura del sensor"));
    return;
  }
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
  h= event.temperature;
  t= event.relative_humidity;

   Serial.print(F("Humedad: "+"%")); //La F() siginifica que lo que esta dentro del parentesis se escribe en la FLASH
   Serial.print(h);
   Serial.println("");
   Serial.print(F("Temperatura:"+"°C")); //La F() siginifica que lo que esta dentro del parentesis se escribe en la FLASH
   Serial.print(t);
   Serial.println("");
   
   Firebase.setInt(tower_garden,ruta+"/Humedad",t);
   Firebase.setInt(tower_garden,ruta+"/Temperatura",h);

   Serial.print(F("Temperature: "));
    Serial.print(event.temperature);
    Serial.println(F("°C"));
    Serial.print(F("Humidity: "));
    Serial.print(event.relative_humidity);
    Serial.println(F("%"));

   /* Serial.print(F("Temperature: "));
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
  }*/
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

 

