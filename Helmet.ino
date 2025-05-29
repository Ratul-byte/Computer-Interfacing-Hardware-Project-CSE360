#include <Wire.h>
#include <MPU6050.h>


#define MQ3_PIN A0            // MQ3 Alcohol Sensor 
#define CRASH_LED_PIN 7       // Crash detection LED
#define BUZZER_PIN 9          // Alcohol detection buzzer
#define ALCOHOL_LED_PIN 8     // Alcohol detection LED
#define IR_SENSOR_PIN 2       // IR sensor for anti-theft
#define HELMET_LED_PIN 10      // Anti-theft LED
#define SOS_BUTTON_PIN 4      // SOS push button
#define TRIG_PIN 11
#define ECHO_PIN 12            // HC-SR04 Echo Pin
#define DISTANCE_THRESHOLD 20   // Distance in cm to trigger alert
#define ULTRASONIC_BUZZER_PIN 13
#define ALCOHOL_THRESHOLD 300 // Threshold for MQ3 sensor
#define TOUCH_SENSOR_PIN 6
#define KILL_SWITCH_PIN 5



MPU6050 mpu;
bool crashReported = false;
bool theftReported = false;
bool sosSent = false;
bool helmetPreviouslyWorn = false;  // Declare globally at the top of your code

void setup() {
  Serial.begin(9600);  // Shared with HC-06

  Wire.begin();
  mpu.initialize();
  if (mpu.testConnection()) {
    Serial.println("MPU6050 connected successfully.");
  } else {
    Serial.println("MPU6050 connection failed!");
    while (1); // Halt if MPU6050 not found
  }

  pinMode(MQ3_PIN, INPUT);
  pinMode(CRASH_LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(ALCOHOL_LED_PIN, OUTPUT);
  pinMode(IR_SENSOR_PIN, INPUT);
  pinMode(HELMET_LED_PIN, OUTPUT);
  pinMode(SOS_BUTTON_PIN, INPUT_PULLUP);  // Use internal pull-up resistor
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(ULTRASONIC_BUZZER_PIN, OUTPUT);
  pinMode(TOUCH_SENSOR_PIN, INPUT);
  pinMode(KILL_SWITCH_PIN, INPUT_PULLUP);

}

void loop() {
  checkAlcohol();

  if (digitalRead(KILL_SWITCH_PIN) == LOW) {  // Switch ON (active LOW)
    digitalWrite(BUZZER_PIN, LOW);
    detectTiltCrash();
  } else {
    digitalWrite(BUZZER_PIN, HIGH);
    digitalWrite(CRASH_LED_PIN, LOW);  // Turn off crash LED
    crashReported = false;
  }

  //detectTiltCrash();
  checkTheft();
  checkSOS();
  checkUltrasonic();
  checkHelmet();   
  delay(200);
}


void checkAlcohol() {
  int alcoholValue = analogRead(MQ3_PIN);

  if (alcoholValue > ALCOHOL_THRESHOLD) {
    digitalWrite(BUZZER_PIN, HIGH);
    digitalWrite(ALCOHOL_LED_PIN, HIGH);
    Serial.println("You are\n");
    Serial.println("Alcoholic\n");
    Serial.println(alcoholValue);
    Serial.println("\n");
  } else {
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(ALCOHOL_LED_PIN, LOW);
  }
}

void detectTiltCrash() {
  int16_t ax, ay, az;
  mpu.getAcceleration(&ax, &ay, &az);

  float x = ax / 16384.0;
  float y = ay / 16384.0;
  float z = az / 16384.0;

  float pitch = atan2(x, sqrt(y * y + z * z)) * 180.0 / PI;
  float roll  = atan2(y, sqrt(x * x + z * z)) * 180.0 / PI;

  if (abs(pitch) > 45 || abs(roll) > 45) {
    digitalWrite(CRASH_LED_PIN, HIGH);
    if (!crashReported) {
      Serial.println("Crash Alert!");
      if(!helmetPreviouslyWorn){
        Serial.println("Helmet on\n");
      }
      else{
        Serial.println("Helmet off\n");
      }
      Serial.println(abs(pitch));
      Serial.println(abs(roll));
      Serial.println("\n");
      crashReported = true;
    }
  } else {
    digitalWrite(CRASH_LED_PIN, LOW);
    crashReported = false;
  }
}

void checkTheft() {
  int irValue = digitalRead(IR_SENSOR_PIN);
  if (irValue == LOW) {
    //digitalWrite(THEFT_LED_PIN, HIGH);
    if (!theftReported) {
      Serial.println("Theft Alert!\n");
      theftReported = true;
    }
  } else {
    //digitalWrite(THEFT_LED_PIN, LOW);
    theftReported = false;
  }
}

void checkSOS() {
  if (digitalRead(SOS_BUTTON_PIN) == LOW) {
    if (!sosSent) {
      Serial.println("HELP\n");
      sosSent = true;
    }
  } else {
    sosSent = false;
  }
}


void checkUltrasonic() {
  long duration;
  float distance;

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration * 0.034 / 2;

  if (distance > 0 && distance < DISTANCE_THRESHOLD) {
    digitalWrite(ULTRASONIC_BUZZER_PIN, HIGH);
    Serial.println("Object too close!\n");
    Serial.println("Distance: " + String(distance) + " cm\n");
  } else {
    digitalWrite(ULTRASONIC_BUZZER_PIN, LOW);
  }
}

void checkHelmet() {
  int helmetTouch = digitalRead(TOUCH_SENSOR_PIN);

  // Assuming active HIGH: sensor outputs HIGH when touched
  if (helmetTouch == LOW) {
    //digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(HELMET_LED_PIN, HIGH);

    if (!helmetPreviouslyWorn) {
      //Serial.println("Helmet Worn");
      helmetPreviouslyWorn = true;
    }

  } else {
    digitalWrite(HELMET_LED_PIN, LOW);
    //digitalWrite(BUZZER_PIN, HIGH);
    helmetPreviouslyWorn = false;
  }
}



