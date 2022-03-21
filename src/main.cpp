#include <Arduino.h>
#include <WIFIConnector_MKR1010.h>
#include "MQTTConnector.h"
#include "Fonction.h"


void setup() {
  
   wifiConnect(); // Branchement au WIFI 
   MQTTConnect(); // Branchement au broker MQTT 

// Setup des broche LED en mode OUTPUT 
   pinMode(LED1, OUTPUT);
   pinMode(LED2, OUTPUT);
   pinMode(LED3, OUTPUT);
   pinMode(LED4, OUTPUT);

// Mettre les broche des LED en LOW 
   eteint();
}

void loop() {

// Appeler la fonction 
  readKp4x4();
}
