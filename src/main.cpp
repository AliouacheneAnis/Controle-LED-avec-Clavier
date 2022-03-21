/*
  Titre      : Controle LED avec clavier matriciel 
  Auteur     : Anis Aliouachene
  Date       : 21/03/2022
  Description: Le programme permets de controler 4 led a l'aide d'un clavier matriciel ou les chiffres 0 a 9 designe l'intensite  et les boutton 
  A,B,C,D designe les LED et on utilise les broche PWM pour allumer les LED 
  Version    : 0.0.1
*/


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
