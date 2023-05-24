#include "priyanshu.h"

int ledState = LOW;
unsigned long previousMillis = 0;


void low_battery_check(short bat_war) {

  if (voltage(VOLT_PIN,R1,R2) < bat_war) {
    blinkled(100);
  } else {
    digitalWrite(LED_WAR_PIN, 0);
  }
}


short current(char current_pin[], short acsref) {
  return ((voltage(current_pin,R1,R2) - acsref) * 66);
}


short voltage(char volt_pin[] , int r1, int r2  ) {
  uint8_t sample = 0;
  for (uint8_t i = 0; i < 100; i++) {
    sample += analogRead( volt_pin );
    delay(1);
  }

  return (((sample / 100) * RES) * (r2 / (r1 + r2)));
}

void blinkled(int intreval) {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= intreval) {
    previousMillis = currentMillis;
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }

  }
  return 0;
}
