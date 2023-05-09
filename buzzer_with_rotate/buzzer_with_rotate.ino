// Pin assignments
const int SENSOR_PIN = A0;   // Rotary angle sensor input pin
const int BUZZER_PIN = 3;    // Buzzer output pin

// Variables
int sensorValue = 0;         // Current sensor value
int buzzerVolume = 128;      // Buzzer volume, range from 0 to 255
int buzzerPitch = 350;       // Buzzer pitch, in Hz
int delayTime = 500;         // Delay time between TIK TIK patterns, in milliseconds

void setup() {
  // Set up buzzer pin as output
  pinMode(BUZZER_PIN, OUTPUT);
  
  // Serial communication for debugging
  Serial.begin(9600);
}

void loop() {
  // Read sensor value and map it to a delay between 50 and 200 ms
  sensorValue = analogRead(SENSOR_PIN);
  int sensorDelay = map(sensorValue, 0, 1023, 50, 200);
  
  // Map sensor value to BPM between 50 and 200
  int bpm = map(sensorValue, 0, 1023, 50, 200);
  // Calculate delay time in ms based on BPM
  delayTime = 60000 / bpm / 2;
  
  // Debugging output
  Serial.print("Sensor value: ");
  Serial.println(sensorValue);
  Serial.print("Sensor delay: ");
  Serial.println(sensorDelay);
  Serial.print("BPM: ");
  Serial.println(bpm);
  Serial.print("Delay time: ");
  Serial.println(delayTime);
  
  // Play TIK TIK pattern on the buzzer
  for (int i = 0; i < 6; i++) {
    analogWrite(BUZZER_PIN, buzzerVolume); // Set buzzer volume
    tone(BUZZER_PIN, buzzerPitch, 10);     // Play tone for 10 ms
    delay(delayTime);                      // Wait for specified delay time
    noTone(BUZZER_PIN);                    // Turn off buzzer
    delay(delayTime);                      // Wait for specified delay time
  }
  
}
