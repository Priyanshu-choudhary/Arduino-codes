
/* Receiver code for the Arduino Radio control with PWM output
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

  This code receive 1 channels and prints the value on the serial monitor
  Please, like share and subscribe : https://www.youtube.com/c/ELECTRONOOBS
*/


#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);


const uint64_t pipeIn = 0xE8E8F0F0E1LL;     //Remember that this code is the same as in the transmitter
RF24 radio(D4, D8); //CSN and CE pins

// The sizeof this struct should not exceed 32 bytes
struct Received_data {
  byte ch1;
};

int ch1_value = 0;
Received_data received_data;




/**************************************************/

void setup()
{
  Serial.begin(9600);

  lcd.begin();
  lcd.backlight();
  lcd.print("VOLTAGE");
  
  
  radio.begin();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.openReadingPipe(1, pipeIn);
  bool result = radio.isChipConnected ();
  Serial.println (result);
  radio.startListening();

  received_data.ch1 = 1000;
}

/**************************************************/

unsigned long last_Time = 0;

//We create the function that will read the data each certain time
void receive_the_data()
{
  while ( radio.available() ) {
    radio.read(&received_data, sizeof(Received_data));
    last_Time = millis(); //Here we receive the data
  }
}

/**************************************************/

void loop()
{
  //Receive the radio data
  receive_the_data();

  Serial.println(received_data.ch1);
  lcd.setCursor(1, 1);
  lcd.print(received_data.ch1);
  delay(100);
  lcd.clear();
}//Loop end
