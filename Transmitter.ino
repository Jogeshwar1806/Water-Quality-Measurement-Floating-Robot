#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// CE and CSN pins for the nRF24L01 module
#define CE_PIN 9
#define CSN_PIN 10

// Create an RF24 object
RF24 radio(CE_PIN, CSN_PIN);

// Address of the receiver (same for both transmitter and receiver)
const byte address[6] = "00001";

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_HIGH);  // Power Amplifier level
  radio.stopListening();  // Set the module as transmitter
}

void loop() {
  const char text[] = "Hello World!";
  radio.write(&text, sizeof(text));  // Send message
  Serial.println("Message sent: Hello World!");
  delay(1000);  // Wait 1 second before sending the next message
}
