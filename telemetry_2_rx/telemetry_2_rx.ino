// Arduino          433Mhz RX
// GND              GND
// 5V               VCC
// D3               Data

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <VirtualWire.h>

LiquidCrystal_I2C lcd(0x3F, 16, 2);

byte message[VW_MAX_MESSAGE_LEN]; // a buffer to store the incoming messages
byte messageLength = VW_MAX_MESSAGE_LEN; // the size of the message
int received_number = 0;
int LED = 5;

void setup()
{
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  lcd.begin();
  lcd.backlight();
  Serial.println("Ready...");
  vw_set_rx_pin(3); // pin
  vw_setup(2000); // bps
  vw_rx_start();
  lcd.setCursor(0, 0);
  lcd.print("   Hello  ");
}

void loop()
{
  if (vw_get_message(message, &messageLength)) // non-blocking
  {
    Serial.print("Potentiometer: ");
    for (int i = 0; i < messageLength; i++)
    {
      Serial.print(message[i]);
      Serial.print("    ");
      received_number = message[i];
    }
    Serial.println(received_number);
    analogWrite(LED, received_number);
  }
  lcd.setCursor(0, 1);
  lcd.print(received_number);
}
