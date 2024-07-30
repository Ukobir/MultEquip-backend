
void osc() {
  adc27.setFrequency(sfreq);
  adc27.begin();
  digitalWrite(led, HIGH);
  for (int i = 0; i < limit; i++) {
    Serial.println(adc27.read());
  }
  adc27.end();
  digitalWrite(led, LOW);
}
