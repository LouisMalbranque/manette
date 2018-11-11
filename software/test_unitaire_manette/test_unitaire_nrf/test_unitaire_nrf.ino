/**
 * Fichier de test du module nrf24l01
 * Ici est utiliser la gachette droite 2 (tester son fonctionnement)
 */
#include <SPI.h>                   // Pour la communication via le port SPI
#include <Mirf.h>                  // Pour la gestion de la communication
#include <nRF24L01.h>              // Pour les définitions des registres du nRF24L01
#include <MirfHardwareSpiDriver.h> // Pour la communication SPI

#define pinBoutonR2 2

// comenter les ligne si dessous pour ne pas avoir de port série connecté
#define DEBUG_USB 1

void setup() {

  // Initialisation du module nrf avec la librairie mirf
  Mirf.cePin = 9;                 // Broche CE sur D9
  Mirf.csnPin = 10;               // Broche CSN sur D10
  Mirf.spi = &MirfHardwareSpi;    // On veut utiliser le port SPI hardware
  Mirf.init();                    // Initialise la bibliothèque

  Mirf.channel = 1;                // Choix du canal de communication (128 canaux disponibles, de 0 à 127)
  Mirf.payload = sizeof(long);     // Taille d'un message (maximum 32 octets)
  Mirf.config();                   // Sauvegarde la configuration dans le module radio

  Mirf.setTADDR((byte *) "nrf02"); // Adresse de transmission
  Mirf.setRADDR((byte *) "nrf01"); // Adresse de réception

  // débugage USB
  #ifdef DEBUG_USB
  Serial.begin(9600);
  Serial.println("Go !");
  #endif

  //on déclare le bouton comme une entrée
  pinMode(pinBoutonR2, INPUT);
}

/**
 * fonction loop dans la quelle on lit la valeur du A1
 */
void loop() {
  // on lit la valeur de la gachete droite 1
  int data = digitalRead(pinBoutonR1);

  #ifdef DEBUG_USB
  Serial.println(data);
  #endif

  // on envoie la valeur de la gachette droite 1
  Mirf.send((byte *) &data);

  // On attend la fin de l'envoi
  while(Mirf.isSending());

}
