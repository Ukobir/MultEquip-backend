

void trig() {
  adc27.setFrequency(sfreq);
  adc27.begin();
//  Muda o nível do trigger  metade do adc (adc27.read() < 2040 || adc27.read() > 2050) {}
  while (adc27.read() < 3100 || adc27.read() > 3110) {}

  digitalWrite(led, HIGH);
  for (int i = 0; i < limit; i++) {
    Serial.println(adc27.read());
  }

  adc27.end();
  digitalWrite(led, LOW);
}
