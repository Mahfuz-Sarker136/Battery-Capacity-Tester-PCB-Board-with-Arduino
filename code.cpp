float capacity = 0;
float vCC = 5.07;         
float R = 10.64;          
unsigned long previousMillis = 0;

const int mosfetPin = 9;         
const float cutoffVoltage = 3.0; 

void setup() {
  Serial.begin(9600); 
  pinMode(mosfetPin, OUTPUT);
  digitalWrite(mosfetPin, HIGH); 
  
  Serial.println("--- MOSFET + 10.64 Ohm Battery Capacity Tester ---");
  Serial.println("Volt(V)\tCurrent(mA)\tCapacity(mAh)");
}

void loop() {
 
  int rawAnalog = analogRead(A0);
  float voltage = (rawAnalog * vCC) / 1023.0;
  
 
  if (voltage > cutoffVoltage) {
    float current = (voltage / R) * 1000.0;
    
    
    if (millis() - previousMillis >= 1000) {
      capacity += current / 3600.0; 
      previousMillis = millis();
      
    
      Serial.print(voltage, 2);
      Serial.print(" V\t");
      Serial.print(current, 1);
      Serial.print(" mA\t");
      Serial.print(capacity, 2);
      Serial.println(" mAh");
    }
  } 

  else {
    digitalWrite(mosfetPin, LOW);
    
   
    unsigned long totalSeconds = millis() / 1000;
    int totalMinutes = totalSeconds / 60;
    int remainingSeconds = totalSeconds % 60;
    
    Serial.println("\n--- Test Complete! ---");
    Serial.print("Final Battery Capacity: ");
    Serial.print(capacity, 2);
    Serial.println(" mAh");
    
    
    Serial.print("Total Time Taken: ");
    Serial.print(totalMinutes);
    Serial.print(" Minutes and ");
    Serial.print(remainingSeconds);
    Serial.println(" Seconds");
    
    while(1); 
  }
}
