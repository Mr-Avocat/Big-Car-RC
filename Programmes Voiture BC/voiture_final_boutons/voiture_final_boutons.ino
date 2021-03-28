#include <Servo.h>
#include <SoftwareSerial.h>
Servo myServo;
SoftwareSerial HC06(10, 11); //Rx et Tx virtuels du module bluetooth
int positionDuServo = 90; // position de démarrage
const char mode_gauche = 'R' , mode_droite = 'B', mode_antigauche = 'r', mode_antidroite = 'b'; // characters envoyés par le téléphone via l'appli Bluetooth Electronics
char mode = mode_gauche;

void setup()
{
  myServo.attach(5); // pin du servo
  myServo.write(positionDuServo);
  HC06.begin (9600); // bauds du module
}

void loop()
{
  if (HC06.available()) // si msg reçu
  {
    char mode_char = HC06.read();
    switch (mode_char)
    {
      case mode_gauche:
        {
          mode = mode_gauche;
          positionDuServo = 50; // tourner à gauche
          break;
        }
      case mode_droite:
        {
          mode = mode_droite;
          positionDuServo = 120; // tourner à droite
          break;
        }
      case mode_antidroite: // boutton droit relaché
        {
          mode = mode_antidroite;
          positionDuServo = 90; // tout droit
          break;
        }
      case mode_antigauche: // boutton gauche relaché
        {
          mode = mode_antigauche;
          positionDuServo = 90; // tout droit
        }
    }
  }
  myServo.write(positionDuServo);

}
