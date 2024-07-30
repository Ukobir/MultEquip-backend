
void vou() {
  mike.setFrequency(250000);
  mike.begin();
  digitalWrite(enableMux, LOW);
  digitalWrite(rSelPins[0], HIGH);  
  digitalWrite(rSelPins[1], HIGH);  
  digitalWrite(rSelPins[2], HIGH);
  while (mike.read() > 20) {
  }
  float time_d = micros();
  digitalWrite(rSelPins[0], LOW);   
  digitalWrite(rSelPins[1], HIGH);  
  digitalWrite(rSelPins[2], LOW);
  while (mike.read() < 2588) {
  }
  float time_c = micros();
  digitalWrite(enableMux, HIGH);
  float T = DELAY_CI*(time_c - time_d);
  float mf = T / rRef[0];
  mike.end();
  Serial.println(mf);
}