#include<Arduino.h>
#include "HX711.h"
#include <ESP8266WiFi.h>
#include <ThingESP.h>
int count  = 0;
ThingESP8266 thing("Pratham16", "Salinelevel", "123456789");
// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 12;
const int LOADCELL_SCK_PIN = 13;

HX711 scale;

void setup() {
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(2,OUTPUT);
  pinMode(0,OUTPUT);
  Serial.begin(115200);
  Serial.println("HX711 Demo");
  Serial.println("Initializing the scale");
  
  thing.SetWiFi("Pratham's Galaxy S20 FE 5G", "dfzr6724");

  thing.initDevice();


  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);


  scale.set_scale(-499.542);
  //scale.set_scale(-471.497);                      // this value is obtained by calibrating the scale with known weights; see the README for details
  scale.tare();               // reset the scale to 0

  

}

void loop() {
  Serial.print("one reading:\t");
  Serial.print(abs(scale.get_units()), 1);
  Serial.print("\t| average:\t");
  Serial.println(abs(scale.get_units(10)), 5);
  float curr_weight = abs(scale.get_units(5));
  if(curr_weight>250 and curr_weight <500)
  {
    digitalWrite(4,HIGH);
    digitalWrite(0,HIGH);
  }
  else
  {
    digitalWrite(4,LOW);
    digitalWrite(0,LOW);
  }
  if(curr_weight<250 and curr_weight >150)
    {
    digitalWrite(2,HIGH);
    }
  else
  {
    digitalWrite(2,LOW);
  }
  if( curr_weight >= 25 and curr_weight <=150)
    {
     digitalWrite(5,HIGH);
     digitalWrite(0,HIGH);
     if(count == 0)
     {
      String msg = "Saline level Low!!!";
      thing.sendMsg("+917028851709",msg);
     }
     count+=1;
    }
   else
   {
    digitalWrite(5,LOW);
    digitalWrite(0,LOW);
    }
    thing.Handle();
}
