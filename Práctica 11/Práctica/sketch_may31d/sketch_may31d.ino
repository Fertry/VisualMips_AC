void setup() {
  Serial.begin(9600);
  DDRD = DDRD & 0xFB;
}

void loop() {
  // 2 saltos del 2 al 0 --> >> 2
  unsigned char pulsacion = (PIND & 0x04) >> 2;

  // Compruebo si  esta pulsado:
  if (pulsacion == 0) {

      PORTD = PORTD | 0x10;
      PORTD = PORTD & 0x1BF;
      Serial.println("Pulsado");
    
  } else {

      PORTD = PORTD & 0x1EF; 
      PORTD = PORTD | 0x40;
      Serial.println("No pulsado");
      
  }
  delay(100);
}
