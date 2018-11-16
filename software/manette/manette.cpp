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

  Mirf.channel = 2; // Choix du canal de communication (128 canaux disponibles, de 0 à 127)
  Mirf.payload = 22; // Taille d'un message (maximum 32 octets)
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
	donneesBrut[0] = digitalRead(BOUTONR1);
	donneesBrut[1] = digitalRead(BOUTONR2);
	donneesBrut[2] = digitalRead(BOUTONL1);
	donneesBrut[3] = analogRead(BOUTONL2)>512;

  donneesBrut[4] = digitalRead(BOUTONJD);
  donneesBrut[5] = digitalRead(BOUTONJG);

  donneesBrut[6] = digitalRead(BOUTONC);

  donneesBrut[7] = analogRead(JOYSTICKDROITX);
  donneesBrut[8] = analogRead(JOYSTICKDROITY);
  donneesBrut[9] = analogRead(JOYSTICKGAUCHEX);
  donneesBrut[10] = analogRead(JOYSTICKGAUCHEY);

}
void Manette::displayBoutons(){
  for (int i=0; i<11; i++){
    Serial.print(donneesBrut[i]);
    Serial.print("\t");
  }
  Serial.println(sizeof(donneesBrut));
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
    ledColor(Mirf.channel);
  }
  etatprecch = etatch;
}
void Manette::ledColor(int color){
  digitalWrite(LEDR, bitRead( (byte) color, 2));  
  digitalWrite(LEDG, bitRead( (byte) color, 1));  
  digitalWrite(LEDB, bitRead( (byte) color, 0));  
}
