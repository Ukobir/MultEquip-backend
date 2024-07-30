// Ohmimetro com rp2040 e analog multiplexer 4066
// por Leonardo Romão

#define _PWM_LOGLEVEL_ 3
#include "RP2040_PWM.h"

#include <arduinoFFT.h>

RP2040_PWM* PWM_Instance;

#include <ADCInput.h>

// CONSTANTES GLOBAIS
const int NUM_REF_RESISTORS = 7;
const int MAX_ANALOG_VALUE = 4095;
const int nPort = 3;
const int SWITCH_RESISTANCE = 100.25;  //100.25
const float DELAY_CI = 0.03846;
const byte enableMux = 16;

//DMA Config
ADCInput adc27(A2);
ADCInput mike(A0);
long sfreq = 50000;

//PWM Config
float freq = 1330;
float duty = 50;
const int pinToUse = 22;


//Resistores Referencia A   B    C
const byte rSelPins[3] = { 13, 12, 9 };
const int rRef[7] = { 219, 988, 5500, 10050, 56000, 750000, 100000 };  //faltando escolher provavel 0, 10k e 100k

const int led = 25;

float calOffset = 0;
int const limit = 260;
unsigned long buffer[limit];


bool dir = 0;
void setup() {
  pinMode(enableMux, OUTPUT);
  digitalWrite(enableMux, HIGH);
  Serial.begin(115200);
  for (int i = 0; i < nPort; i++) {
    pinMode(rSelPins[i], OUTPUT);  // Mux select pins configured as outputs
  }
  pinMode(led, OUTPUT);

  adc27.setBuffers(12, 32);
  mike.setFrequency(sfreq);
  adc27.setFrequency(sfreq);

  PWM_Instance = new RP2040_PWM(pinToUse, freq, duty);
  PWM_Instance->setPWM(pinToUse, freq, duty);
  pinMode(23, OUTPUT);
  digitalWrite(23, HIGH);
}

void loop() {

  if (Serial.available()) {
    char ch = Serial.read();
    switch (ch) {
      case '0':
        digitalWrite(led, HIGH);
        sfreq = 100;
        digitalWrite(led, LOW);
        break;
      case '1':
        digitalWrite(led, HIGH);
        sfreq = 500;
        digitalWrite(led, LOW);
        break;
      case '2':
        digitalWrite(led, HIGH);
        sfreq = 1000;
        digitalWrite(led, LOW);
        break;
      case '3':
        digitalWrite(led, HIGH);
        sfreq = 5000;
        digitalWrite(led, LOW);
        break;
      case '4':
        digitalWrite(led, HIGH);
        sfreq = 10000;
        digitalWrite(led, LOW);
        break;
      case '5':
        digitalWrite(led, HIGH);
        sfreq = 50000;
        digitalWrite(led, LOW);
        break;
      case '6':
        digitalWrite(led, HIGH);
        sfreq = 100000;
        digitalWrite(led, LOW);
        break;
      case '7':
        digitalWrite(led, HIGH);
        sfreq = 250000;
        digitalWrite(led, LOW);
        break;
      case 'b':
        dir = !dir;
        Serial.println(dir);
        digitalWrite(led, dir);
        break;
      case 'O':
        digitalWrite(led, HIGH);
        res();
        digitalWrite(led, LOW);
        break;
      case 'S':
        osc();
        break;
      case 'C':
        digitalWrite(led, HIGH);
        vou();
        digitalWrite(led, LOW);
        break;
      case 'K':
        digitalWrite(led, HIGH);
        shortCal();
        digitalWrite(led, LOW);
      case 'a':
        digitalWrite(led, HIGH);
        analiza();
        digitalWrite(led, LOW);
        break;
      case 'T':
        trig();
        break;
    }
  }
}