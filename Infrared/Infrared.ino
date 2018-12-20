#include "IRremote.h"

int recvPin = 11; // Y on IR
int ledPin = 12; // Red LED OP 
int powerPin = 10; // Green LED OP
int buzzPin = 9; // Buzz
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

              if (myDecod.value == 12606573 || myDecod.value == 3351024064 && digitalRead(ledPin) == LOW)
                      state = 1;
                
              if (myDecod.value == 12606574 || myDecod.value == 1382615993 && digitalRead(ledPin) == HIGH)
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


