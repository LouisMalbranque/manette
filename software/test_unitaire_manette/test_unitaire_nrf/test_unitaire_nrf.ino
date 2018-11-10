/**
 * Exemple de code pour la bibliothèque Mirf – Client Ping Pong
 * https://www.carnetdumaker.net/articles/communiquer-sans-fil-avec-un-module-nrf24l01-la-bibliotheque-mirf-et-une-carte-arduino-genuino/
 */
#include <SPI.h>      // Pour la communication via le port SPI
#include <Mirf.h>     // Pour la gestion de la communication
#include <nRF24L01.h> // Pour les définitions des registres du nRF24L01
#include <MirfHardwareSpiDriver.h> // Pour la communication SPI

void setup() {
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
  unsigned long time_message = millis(); // On garde le temps actuel retourné par millis()

  Serial.print("Ping ... ");
  Mirf.send((byte *) &time_message); // On envoie le temps actuel en utilisant une astuce pour transformer le long en octets
  while(Mirf.isSending()); // On attend la fin de l'envoi

  // Attente de la réponse
  while(!Mirf.dataReady()) { // On attend de recevoir quelque chose
    if (millis() - time_message > 1000 ) { // Si on attend depuis plus d'une seconde
      Serial.println("Pas de pong"); // C'est le drame ...
      return;
    }
  }

  // La réponse est disponible
  Mirf.getData((byte *) &time_message); // On récupère la réponse

  // On affiche le temps de latence (sans division par deux)
  Serial.print("Pong: ");
  Serial.print(millis() - time_message);
  Serial.println("ms");

  // Pas besoin de tester plus d'une fois par seconde
  delay(1000);
}
