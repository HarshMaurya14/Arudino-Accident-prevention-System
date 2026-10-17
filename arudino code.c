// Include required library
#include <LiquidCrystal.h>

// Pin Definitions
#define IR_SENSOR_PIN 3       // IR Sensor pin (Digital)
#define MQ2_SENSOR_PIN A0     // MQ-2 Smoke sensor pin (Analog)
#define BUZZER_PIN 10         // Buzzer pin
#define GREEN_LED_PIN 12      // Green LED pin
#define RED_LED_PIN 11        // Red LED pin

// LCD Pin Definitions (16x2 without I2C)
#define LCD_RS 4              // Register Select pin
#define LCD_EN 5              // Enable pin
#define LCD_D4 6              // Data pin 4
#define LCD_D5 7              // Data pin 5
#define LCD_D6 8              // Data pin 6
#define LCD_D7 9              // Data pin 7

// Threshold values
const int smokeThreshold = 300; // Adjust based on sensor calibration
const int drowsinessTime = 3000; // 3 seconds of eyes closed

// LCD Setup
LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

// Variables
unsigned long eyeClosedStartTime = 0;
bool eyesClosed = false;

void setup() {
  // Initialize LCD
  lcd.begin(16, 2);
  
  // Set pin modes
  pinMode(IR_SENSOR_PIN, INPUT);
  pinMode(MQ2_SENSOR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);

  // Initialize the system in default state
  digitalWrite(GREEN_LED_PIN, HIGH);  // Green LED ON at start
  digitalWrite(RED_LED_PIN, LOW);     // Red LED OFF
  digitalWrite(BUZZER_PIN, LOW);      // Buzzer OFF
  
  lcd.setCursor(0, 0);
  lcd.print("Safe Drive!");
  lcd.setCursor(0, 1);
  lcd.print("System Active");
  
  delay(2000);  // Display default message for 2 seconds
  lcd.clear();
}

void loop() {
  int irSensorValue = digitalRead(IR_SENSOR_PIN);



#include <LiquidCrystal.h>

// Pin Definitions
#define IR_SENSOR_PIN 3       // IR Sensor pin (Digital)
#define MQ2_SENSOR_PIN A0     // MQ-2 Smoke sensor pin (Analog)
#define BUZZER_PIN 10         // Buzzer pin
#define GREEN_LED_PIN 12      // Green LED pin
#define RED_LED_PIN 11        // Red LED pin

// LCD Pin Definitions (16x2 without I2C)
#define LCD_RS 4              // Register Select pin
#define LCD_EN 5              // Enable pin
#define LCD_D4 6              // Data pin 4
#define LCD_D5 7              // Data pin 5
#define LCD_D6 8              // Data pin 6
#define LCD_D7 9              // Data pin 7

// Threshold values
const int smokeThreshold = 300; // Adjust based on sensor calibration
const int drowsinessTime = 3000; // 3 seconds of eyes closed

// LCD Setup
LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

// Variables
unsigned long eyeClosedStartTime = 0;
bool eyesClosed = false;

void setup() {
  // Initialize LCD
  lcd.begin(16, 2);
  
  // Set pin modes
  pinMode(IR_SENSOR_PIN, INPUT);
  pinMode(MQ2_SENSOR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);

  // Initialize the system in default state
  digitalWrite(GREEN_LED_PIN, HIGH);  // Green LED ON at start
  digitalWrite(RED_LED_PIN, LOW);     // Red LED OFF
  digitalWrite(BUZZER_PIN, LOW);      // Buzzer OFF
  
  lcd.setCursor(0, 0);
  lcd.print("Safe Drive!");
  lcd.setCursor(0, 1);
  lcd.print("System Active");
  
  delay(2000);  // Display default message for 2 seconds
  lcd.clear();
}

void loop() {
  int irSensorValue = digitalRead(IR_SENSOR_PIN);
  int smokeSensorValue = analogRead(MQ2_SENSOR_PIN);

  // ---- DROWSINESS DETECTION ----
  if (irSensorValue == LOW) {  // Eyes closed
    if (!eyesClosed) {
      eyesClosed = true;
      eyeClosedStartTime = millis();  // Start timing
    }
    
    // Check if eyes are closed for a prolonged period (e.g., 3 seconds)
    if (eyesClosed && (millis() - eyeClosedStartTime >= drowsinessTime)) {
      // Trigger drowsiness alert
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Drowsy! Eyes Closed");
      lcd.setCursor(0, 1);
      lcd.print("Stop the Vehicle!");
      
      digitalWrite(BUZZER_PIN, HIGH);       // Buzzer ON
      digitalWrite(GREEN_LED_PIN, LOW);     // Green LED OFF
      digitalWrite(RED_LED_PIN, HIGH);      // Red LED ON
    }
  } else {  // Eyes open
    eyesClosed = false;
    eyeClosedStartTime = 0;
    
    // Reset system to normal state if eyes are open
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Safe Drive!");
    lcd.setCursor(0, 1);
    lcd.print("System Active");

    digitalWrite(BUZZER_PIN, LOW);       // Buzzer OFF
    digitalWrite(GREEN_LED_PIN, HIGH);   // Green LED ON
    digitalWrite(RED_LED_PIN, LOW);      // Red LED OFF
  }

  // ---- SMOKE DETECTION ----
  if (smokeSensorValue > smokeThreshold) {  // Smoke detected
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Smoke Detected!");
    lcd.setCursor(0, 1);
    lcd.print("Check Engine!");

    digitalWrite(BUZZER_PIN, HIGH);       // Buzzer ON
    digitalWrite(RED_LED_PIN, HIGH);      // Red LED ON
    digitalWrite(GREEN_LED_PIN, LOW);     // Green LED OFF
    
    delay(2000);  // Hold the message for 2 seconds
  }
  
  delay(100);  // Small delay for stability
}
