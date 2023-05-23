// nodemcu         433Mhz TX
// GND              GND
// 5V               VCC
// D3               Data

#include <VirtualWire.h> //Download it here: http://electronoobs.com/eng_arduino_virtualWire.php
#define size 2
#define INPUT_PIN A0
#define R1 1000
#define R2 10000
#define REF_VOL 3.3
//#define POT A1
#define DATA_PIN  3
byte TX_buffer[size] = {0,0};
byte i;

float vin;
float vin_avg;
float arr[2];

int readvolt(int);
void setup()
{
  pinMode(2,OUTPUT);
  digitalWrite(2,LOW);
  pinMode(5,OUTPUT);
  digitalWrite(5,HIGH);
  
  Serial.begin(9600);
  // virtual wire
  pinMode(INPUT_PIN, INPUT);
  vw_set_tx_pin(DATA_PIN); // pin
  vw_setup(2000); // bps
  for (i = 0; i < size; i++)
  {
    TX_buffer[i] = i;
  }
}

void loop()
{
//  int val = map((POT), 0, 1024, 0, 255);
  TX_buffer[0] = map(readvolt(), 1033, 1260,0, 100);
  //TX_buffer[0] = val;
  vw_send(TX_buffer, size);
  vw_wait_tx();
  Serial.print(TX_buffer[0]);
  Serial.print("   ");
  //Serial.println(TX_buffer[1]);
  delay(10);
}

int readvolt() {
  for (int i = 0; i < 500; i++) {
    vin = (( analogRead(INPUT_PIN) * REF_VOL) / 1024.0) / (R2 / (R1 + R2));
    if (vin < 0.09) {
      vin = 0.0;
    }
    vin_avg = vin_avg + vin;
  }

  return (vin_avg / 500)*100;
}
