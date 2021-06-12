void setup() {
  Serial.begin(9600);
  DDRD = DDRD & 0xFB;
  attachInterrupt(0,rutina_int,CHANGE);
  sei();
}

void loop() {
  int i;
  for(i=0;i<10;i++){
    Serial.println(i);
    delay(1000);
  }
}

void rutina_int() {
  // 2 saltos del 2 al 0 --> >> 2
  unsigned char pulsacion = (PIND & 0x04) >> 2;

  // Compruebo si  esta pulsado:
  if (pulsacion == 0) {
      Serial.println("Pulsado");
  } 
  delay(100);
}
