#include <SPI.h>      // Pour la communication via le port SPI
#include <Mirf.h>     // Pour la gestion de la communication
#include <nRF24L01.h> // Pour les définitions des registres du nRF24L01
#include <MirfHardwareSpiDriver.h> // Pour la communication SPI

#define BOUTONL1 A2
#define BOUTONL2 A7
#define BOUTONR1 A1
#define BOUTONR2 2

#define BOUTONC A0

#define JOYSTICKGAUCHEX A3
#define JOYSTICKGAUCHEY A4
#define JOYSTICKDROITX A6
#define JOYSTICKDROITY A5

#define BOUTONJD 4
#define BOUTONJG 6

#define LEDR 7
#define LEDG 5
#define LEDB 3

class Manette{
private:
	int donneesBrut[11];
	int ch=0;
	int etatprecch;

public:
	Manette();
	void initMirf();											// sequence d'initialisation du NRF
	void send();
	void getBoutons();
	void initBoutons();
	void displayBoutons();
	void channel();
  void ledColor(int color);
};
