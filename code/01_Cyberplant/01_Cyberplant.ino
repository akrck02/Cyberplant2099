#define SERIAL_PORT 9600

#define MOISTURE_SENSOR_PIN A0
#define PUMP_PIN 12

#define MOISTURE_SENSOR_DRY 537
#define MOISTURE_SENSOR_WET 210

#define MOISTURE_OFFSET 35 // This constant will be different on each plant, check it
#define WATERING_TIME 1000

#define DAY_TIME 86400000

/**
 * Pre start setup
 */
void setup() {
  
  // Start serial communication
  Serial.begin(SERIAL_PORT);
  Serial.println("Hi, I'm cyberplant, how are you? :D");
  
  //Reset the values
  pinMode(PUMP_PIN, OUTPUT);
  digitalWrite(PUMP_PIN,HIGH);  
}

/**
 * Main loop of the Arduino logic
 */
void loop() {

  // Get humidity percent
  int percent = getHumidityPercent();

  // If the plant need water 
  while(percent < MOISTURE_OFFSET){
    water();
    percent = getHumidityPercent();
  }

  // Print happy plant messages
  Serial.print("Cyberplant: my humidity is ");
  Serial.print(percent);
  Serial.println("%\n");

  delay(DAY_TIME); 
}

/**
 * Get the humidity percentage of the cyberplant
 */
int getHumidityPercent(){
  
  int sensorValue = analogRead(MOISTURE_SENSOR_PIN) - MOISTURE_SENSOR_WET;
  int minMoisture = 0;
  int maxMoisture = MOISTURE_SENSOR_DRY - MOISTURE_SENSOR_WET;

  // Calculate percentage
  int percent = 100 - (((double) sensorValue)/ maxMoisture) * 100;

  // Normalizing percentages (The sensor precission can change with time)
  if(percent > 100){
    percent = 100;
  } else if(percent < 0){
    percent = 0;
  }

  return percent;
}

/**
 * Water the cyberplant
 */
void water() {
   digitalWrite(PUMP_PIN,LOW);  
   delay(WATERING_TIME);
   digitalWrite(PUMP_PIN,HIGH);  
   Serial.println("Cyberplant: Some water for me :)");
}
