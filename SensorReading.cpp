#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// Define sensor pins (modify according to your setup)
#define PH_PIN A0
#define TEMP_PIN A1
#define DO_PIN A2
#define TURBIDITY_PIN A3

// RF24 setup
RF24 radio(9, 10); // CE, CSN pins for nRF24L01+

// Address for the nRF24 module
const byte address[6] = "00001";

// Data structure for transmitting sensor readings
struct SensorData {
  float pH;
  float temperature;
  float dissolvedOxygen;
  float turbidity;
} data;

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(9600);
  
  // Initialize nRF24 module
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_HIGH);
  radio.stopListening();
  
  // Initialize sensors (if necessary)
  pinMode(PH_PIN, INPUT);
  pinMode(TEMP_PIN, INPUT);
  pinMode(DO_PIN, INPUT);
  pinMode(TURBIDITY_PIN, INPUT);
  
  Serial.println("Water Quality Robot Initialized...");
}

void loop() {
  // Read sensors
  data.pH = readPH();
  data.temperature = readTemperature();
  data.dissolvedOxygen = readDO();
  data.turbidity = readTurbidity();
  
  // Send data via nRF24
  bool report = radio.write(&data, sizeof(data));
  if (report) {
    Serial.println("Data sent successfully.");
  } else {
    Serial.println("Failed to send data.");
  }

  // Delay for a while before next reading
  delay(2000);
}

// Function to read pH sensor
float readPH() {
  int sensorValue = analogRead(PH_PIN);
  float voltage = sensorValue * (5.0 / 1023.0);
  float pHValue = 7 + ((2.5 - voltage) / 0.18); // Adjust based on your sensor's calibration
  return pHValue;
}

// Function to read temperature sensor
float readTemperature() {
  int sensorValue = analogRead(TEMP_PIN);
  float voltage = sensorValue * (5.0 / 1023.0);
  float temperature = (voltage - 0.5) * 100; // Example for LM35 sensor
  return temperature;
}

// Function to read dissolved oxygen sensor
float readDO() {
  int sensorValue = analogRead(DO_PIN);
  float voltage = sensorValue * (5.0 / 1023.0);
  float dissolvedOxygen = voltage * 100; // Placeholder formula, calibrate accordingly
  return dissolvedOxygen;
}

// Function to read turbidity sensor
float readTurbidity() {
  int sensorValue = analogRead(TURBIDITY_PIN);
  float voltage = sensorValue * (5.0 / 1023.0);
  float turbidity = voltage * 100; // Placeholder formula, calibrate accordingly
  return turbidity;
}
