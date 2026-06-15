float capacity = 0;              // Stores the accumulated battery capacity in mAh
float vCC = 5.07;               // Measured Arduino VCC voltage for accurate ADC calculation
float R = 10.64;                // Resistance value of the load resistor in Ohms
unsigned long previousMillis = 0; // Stores the last time the capacity was updated (in milliseconds)

const int mosfetPin = 5;         // Digital pin connected to the MOSFET gate
const float cutoffVoltage = 3.0; // Minimum voltage limit to stop discharging the battery

void setup() {
  Serial.begin(9600);            // Initialize serial communication at 9600 baud rate
  pinMode(mosfetPin, OUTPUT);    // Set the MOSFET pin as an output
  digitalWrite(mosfetPin, HIGH); // Turn ON the MOSFET to start discharging the battery
  
  // Print table headers to the Serial Monitor
  Serial.println("---Battery Capacity Tester ---");
  Serial.println("Volt(V)\tCurrent(mA)\tCapacity(mAh)");
}

void loop() {
  int rawAnalog = analogRead(A0);             // Read the raw analog value (0 to 1023) from pin A0
  float voltage = (rawAnalog * vCC) / 1023.0; // Convert the raw analog value to actual battery voltage
  
  // Check if the battery voltage is still above the safe cutoff limit
  if (voltage > cutoffVoltage) {
    float current = (voltage / R) * 1000.0;   // Calculate discharge current using Ohm's Law (I = V/R) and convert to mA
    
    // Non-blocking timer: Check if 1 second (1000 ms) has passed
    if (millis() - previousMillis >= 1000) {
      capacity += current / 3600.0;           // Convert mA per second to mAh and add to total capacity
      previousMillis = millis();              // Update the timestamp for the next 1-second interval
      
      // Print the current status (Voltage, Current, Capacity) to the Serial Monitor
      Serial.print(voltage, 2);
      Serial.print(" V\t");
      Serial.print(current, 1);
      Serial.print(" mA\t");
      Serial.print(capacity, 2);
      Serial.println(" mAh");
    }
  } 
  // If the battery voltage drops to or below the cutoff limit
  else {
    digitalWrite(mosfetPin, LOW); // Turn OFF the MOSFET to stop discharging and protect the battery
    
    // Calculate the total elapsed time since the Arduino started running
    unsigned long totalSeconds = millis() / 1000; // Total time in seconds
    int totalMinutes = totalSeconds / 60;         // Extract total minutes
    int remainingSeconds = totalSeconds % 60;     // Extract remaining seconds
    
    // Print the final test results to the Serial Monitor
    Serial.println("\n--- Test Complete! ---");
    Serial.print("Final Battery Capacity: ");
    Serial.print(capacity, 2);
    Serial.println(" mAh");
    
    Serial.print("Total Time Taken: ");
    Serial.print(totalMinutes);
    Serial.print(" Minutes and ");
    Serial.print(remainingSeconds);
    Serial.println(" Seconds");
    
    while(1); // Infinite loop to halt the program execution so it doesn't repeat
  }
}
