#include <Arduino.h>

// define the pin for the SPI Clock

#define SPI_SCK_PIN (16)
#define SPI_SS_PIN (17)

#define CLOCK_DELAY delayMicroseconds(10)

// define this to do a pin  0..RANGE instead.
//#define RANGE   (200)

// list of GPIO pins to toggle, makes sure SPI_SS_PIN and SPI_SCK_PIN isn't in here ( spi test routine detects those pins and ignores them)
const int gpioPins[] = {
  0,1,2,3,4,5,6,7,8,9,
  10,11,12,13,14,15,18,19,
  20,21,22,23,24,25,26,27,28,29,
  30,31,32,33,34,35,36,37,38,39,
  40,41,42,43,44,45,46,47,48,49,
  50,51,52,53,54,55,56,57,58,59,
  60,61,62,63,64,65,66,67,68,69,
  70,71,72,73,74,75,76,77,78,79,

};

const int numPins = sizeof(gpioPins) / sizeof(gpioPins[0]);
void outputWithLeadersAndEncoding();
void encodeAndOutputPinNumber(int pin, int index);
void encodeAndOutputPinNumberRS232(int pin, int index);
void emulateSPIOutput(int pinNumber );

void setup() {
#ifdef SPI_SCK_PIN
  // initialize the clock pin as OUTPUT
  pinMode(SPI_SCK_PIN, OUTPUT);
  digitalWrite(SPI_SCK_PIN, LOW); // ensure clock starts in idle state
#endif  
#ifdef SPI_SS_PIN
  pinMode(SPI_SS_PIN, OUTPUT);
  digitalWrite(SPI_SS_PIN, LOW);
#endif

  // initialize all the GPIO pins in the list as OUTPUT
  for(int i = 0; i < numPins; i++) {
    pinMode(gpioPins[i], OUTPUT);
  }



}

void loop() {

  // output sequence with leaders and 8-bit encoding of pin numbers
  outputWithLeadersAndEncoding();

}

/**
 * @brief toggles each pin in the gpioPins array with an 8-bit encoding of the pin index, with a start/end leader delay.
 */
void outputWithLeadersAndEncoding() {
  
  delay(5); // leader signal duration
  
#ifndef RANGE
  // toggle each pin with its 8-bit encoded index
  for(int i = 0; i < numPins; i++) {
    emulateSPIOutput(gpioPins[i]);
  }
#else
  for(int i = 0; i < RANGE; i++) {
    emulateSPIOutput(i);
  }
#endif

  delay(5); // leader signal duration
}

/**
 * @brief encodes and outputs the 8-bit representation of the pin's index number.
 * @param pin The GPIO pin to toggle.
 * @param index The index of the pin, to encode and output.
 */
void encodeAndOutputPinNumber(int pin, int index) {
  for(int bit = 7; bit >= 0; bit--) {
    int bitValue = (index >> bit) & 1;
    digitalWrite(pin, bitValue);
    delay(1); // simple delay
  }
}

/**
 * @brief encodes and outputs the 8-bit representation of the pin's index number using RS-232 format (8N1).
 * @param pin GPIO pin to toggle.
 * @param index index of the pin, to encode and output.
 */
void encodeAndOutputPinNumberRS232(int pin, int index) {
  
  // start bit
  digitalWrite(pin, LOW);
  delay(2); // start bit duration

  // data bits (LSB first)
  for(int bit = 0; bit < 8; bit++) {
    int bitValue = (index >> bit) & 1;
    digitalWrite(pin, bitValue ? HIGH : LOW); // invert logic for RS-232 if needed
    delay(10); // bit duration
  }

  // stop bit
  digitalWrite(pin, HIGH);
  delay(2); // stop bit duration
}


/**
 * @brief emulates SPI MOSI output, writes pinNumber to pin +clock
 */
void emulateSPIOutput(int pinNumber ) {

// don't toggle to these pins
  if( pinNumber == SPI_SCK_PIN ) return;
  if( pinNumber == SPI_SS_PIN ) return;

    digitalWrite(SPI_SS_PIN, HIGH);
    delayMicroseconds(5);

    // simulate SPI transfer for the pin number
    for(int bit = 7; bit >= 0; bit--) {
      int bitValue = (pinNumber >> bit) & 1;

      digitalWrite(pinNumber, bitValue ? HIGH : LOW); 

      // toggle the clock (low -> high -> low) to emulate the SPI clock signal
      digitalWrite(SPI_SCK_PIN, LOW); // ensure clock starts in idle state
      CLOCK_DELAY; // clock low period to prepare for data sampling
      digitalWrite(SPI_SCK_PIN, HIGH); // data is sampled on this rising edge
      CLOCK_DELAY; // clock high period to complete the data bit transfer
      digitalWrite(SPI_SCK_PIN, LOW); // return to idle state, completing the clock cycle
    }
    delayMicroseconds(5);

    digitalWrite(SPI_SS_PIN, LOW);

    delayMicroseconds(100);
}