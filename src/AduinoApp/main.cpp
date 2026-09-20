#include <avr/io.h>
#include <util/delay.h>

void setup() {
   pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);  // LED encendido
  delay(500);                      // 500 ms
  digitalWrite(LED_BUILTIN, LOW);   // LED apagado
  delay(500);
}

int main(){

    setup();
    loop();

    return 0;
}