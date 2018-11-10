#include "manette.h"
#include <SPI.h>      // Pour la communication via le port SPI
#include <Mirf.h>     // Pour la gestion de la communication
#include <nRF24L01.h> // Pour les définitions des registres du nRF24L01
#include <MirfHardwareSpiDriver.h> // Pour la communication SPI

Manette::Manette(){
}
void Manette::initMirf(){
  Mirf.cePin = 9; // Broche CE sur D9
  Mirf.csnPin = 10; // Broche CSN sur D10
  Mirf.spi = &MirfHardwareSpi; // On veut utiliser le port SPI hardware
  Mirf.init(); // Initialise la bibliothèque

  Mirf.channel = 0; // Choix du canal de communication (128 canaux disponibles, de 0 à 127)
  Mirf.payload = sizeof(int) * 8; // Taille d'un message (maximum 32 octets)
  Mirf.config(); // Sauvegarde la configuration dans le module radio

  Mirf.setTADDR((byte *) "nrf02"); // Adresse de transmission
  Mirf.setRADDR((byte *) "nrf01"); // Adresse de réception

	return;			// sequence d'initialisation du NRF
}
void Manette::send(){
	Mirf.send((byte *) &donneesBrut); // On envoie le message
  while (Mirf.isSending()); // On attend la fin de l'envoi
}
void Manette::initBoutons(){
	pinMode(BOUTONR1, INPUT);
	pinMode(BOUTONR2, INPUT);
	pinMode(BOUTONL1, INPUT);
	pinMode(BOUTONL2, INPUT);

	pinMode(BOUTONJD, INPUT_PULLUP);
	pinMode(BOUTONJG, INPUT_PULLUP);

	pinMode(BOUTONC, INPUT);

  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);
}
void Manette::getBoutons(){
  donneesBrut[0] = 0b00000000;
	donneesBrut[0] = (donneesBrut[0] << 1) + digitalRead(BOUTONR1);
	donneesBrut[0] = (donneesBrut[0] << 1) + digitalRead(BOUTONR2);
	donneesBrut[0] = (donneesBrut[0] << 1) + digitalRead(BOUTONL1);
	donneesBrut[0] = (donneesBrut[0] << 1) + (analogRead(BOUTONL2)>512);

  donneesBrut[0] = (donneesBrut[0] << 1) + digitalRead(BOUTONJD);
  donneesBrut[0] = (donneesBrut[0] << 1) + digitalRead(BOUTONJG);

  donneesBrut[0] = (donneesBrut[0] << 1) + digitalRead(BOUTONC);

  donneesBrut[1] = analogRead(JOYSTICKDROITX);
  donneesBrut[2] = analogRead(JOYSTICKDROITY);
  donneesBrut[3] = analogRead(JOYSTICKGAUCHEX);
  donneesBrut[4] = analogRead(JOYSTICKGAUCHEY);

}
void Manette::displayBoutons(){
  for (int i=0; i<5; i++){
    Serial.print(donneesBrut[i]);
    Serial.print("\t");
  }
  Serial.println();
}
void Manette::channel(){
  int etatch = digitalRead(BOUTONC);
  if (etatch != etatprecch) {
    if (etatch == 1) {
      ch++;
      if (ch > 7) ch = 0;
    }
    Mirf.channel = ch; 
    Mirf.config();
    ledColor(ch);
  }
  etatprecch = etatch;
}
void Manette::ledColor(int color){
  digitalWrite(LEDR, bitRead( (byte) color, 2));  
  digitalWrite(LEDG, bitRead( (byte) color, 1));  
  digitalWrite(LEDB, bitRead( (byte) color, 0));  
}
