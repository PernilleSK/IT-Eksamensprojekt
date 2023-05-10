#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

// Pin assignments
const int SENSOR_PIN = A0;   // Rotary angle sensor input pin
const int BUZZER_PIN = 3;    // Buzzer output pin
const int BUTTON_PIN = 2;    // button pin 

// Variables
int sensorValue = 0;         // Current sensor value
int buzzerVolume = 128;      // Buzzer volume, range from 0 to 255
int buzzerPitch = 350;       // Buzzer pitch, in Hz
int delayTime = 500;         // Delay time between TIK TIK patterns, in milliseconds
String chords[] = {"Em", "C", "G", "D"};  // Array of chords to display
String chords1[] = {"G", "D", "Am", "C"};  // Array of chords to display
String strings[] = {"C", "D", "E", "G","A", "Cm", "Dm", "Em","Fm","Gm"};
int chordIndex = 0;          // Index of current chord to display
int z = 0;
int bpm = 0;

void setup() {
  // Set up buzzer pin as output
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);

  // Set up LCD
  lcd.begin(16, 2);
  lcd.setRGB(0, 255, 0);     // Set LCD backlight color to green

  // Serial communication for debugging
  Serial.begin(9600);

  bool buttonState = digitalRead(BUTTON_PIN);
  int z = 0;
  bool pause = false;

  randomSeed(analogRead(0));
}

void loop() {
  // Read sensor value and map it to a delay between 50 and 200 ms
  sensorValue = analogRead(SENSOR_PIN);
  int sensorDelay = map(sensorValue, 0, 1023, 50, 200);

  bpm = map(sensorValue, 0, 1023, 50, 200);

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

  bool buttonState = digitalRead(BUTTON_PIN);
  
  Serial.print("hihihihihihihi");
  Serial.print(z);
  bool pause = true;
  //for the button to change between 3 stages  
  if(buttonState == HIGH)
  {
    Serial.print("nenenennene");
    Serial.print(z);
    
    if(z == 0 && pause == true)
    {
      z = 1;
      Serial.print("nonononono");
      Serial.print(z);
      chordIndex = 0;
      pause = false;
    }
    
    if(z == 1 && pause == true)
    {
      z = 2;
      Serial.print("minmimimi");
      Serial.print(z);
      pause = false;
    }
    if(z == 2 && pause == true)
    {
      z = 0;
      Serial.print(z);
      chordIndex = 0;
      pause = false;
    }
  }
  //for the first song 
  if(z == 0)
    {  
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(chords[chordIndex]);
      lcd.setCursor(15, 0);
      lcd.print("1");
      lcd.setCursor(0, 1);
      lcd.print("BPM: ");
      lcd.print(bpm);

    }
  //for the second song 
  if(z == 1)
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(chords1[chordIndex]);
      lcd.setCursor(15, 0);
      lcd.print("2");
      lcd.setCursor(0, 1);
      lcd.print("BPM: ");
      lcd.print(bpm);
    }
  //for the third one which is random
  if(z == 2)
    {
      int randomIndex = random(sizeof(strings)/sizeof(*strings));
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(strings[randomIndex]);
      lcd.setCursor(15, 0);
      lcd.print("3");
      lcd.setCursor(0, 1);
      lcd.print("BPM: ");
      lcd.print(bpm);
    }
  //this is for the tik sound 4/4
  for (int i = 0; i < 4; i++) {
    if(i==0)
     {
      buzzerPitch = 1000;
     }
    else if(i>0)
    {
      buzzerPitch = 350;
    }
       analogWrite(BUZZER_PIN, buzzerVolume); // Set buzzer volume
       tone(BUZZER_PIN, buzzerPitch, 10);     // Play tone for 10 ms
       delay(delayTime);                      // Wait for specified delay time
       noTone(BUZZER_PIN);                    // Turn off buzzer
       delay(delayTime);                      // Wait for specified delay time
    
  }

  // Increment chord index and loop back to 0 if end of array is reached
  chordIndex++;
  if (chordIndex >= 4) {
    chordIndex = 0;
  }
}
