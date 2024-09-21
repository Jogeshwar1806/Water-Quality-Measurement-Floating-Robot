// Function to read pH sensor data
float readPH() {
    int sensorValue = analogRead(A0); // pH sensor connected to A0
    float voltage = sensorValue * (5.0 / 1023.0); // Convert to voltage
    float pH = 7 + ((2.5 - voltage) / 0.18); // Formula for pH conversion
    return pH;
}

// Function to read temperature sensor data
float readTemperature() {
    int sensorValue = analogRead(A1); // Temperature sensor connected to A1
    float voltage = sensorValue * (5.0 / 1023.0);
    float temperature = (voltage - 0.5) * 100; // Convert to °C
    return temperature;
}

// Function to read dissolved oxygen sensor data
float readDO() {
    int sensorValue = analogRead(A2); // DO sensor connected to A2
    float voltage = sensorValue * (5.0 / 1023.0);
    float dissolvedOxygen = voltage * 100; // Adjust as per sensor's calibration
    return dissolvedOxygen;
}

// Function to read turbidity sensor data
float readTurbidity() {
    int sensorValue = analogRead(A3); // Turbidity sensor connected to A3
    float voltage = sensorValue * (5.0 / 1023.0);
    float turbidity = voltage * 100; // Adjust as per sensor's calibration
    return turbidity;
}

