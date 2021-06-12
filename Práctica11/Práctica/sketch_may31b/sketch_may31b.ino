void setup() {
  Serial.begin(9600);
  DDRD = DDRD | 0x50;
}

void loop() {
  PORTD = PORTD | 0x10;
  PORTD = PORTD & 0x1BF;
  Serial.println("1 encendido, 2 apagado");
  delay(1000);
  PORTD = PORTD & 0x1EF; 
  PORTD = PORTD | 0x40;
  Serial.println("1 apagado, 2 encendido");
  delay(1000);
}
