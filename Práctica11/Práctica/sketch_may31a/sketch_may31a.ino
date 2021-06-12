void setup() {
  Serial.begin(9600);
  DDRD = DDRD | 0x50;
}

void loop() {
  PORTD = PORTD | 0x10;
  PORTD = PORTD & 0x1BF;
  delay(1000);
  PORTD = PORTD & 0x1EF; 
  PORTD = PORTD | 0x40;
  delay(1000);
}
