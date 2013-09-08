//SFEMP3Library author Bill Porter
//SFEMP3Library author Michael P. Flaga
/* MP3 Player Shield Music Box Code Example:  
SparkFun Electronics, Pamela, 1/24/2013  
Beerware License  

Hardware Connections:
-LED = D3 on MP3 Player Shield;  
-Motor = D5 on MP3 Player Shield;
-Reed Switch = D4 on MP3 Player Shield;
-Mono Audio Amp Breakout Board Shutdown Pin = D10 on MP3 Player Shield;
You will need to solder header pins to the MP3 Player Shield.  
Put the shield on top of an Arduino Uno.    

Usage:  
When the door opens, the motor will spin and a sound file will play.  
The sound file will loop.   
Then when the door closes the motor stops spinning and a new track plays one time. */

#include <SPI.h>
#include <SdFat.h>
#include <SdFatUtil.h>
#include <SFEMP3Shield.h>
#include <Servo.h>

 SFEMP3Shield MP3player;
 Servo monServo;
 int boutonUn = 3;
 int servoPin = 5;


void setup() {
  Serial.begin(9600);
  pinMode(servoPin, OUTPUT); //Servo
  pinMode(boutonUn, INPUT); //Bouton
  monServo.attach(servoPin);
}

void loop() {
  Serial.println(digitalRead(boutonUn));

  if (digitalRead(boutonUn) == LOW)//Appui sur bouton 1
  {
    Serial.println("Test");
    Serial.println(boutonUn);
    monServo.write(0);    //Pour le moment sur un servo non continu
  }
  else if (digitalRead(boutonUn) == HIGH) //while door is closed
  {
    monServo.write(90);
  }
  
  delay(100);  
}
