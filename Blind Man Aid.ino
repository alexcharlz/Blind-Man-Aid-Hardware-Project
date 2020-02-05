#include <rm4.h>

const int water = A1;
const int button = 7;
const int trigger = 2; //Trigger pin of 1st Sesnor
const int echo = 3; //Echo pin of 1st Sesnor
const int Buzz = 4; //Echo pin of 1st Sesnor
const int Light = A5; //Echo pin of 1st Sesnor
long time_taken;
int dist;
int Signal;
int Intens;
int similar_count;
static const int kData0Pin = 9;
static const int kData1Pin = 10;
static const int kData2Pin = 11;
static const int kData3Pin = 12;
static const int kEnablePin = 13;

RM4 remote(kData0Pin, kData1Pin, kData2Pin, kData3Pin);

void setup() {
Serial.begin(9600); 
pinMode(Buzz,OUTPUT);
digitalWrite(Buzz,LOW);
pinMode(trigger, OUTPUT); 
pinMode(echo, INPUT); 
pinMode(button, INPUT);
pinMode(water, INPUT);
pinMode(kEnablePin, OUTPUT);
digitalWrite(kEnablePin, HIGH);
}


/*###Function to calculate distance###*/
void calculate_distance(int trigger, int echo)
{
digitalWrite(trigger, LOW);
delayMicroseconds(2);
digitalWrite(trigger, HIGH);
delayMicroseconds(10);
digitalWrite(trigger, LOW);
time_taken = pulseIn(echo, HIGH);
dist= time_taken*0.034/2;
if (dist>300)
dist=300;
}


void loop() { //infinite loopy
calculate_distance(trigger,echo);
Intens = analogRead(Light);


const int button_code = remote.buttonCode();
if((button_code == 8)||(button_code == 4)||(button_code == 2)||(button_code == 1)){
  Serial.print(similar_count); Serial.println("Remote Pressed");
  digitalWrite(Buzz,HIGH);delay(3000);digitalWrite(Buzz,LOW);
}


int water_value = analogRead(water);
if (water_value > 500){
  digitalWrite(Buzz, HIGH);
}
else{
  digitalWrite(Buzz, LOW);
}

int val = digitalRead(button);
if(val ==1){
//If very dark
if (Intens<200)
{
  Serial.print(Intens); Serial.println("Bright Light");
  digitalWrite(Buzz,HIGH);delay(200);digitalWrite(Buzz,LOW);delay(200);digitalWrite(Buzz,HIGH);delay(200);
  digitalWrite(Buzz,LOW);delay(200);
  delay(500);
}
//If very bright
if (Intens>800)
{
  Serial.print(Intens); Serial.println("Low Light");
  digitalWrite(Buzz,HIGH);delay(500);digitalWrite(Buzz,LOW);delay(500);digitalWrite(Buzz,HIGH);delay(500);
  digitalWrite(Buzz,LOW);delay(500);
  }
}


if (dist<75)
{
  Serial.print(dist); Serial.println("Object Alert");
  
  digitalWrite(Buzz,HIGH);
  for (int i=dist; i>0; i--)
    delay(10);
  digitalWrite(Buzz,LOW);
  for (int i=dist; i>0; i--)
    delay(10);
    
}
}
