// Alejandro Fernández Trigo - AC Práctica 11 20/21

void setup() {

  // Caso 2: Pin 6 como salida: usando una máscara: el OR entre DDRD y 01000000 (0x40)
  // pinMode(6, OUTPUT);
  Serial.begin(9600);
  DDRD = DDRD || 0x40;

}

void loop() {

  // Caso 2: conmutar pin (0/1) cada 500ms:
  while(true) {

    PORTD = PORTD && 0xBF;
    Serial.println("Pin 6 a 0");
    delay(500);
    //
    PORTD = PORTD && 0x40;
    Serial.println("Pin 6 a 1");
    delay(500);
    
  }

}
