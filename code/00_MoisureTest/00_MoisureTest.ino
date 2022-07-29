
#define SERIAL_PORT 9600
#define MOISURE_SENSOR_PIN A0

void setup() {
  Serial.begin(SERIAL_PORT);
}

void loop() {
  
  int sensorValue = analogRead(MOISURE_SENSOR_PIN);
  Serial.print("read : ");
  Serial.println(sensorValue);
  
}
