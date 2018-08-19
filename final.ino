#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "85556b7830cb477bb2da85d03bc64abb";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "NStudents";
char pass[] = "nstudents321";

BlynkTimer timer;
BlynkTimer timer1;
BlynkTimer timer2;


int trig2=D8;
int trig=D5;
int echo=D6;

int echo2=D7;

long duration1,duration2,cm,cm1;



void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V3," water tank is empty");
}

void myTimerEvent1()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V3," water tank is filled");
}
void myTimerEvent2()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V3," well is empty");
}



void setup()
{
 Serial.begin(9600);
 pinMode(trig,OUTPUT);
 pinMode(trig2,OUTPUT);
 pinMode(echo,INPUT);
 
 pinMode(echo2,INPUT);

 
 

 digitalWrite(trig,LOW);
 digitalWrite(trig2,LOW);
 

 
 delay(100);


 // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 8442);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8442);

  // Setup a function to be called every second
  timer.setInterval(1000L, myTimerEvent);
   timer1.setInterval(1000L, myTimerEvent1);
     timer2.setInterval(1000L, myTimerEvent2);


}

void loop() {
  digitalWrite(trig,HIGH);
  delay(100);
  digitalWrite(trig,LOW);
  duration1=pulseIn(echo,HIGH);
  
  digitalWrite(trig2,HIGH);
  delay(100);
  digitalWrite(trig2,LOW);
  duration2=pulseIn(echo2,HIGH);

  
  cm=(duration1/2)/29.1;
  cm1=(duration2/2)/29.1;

 

  if(cm1<80){
   if(cm>50){
  Serial.println(cm);
  Serial.println(" water tank is empty");
      Blynk.run();
  timer.run(); // Initiates BlynkTimer
  
}


   if(cm<10){
   Serial.println(cm);
  Serial.println(" water tank is filled");
    Blynk.run();
  timer1.run(); // Initiates BlynkTimer
  
}

  }
  else if(cm1>80){
     Serial.println(cm1);
    Serial.println("the wel is empty");
      Blynk.run();
  timer2.run(); // Initiates BlynkTimer
  
     
  }

}
