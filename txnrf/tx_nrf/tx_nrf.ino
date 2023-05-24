
/* Tranmsitter code for the Arduino Radio control with PWM output
   Install the NRF24 library to your IDE
   Upload this code to the Arduino UNO, NANO, Pro mini (5V,16MHz)
   Connect a NRF24 module to it:

    Module // Arduino UNO,NANO

    GND    ->   GND
    Vcc    ->   3.3V
    CE     ->   D9
    CSN    ->   D10
    CLK    ->   D13
    MOSI   ->   D11
    MISO   ->   D12

  This code transmits 1 channels with data from pins A0 POTENTIOMETER
  Please, like share and subscribe : https://www.youtube.com/c/ELECTRONOOBS
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "priyanshu.h"
const uint64_t my_radio_pipe = 0xE8E8F0F0E1LL; //Remember that this code should be the same for the receiver

RF24 radio(9, 10);

#define VOLT_PIN A0
#define R1 1000
#define R2 10000
#define CURRENT_PIN A1
#define BAT_WAR 10.00
#define LED_WAR_PIN  2

short volt;
short acsref;
struct Data_to_be_sent {
 
  short volt;
  short current;
  short power;
};

Data_to_be_sent sent_data;

void setup()
{ Serial.begin(9600);
  radio.begin();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.openWritingPipe(my_radio_pipe);
  bool result = radio.isChipConnected ();
  Serial.println (result);
  analogReference(INTERNAL);
  delay(500);
  acsref = voltage(VOLT_PIN,R1,R2);
  pinMode(LED_WAR_PIN, OUTPUT);
}

/**************************************************/


void loop()
{
  sent_data.volt = voltage(VOLT_PIN,R1,R2);
  sent_data.current = current(CURRENT_PIN,acsref);
  sent_data.power= (sent_data.volt*sent_data.current);

  low_battery_check(BAT_WAR);
  radio.write(&sent_data, sizeof(Data_to_be_sent));
}
