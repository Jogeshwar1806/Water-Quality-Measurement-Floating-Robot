#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// RF24 setup
RF24 radio(9, 10); // CE, CSN pins for nRF24L01+
const byte address[6] = "00001";

// Data structure for receiving sensor readings
struct SensorData {
  float pH;
  float temperature;
  float dissolvedOxygen;
  float turbidity;
} receivedData;

void setup() {
  Serial.begin(9600);
  
  // Initialize nRF24 module
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_HIGH);
  radio.startListening();
  
  Serial.println("Receiver Initialized...");
}

void loop() {
  if (radio.available()) {
    radio.read(&receivedData, sizeof(receivedData));

    // Log received data
    Serial.print("pH: ");
    Serial.println(receivedData.pH);
    Serial.print("Temperature: ");
    Serial.println(receivedData.temperature);
    Serial.print("Dissolved Oxygen: ");
    Serial.println(receivedData.dissolvedOxygen);
    Serial.print("Turbidity: ");
    Serial.println(receivedData.turbidity);

    // Add data logging functionality (CSV, or send to server)
  }

  delay(1000);
}
