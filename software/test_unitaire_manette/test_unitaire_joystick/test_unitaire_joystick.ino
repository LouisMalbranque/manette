/*
 * Programme de test des Joysticks
 * fait fonctionner les deux avec le bouton et renvoie le résultat sur le port serie
 */



 #define JoystickGaucheX A3
 #define JoystickGaucheY A4
 #define JoystickGaucheBouton 6

 #define JoystickDroiteX A6
 #define JoystickDroiteY A5
 #define JoystickDroiteBouton 4




void setup() {
  Serial.begin(9600);

  // initialisation des bouton des Joysticks
  pinMode(JoystickDroiteBouton, INPUT_PULLUP);
  pinMode(JoystickGaucheBouton, INPUT_PULLUP);

}

void loop() {
  // affichage des valeurs

  Serial.print(String("Gauche : X= ") + analogRead(JoystickGaucheX) + " Y= " + + analogRead(JoystickGaucheY) + " Bouton = " + digitalRead(JoystickGaucheBouton)  + "\t");
  Serial.println(String("Droite : X= ") + analogRead(JoystickDroiteX) + " Y= " + + analogRead(JoystickDroiteY) + " Bouton = " + digitalRead(JoystickDroiteBouton) );

  delay(200);
}
