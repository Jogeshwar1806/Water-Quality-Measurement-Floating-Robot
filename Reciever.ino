#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// CE and CSN pins for the nRF24L01 module
#define CE_PIN 9
#define CSN_PIN 10

// Joystick pins
#define JOY_PIN_X A1
#define JOY_PIN_Y A0

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
  
  // Initialize joystick pins
  pinMode(JOY_PIN_X, INPUT);
  pinMode(JOY_PIN_Y, INPUT);
}

void loop() {
  // Read joystick positions
  int vx = analogRead(JOY_PIN_X);
  int vy = analogRead(JOY_PIN_Y);
  
  String messageX = "";
  String messageY = "";
  
  // Determine X-axis message
  if (vx < 200) {
    messageX = "Large Left";
  } else if (vx >= 200 && vx < 400) {
    messageX = "Small Left";
  } else if (vx >= 400 && vx <= 600) {
    messageX = "Center";
  } else if (vx > 600 && vx <= 800) {
    messageX = "Small Right";
  } else if (vx > 800) {
    messageX = "Large Right";
  }
  
  // Determine Y-axis message
  if (vy < 200) {
    messageY = "Large Down";
  } else if (vy >= 200 && vy < 400) {
    messageY = "Small Down";
  } else if (vy >= 400 && vy <= 600) {
    messageY = "Center";
  } else if (vy > 600 && vy <= 800) {
    messageY = "Small Up";
  } else if (vy > 800) {
    messageY = "Large Up";
  }

  // Combine X and Y messages
  String message = messageX + ", " + messageY;
  
  // Send message via nRF24L01
  char text[32];
  message.toCharArray(text, 32);
  radio.write(&text, sizeof(text));  // Send message
  
  // Print message to serial monitor
  Serial.print("Message sent: ");
  Serial.println(message);
  
  delay(500);  // Delay to prevent spamming
}
