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

    //Add the SdFat Libraries
    #include <SdFat.h>
    #include <SdFatUtil.h>
    //and the MP3 Shield Library
    #include <SFEMP3Shield.h>

     SFEMP3Shield MP3player;

     int led = 3;
     int motor = 5;
     int reedSwitch = 4;
     int speaker = 10;

     int fadeAmount = 5;
     int brightness = 0;
     boolean active = false;


    void setup() {
      pinMode(motor, OUTPUT); //Motor
      pinMode(led, OUTPUT); // LED
      pinMode(reedSwitch, INPUT); //Reed Switch
      pinMode(speaker, OUTPUT); //Speaker Enable

      analogWrite(led, 0); //LED off
      digitalWrite(reedSwitch, HIGH); //turn on internal pullups for reed input
      digitalWrite(motor, LOW); //Motor off

      MP3player.begin();
      MP3player.SetVolume(0x00, 0x00); //set volume
    }

    void loop() {

      if (digitalRead(reedSwitch) == HIGH && !active)//when door opens
      {
        active = true;
        analogWrite(led, 80);
        digitalWrite(speaker,HIGH);
        digitalWrite(motor, HIGH);
        MP3player.stopTrack();
        MP3player.playTrack(3);
      }
      else if (digitalRead(reedSwitch) == LOW && active)//when door closing
      {
        active = false;
        MP3player.stopTrack();
        MP3player.playTrack(2); 
        digitalWrite(motor, LOW);
        analogWrite(led, 255);
      }
      else if (digitalRead(reedSwitch) == LOW) //while door is closed
      {
        analogWrite(led, 0);
        digitalWrite(motor, LOW);
      }

      else
      {
        MP3player.playTrack(1);
        analogWrite(led, brightness);
        if (brightness == 0 || brightness == 255) {
          fadeAmount = -fadeAmount;
        }  
        brightness += fadeAmount;
      }

      delay(100);  
    }