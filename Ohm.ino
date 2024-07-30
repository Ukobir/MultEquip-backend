

void res() {
  int cOut;
  float delta, deltaBest1 = MAX_ANALOG_VALUE, deltaBest2 = MAX_ANALOG_VALUE;
  float rBest1 = -1, rBest2 = -1, rR, rX;

  for (byte count = 0; count < NUM_REF_RESISTORS; count++) {

    digitalWrite(rSelPins[0], count & 1); // A
    digitalWrite(rSelPins[1], count & 2); // B:
    digitalWrite(rSelPins[2], count & 4); // C: most significant bit

    digitalWrite(enableMux, LOW); 
    delay(count + 1);
    cOut = filtro() - calOffset;
    digitalWrite(enableMux, HIGH);
    delay(NUM_REF_RESISTORS - count);
  

    if (cOut < MAX_ANALOG_VALUE) {
      rR = rRef[count] + SWITCH_RESISTANCE;
      rX = (rR * cOut) / (MAX_ANALOG_VALUE - cOut);

      // Compute the delta and track the top two best delta and Rx values
      delta = (MAX_ANALOG_VALUE / 2.0 - cOut);
      if (fabs(delta) < fabs(deltaBest1)) {
        deltaBest2 = deltaBest1;
        rBest2 = rBest1;
        deltaBest1 = delta;
        rBest1 = rX;
      } else if (fabs(deltaBest2) > fabs(delta)) {
        deltaBest2 = delta;
        rBest2 = rX;
      }
    }
    // Make sure there are at least two good samples to work with
    if (rBest1 >= 0 && rBest2 >= 0) {
      // Check to see if need to interpolate between the two data points.
      // Refer to the documentation for details regarding this.
      if (deltaBest1 * deltaBest2 < 0) {
        rX = rBest1 - deltaBest1 * (rBest2 - rBest1) / (deltaBest2 - deltaBest1);  // Yes
      } else {
        rX = rBest1;  // No. Just use the best value
      }

      // Convert the scaled float result to string and extract the units
    }
  }

  Serial.println(rX);
  delay(1e3);
}