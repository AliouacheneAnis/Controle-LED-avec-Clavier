#include<Arduino.h>
#include <Keypad.h>

//Constants
#define ROWS 4
#define COLS 4
const int LED1 = 2;
const int LED2 = 3;
const int LED3 = 4;
const int LED4 = 5;

//Parameters
const char kp4x4Keys[ROWS][COLS]  = {{'1', '2', '3', 'A'}, {'4', '5', '6', 'B'}, {'7', '8', '9', 'C'}, {'*', '0', '#', 'D'}};

// Setup Pin
byte rowKp4x4Pin [4] = {13, 12, 11, 10};  
byte colKp4x4Pin [4] = {9, 8, 7, 6};

//Variables
Keypad kp4x4  = Keypad(makeKeymap(kp4x4Keys), rowKp4x4Pin, colKp4x4Pin, ROWS, COLS);

int LedSelected, Intensite, LedSelectedString; 
int LastIntensiteLed1, LastIntensiteLed2 ,LastIntensiteLed3 ,LastIntensiteLed4, LastIntensite; 
char PreviousKey; 


// Declaration Fonction 
void readKp4x4(); 
void eteint();


void readKp4x4() {

 // function readKp4x4 
 //  Read button states from keypad
  char customKey = kp4x4.getKey();
  
  if (customKey) {
      
      switch (customKey)
      {  
        
        case 'A':  // Dans le cas de pression sur la touche A 

            LedSelected = LED1;  // Affecter numero de la broche de la led 1 dans la variable LedSelected puisque on a selectionner la led 1 
            LedSelectedString = 1; // Affecter le chiffre 1 qui designe LED 1 pour l'envoyer sur ThingsBoard
            PreviousKey = 'A';   // Garder la trace du bouton presser 
            Intensite = LastIntensiteLed1;  // Affecter la derniere intensite de la led pour l'afficher sur Thingsboard 
            break;

        case 'B': // Dans le cas de pression sur la touche B
          
            LedSelected = LED2; // Affecter numero de la broche de la led 2 dans la variable LedSelected puisque on a selectionner la led 2
            LedSelectedString = 2; // Affecter le chiffre 2 qui designe LED 2 pour l'envoyer sur ThingsBoard
            PreviousKey = 'B';
            Intensite = LastIntensiteLed2;
            break;

        case 'C': // Dans le cas de pression sur la touche C

            LedSelected = LED3;  // Affecter numero de la broche de la led 3 dans la variable LedSelected puisque on a selectionner la led 3
            LedSelectedString = 3;// Affecter le chiffre 3 qui designe LED 3 pour l'envoyer sur ThingsBoard
            PreviousKey = 'C';
            Intensite = LastIntensiteLed3;
            break;

        case 'D': // Dans le cas de pression sur la touche D

            LedSelected = LED4; // Affecter numero de la broche de la led 4 dans la variable LedSelected puisque on a selectionner la led 4 
            LedSelectedString = 4; // Affecter le chiffre 4 qui designe LED 4 pour l'envoyer sur ThingsBoard
            PreviousKey = 'D'; 
            Intensite = LastIntensiteLed4;
            break;
        
        case '*':  // Dans le cas de pression sur la touche * rien qui ce passe  
           break;

        case '#':  // Dans le cas de pression sur la touche # rien qui ce passe  
           break;

      default:   // Dans le cas de pression sur les touches numeriques entre 0 et 9 
            
            int Key = customKey - '0'; // Converssion char en type entier int on converti les char '0' - '9' en chiffre entier 

            // Utiliser la fonction map pour la regle des troi afin d'avoir l'intensite selon le chiffre selectionner 
            // 0 c'est intensite 0 , 9 c'est l'intensite maxiamle 255  
            Intensite = map(Key,0,9,0,255);
            
            // Affectation de l'intensite au variable pour la sauvegarder et garder la dernier intensite de chaque LED
            if (PreviousKey == 'A')
                LastIntensiteLed1 = Intensite;

            else if (PreviousKey == 'B')
                LastIntensiteLed2 = Intensite;

            else if (PreviousKey == 'C')
                 LastIntensiteLed3 = Intensite;

            else if (PreviousKey == 'D')
                  LastIntensiteLed4 = Intensite;


            // Allumage de LED selectionner par une broche PWM avec une intensite entre 0 et 255  
            analogWrite(LedSelected, Intensite);
          break;
      }     

            appendPayload("Intenaite", Intensite);  //Ajout de la donnée  au message MQTT
            appendPayload("LED Selectionner ", LedSelectedString); //Ajout de la donnée au message MQTT
            sendPayload();  //Envoie du message via le protocole MQTT

 }

}

// Fontion pour eteindre tous les LED
void eteint(){
      digitalWrite(LED1 , LOW);
      digitalWrite(LED2 , LOW);
      digitalWrite(LED3 , LOW);
      digitalWrite(LED4 , LOW);
}
