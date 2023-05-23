#include <RH_ASK.h>
#include <SPI.h>

RH_ASK rf_driver;

#define INPUT_PIN A0
#define R1 1000
#define R2 10000
#define REF_VOL 5.0

float vin;
float vin_avg;

void setup()
{
  rf_driver.init();
  Serial.begin(9600);
  pinMode(INPUT_PIN, INPUT);
}

void loop() {
  readvolt();

  const char *msg = "Hello World";
  rf_driver.send((uint8_t *)msg, strlen(msg));
  rf_driver.waitPacketSent();
  delay(1000);
}
int readvolt() {
  for (int i = 0; i < 500; i++) {
    vin = (( analogRead(INPUT_PIN) * REF_VOL) / 1024.0) / (R2 / (R1 + R2));
    if (vin < 0.09) {
      vin = 0.0; 
    }
    vin_avg=vin_avg+vin;
  }
  
  return vin_avg/500;
}
