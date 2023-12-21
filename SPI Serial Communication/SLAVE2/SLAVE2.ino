#include <SPI.h>

const int redLed = 3;
const int greenLed = 2;

char data_received[100];
char count;
volatile bool rx_complete; 

void setup() {
  Serial.begin(115200);

  SPCR |= bit(SPE);      /* Enable SPI */
  pinMode(MISO, OUTPUT); /* Make MISO pin as OUTPUT */
  count = 0;
  rx_complete = false;
  SPI.attachInterrupt(); /* Attach SPI interrupt */

  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
}

void loop() {

  while (rx_complete == false) {
    Serial.println(data_received);
    waitLed();
  }

  if (rx_complete && data_received == "Hi 2!") {
    Serial.println("Complete");
    Serial.println(data_received);
  } else if (rx_complete == false && data_received != "Hi 2!") {
    data_received[count] = 0;
    rx_complete = false;
  }

  while (rx_complete) {
    Serial.println("Received!");
    receivedLed();
  }
}

void waitLed() {
  digitalWrite(redLed, HIGH);  // Turn the green LED on
  delay(500);                  // Wait for 1/2 second (500 milliseconds)
  digitalWrite(redLed, LOW);   // Turn the green LED off
  delay(500);
}

void receivedLed() {
  digitalWrite(greenLed, HIGH);  // Turn the green LED on
  delay(500);                    // Wait for 1/2 second (500 milliseconds)
  digitalWrite(greenLed, LOW);   // Turn the green LED off
  delay(500);
}



// SPI interrupt routine
ISR(SPI_STC_vect) {
  uint8_t oldsrg = SREG;
  cli();
  char var = SPDR;
  if (count < sizeof(data_received)) {
    data_received[count++] = var;
    if (var == '!') { /* Check for newline character as end of msg */
      rx_complete = true;
    }
  }
  SREG = oldsrg;
}
