/**
 * Exemple de code pour la bibliothèque Mirf – Client Ping Pong
 */
#include <SPI.h>      // Pour la communication via le port SPI
#include <Mirf.h>     // Pour la gestion de la communication
#include <nRF24L01.h> // Pour les définitions des registres du nRF24L01
#include <MirfHardwareSpiDriver.h> // Pour la communication SPI

#define pinBoutonR2 2
void setup() {
  pinMode(pinBoutonR2, INPUT);
  Serial.begin(9600);
   
  Mirf.cePin = 9; // Broche CE sur D9
  Mirf.csnPin = 10; // Broche CSN sur D10
  Mirf.spi = &MirfHardwareSpi; // On veut utiliser le port SPI hardware
  Mirf.init(); // Initialise la bibliothèque

  Mirf.channel = 1; // Choix du canal de communication (128 canaux disponibles, de 0 à 127)
  Mirf.payload = sizeof(long); // Taille d'un message (maximum 32 octets)
  Mirf.config(); // Sauvegarde la configuration dans le module radio

  Mirf.setTADDR((byte *) "nrf02"); // Adresse de transmission
  Mirf.setRADDR((byte *) "nrf01"); // Adresse de réception
   
  Serial.println("Go !"); 
}
 
void loop() {
  int data = digitalRead(pinBoutonR2);
  Serial.println(data);
  Mirf.send((byte *) &data); // On envoie le temps actuel en utilisant une astuce pour transformer le long en octets
  while(Mirf.isSending()); // On attend la fin de l'envoi

} 
