const uint16_t samples = 2048;  //This value MUST ALWAYS be a power of 2

float vReal[samples];
float vImag[samples];

ArduinoFFT<float> FFT = ArduinoFFT<float>(vReal, vImag, samples, sfreq); /* Create FFT object */
void analiza() {
  adc27.setFrequency(sfreq);
  adc27.begin();
  for (int i = 0; i < samples; i++) {
    vReal[i] = adc27.read();
    vImag[i] = 0;
  }
  adc27.end();
  FFT.windowing(FFTWindow::Hamming, FFTDirection::Forward); /* Weigh data */
  FFT.compute(FFTDirection::Forward);                       /* Compute FFT */
  FFT.complexToMagnitude();
  for (int i = 0; i < samples; i++) {
    Serial.println(vReal[i]);
  }
}