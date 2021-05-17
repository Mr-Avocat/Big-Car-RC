//Créé par camille Jouhet en 2019

#include <SoftwareSerial.h>
#include <Servo.h>
Servo monServo;
SoftwareSerial HC06(10, 11); //RX et TX port virtuel pour communiquer avec le module
int positionDuServo = 90 , VitesseVoiture = 0, last_position;
bool save_speed, save_direction, message_ok;
String vitesse, angle;


void setup()
{

  HC06.begin(9600);
  Serial.begin(9600);
  monServo.attach(9);
  monServo.write(positionDuServo);

}

void loop()
{
  message_ok = 0;
  save_speed = 0;
  save_direction = 0;
  vitesse = "";
  angle = "";

  //  Serial.println("ok");
  while (message_ok == 0) {
    if (HC06.available())
    {

      char mode_char = HC06.read();
      if (mode_char == 'X')
      {
        save_speed = 0;
        save_direction = 1;
      }
      else if (mode_char == 'Y')
      {
        save_speed = 1;
        save_direction = 0;
      }
      else if (mode_char == 'Z')
      {
        message_ok = 1;
      }
      else
      {
        if (save_speed) {
          vitesse += mode_char;
        }
        else if (save_direction)
        {
          angle += mode_char;
        }
      }
    }
  }

  last_position = positionDuServo;
  positionDuServo = map(angle.toInt(), 0, 100, 70, 120);
  VitesseVoiture = 0;

  //  Serial.println(positionDuServo);
  //Serial.println(angle);

  if (abs(last_position - positionDuServo) > 1)
  {
    if (last_position < positionDuServo)
    {
      positionDuServo = positionDuServo + 1;
    }
    else
    { 
      positionDuServo = positionDuServo - 1;
    }
  }
  monServo.write(positionDuServo);

  delay(100);
}
