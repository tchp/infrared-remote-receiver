#include "IRremote.h"

int recvPin = 11;
int ledPin = 12;
int powerPin = 10;
int buzzPin = 9;
int state = 0;
//char samsungRed = 3772790473;
//char samsungGreen = 3772786903;

IRrecv myRecv(recvPin);
decode_results myDecod;



void setup() 
{
   Serial.begin(9600);

   
   pinMode(recvPin, INPUT);
   pinMode(ledPin, OUTPUT);
   pinMode(powerPin, OUTPUT);
   pinMode(buzzPin, OUTPUT);
   setupFlash();
   
   myRecv.enableIRIn();
}

void loop() 
{
  digitalWrite(powerPin, HIGH);
  
     if (myRecv.decode(&myDecod))
     {
             Serial.println(myDecod.value);
             myRecv.resume();

              if (myDecod.value == 119 || myDecod.value == 2167 && digitalRead(ledPin) == LOW)
                      state = 1;
                
              if (myDecod.value == 118 || myDecod.value == 2166 && digitalRead(ledPin) == HIGH)
                      state = 0;
             
             
             switch (state)
             {
              
              case 1:
                  {
                      digitalWrite(ledPin, HIGH);
                      tone(buzzPin, 100);
                      myRecv.resume();
                      break;
                  }

               case 0:
                    {
                      digitalWrite(ledPin, LOW);
                      noTone(buzzPin);
                      myRecv.resume();
                      break;
                    }
                  
             }//switch
      }//if
}//loop



void flash(int rate)
{
  digitalWrite(ledPin, HIGH);
  delay(rate);
  digitalWrite(ledPin, LOW);
  delay(rate);
}

void setupFlash()
{
  for (int i = 0; i < 2; i++)
  {
    flash(50);
    delay(50);
    flash(50);
    delay(800);
  }
}


