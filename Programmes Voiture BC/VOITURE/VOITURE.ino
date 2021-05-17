// Créé par Camille Jouhet en 2019

#include <Servo.h>
#include <SoftwareSerial.h>
SoftwareSerial HC06(10, 11); //pin numérique rx/tx
Servo monServo;//déclare l'utilisation d'un servo nommé monServo
int positionDuServo = 0; //variable indiquant la position du servomoteur
const byte TRIGGER_PIN = 2; //pin du trigger
const byte ECHO_PIN = 3; //pin de l'echo
const unsigned long MESURE_TIMEOUT = 25000UL;
const float SOUND_SPEED = 340.0 / 1000; //vitesse du son dans l'athmosphère
char PWM_ENABLE = 3; //pin1 du l293d
char moteurAV = 2; //pin2 du l293d
char moteurRE = 4; //pin7 du l293d
int vitesseDuMoteur = 0; //variable indiquant la vitesse du moteur souhaitée

void setup()
{
  pinMode(TRIGGER_PIN, OUTPUT); //initialisation du pin du trigger
  digitalWrite(TRIGGER_PIN, LOW); //éteint le pin
  pinMode(ECHO_PIN, INPUT); //initialisation du pin de l'écho
  Serial.begin(9600);//initialisation de la communication avec le moniteur série
  HC06.begin(9600);//initialisation de la communication avec le module bluetooth HC-05
  pinMode(moteurAV, OUTPUT);//déclaration de pins comme sorties
  pinMode(moteurRE, OUTPUT);
  pinMode(PWM_ENABLE, OUTPUT);
  digitalWrite(moteurAV, LOW);//ne pas envoyer de courant dans le module L293D
  digitalWrite(moteurRE, LOW);
  analogWrite(PWM_ENABLE, 0);
  monServo.attach(9);//initialisation du pin du servomoteur
  monServo.write(positionDuServo);//positionnement initial du servomoteur

}

void loop()
{
  while (HC06.available())
  {
    delay(3);
    char c = HC06.read();
    messageRecu += c;
  }
  
  if (messageRecu == "d")
  {
    digitalWrite(moteurAV, LOW);
    digitalWrite(moteurRE, LOW);
    analogWrite(PWM_ENABLE, 0);

  }

  digitalWrite(TRIGGER_PIN, HIGH);//envoi d'une impulsion ultrasonore
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  long measure = pulseIn(ECHO_PIN, HIGH, MESURE_TIMEOUT);//calcul du temps mis part l'impulsion
  float distance_mm = measure / 2.0 * SOUND_SPEED;//calcul de la distance

  if (messageRecu == 4)//si je vais a gauche
  {
    positionDuServo = 0;

  }
  if (messageRecu == 2)//si je vais a droite
  {
    positionDuServo = 180;

  }


  if (messageRecu == 1)//si j'avance
  {
    digitalWrite(moteurAV, HIGH);
    digitalWrite(moteurRE, LOW);
    vitesseDuMoteur = 175;
    positionDuServo = 90;

  }
  if (messageRecu == 3)//si je recule
  {
    digitalWrite(moteurAV, LOW);
    digitalWrite(moteurRE, HIGH);
    vitesseDuMoteur = 75;
    positionDuServo = 90;

  }
  analogWrite(PWM_ENABLE, vitesseDuMoteur);
  monServo.write(positionDuServo);

}
