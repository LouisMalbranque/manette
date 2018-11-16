/*
 * Programme de test des Boutons
 * fait fonctionner les deux avec le bouton et renvoie le résultat sur le port serie
 */

#define BoutonChannel A0

#define GachetteDroit1 A1
#define GachetteDroit2 2

#define GachetteGauch1 A2
#define GachetteGauch2 A7

// suite a un probleme indeterminé on fait ca pour avoir la valeur digitale de GachetteGauch2
#define digitalReadManette(pin)  (analogRead(pin) > 1020)



void setup() {
  Serial.begin(9600);

  // initialisation des Boutons
  pinMode(BoutonChannel, INPUT);

  pinMode(GachetteDroit1, INPUT);
  pinMode(GachetteDroit2, INPUT);

  pinMode(GachetteGauch1, INPUT);
  // pinMode(GachetteGauch2, INPUT);

}


void loop() {

  // affichage des valeurs
  Serial.println(String("Channel : ") + digitalRead(BoutonChannel) + "\tGauche : 1er= " + digitalRead(GachetteGauch1) + "  2em= " + digitalReadManette(GachetteGauch2) + "\t Droite : 1er= " + digitalRead(GachetteDroit1) + "  2em= " + digitalRead(GachetteDroit2)  );


  delay(500);
}
