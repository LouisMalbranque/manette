#include "manette.h"

Manette maManette;

int target = 0;
int once = 0;
int AUTREOK = 0;
int DRONEOK = 1;
int HOVERCRAFTOK = 2;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  maManette.initMirf();
  maManette.initBoutons();
}

void loop() {
  // put your main code here, to run repeatedly:
  maManette.getBoutons();
  maManette.channel();
  maManette.send();

  //maManette.displayBoutons();

}
