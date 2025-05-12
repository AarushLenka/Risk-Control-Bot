#define BLYNK_TEMPLATE_ID "TMPL3VD1qQ8gh"
#define BLYNK_TEMPLATE_NAME "riskmonitor"
#define BLYNK_AUTH_TOKEN "d3y2KulVL1Yw-16y7d665-FrvFP8YQmb"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

#define DHTPIN A0     // Pin connected to DHT sensor
#define DHTTYPE DHT11 // Change to DHT22 if using that

DHT dht(DHTPIN, DHTTYPE);

char auth[] = "d3y2KulVL1Yw-16y7d665-FrvFP8YQmb";
char ssid[] = "Galaxy A52s 5GF184";
char pass[] = "Recharge karwalo";

const int motorPin1 = D1; // IN1
const int motorPin2 = D2; // IN2
const int motorPin3 = D3; // IN3
const int motorPin4 = D4; // IN4
const int flamePin = D0;  // Flame sensor pin
//const int gasPin = A0;    // Gas sensor pin
const int buzzerPin = D6; // Buzzer pin

BlynkTimer timer;

void readSensors() {
  // Flame sensor
  int flame_detection = digitalRead(flamePin);
  Blynk.virtualWrite(V0, flame_detection);
  if (flame_detection == 1) {
    Serial.println("Warning! Flame is detected!");
  } else {
    Serial.println("No fire detected.");
  }

  /*// Gas sensor
  int gas_levels = analogRead(gasPin);
  Blynk.virtualWrite(V3, gas_levels);
  Serial.print("Gas levels: ");
  Serial.println(gas_levels);
  */

  // Buzzer control
  float gas_threshold = 100;
  if ( flame_detection == 0) {
    digitalWrite(buzzerPin, HIGH);
  } else {
    digitalWrite(buzzerPin, LOW);
  }

  // DHT sensor
  float temp_levels = dht.readTemperature();
  //float hum_levels = dht.readHumidity();
 // if (isnan(temp_levels) /|| isnan(hum_levels)/) {
 //   Serial.println(temp_levels);
 // } else {
  Blynk.virtualWrite(V4, temp_levels);
    //Blynk.virtualWrite(V5, hum_levels);
  Serial.println("Temperature: ");
  Serial.println(temp_levels);
    //Serial.print(" °C, Humidity: ");
    //Serial.print(hum_levels);
    //Serial.println(" %");
 // }
}

void setup() {
  // Debug console
  Serial.begin(9600);

  // Connect to Wi-Fi
  Blynk.begin(auth, ssid, pass);

  // Initialize sensor pins
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  pinMode(flamePin, INPUT);
  //pinMode(gasPin, INPUT);
  pinMode(buzzerPin, OUTPUT);

  // Initialize DHT sensor
  dht.begin();

  // Setup a function to be called every second
  timer.setInterval(1000L, readSensors);
}

void loop() {
  Blynk.run();
  timer.run();
}

BLYNK_WRITE(V1) {
  int value = param.asInt();
  if (value == 1) {
    // Forward
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, HIGH);
    digitalWrite(motorPin3, HIGH);
    digitalWrite(motorPin4, LOW);
  } else {
    // Stop
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, LOW);
    digitalWrite(motorPin3, LOW);
    digitalWrite(motorPin4, LOW);
  }
}

BLYNK_WRITE(V2) {
  int value = param.asInt();
  if (value == 1) {
    // Reverse
    digitalWrite(motorPin1, HIGH);
    digitalWrite(motorPin2, LOW);
    digitalWrite(motorPin3, LOW);
    digitalWrite(motorPin4, HIGH);
  } else {
    // Stop
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, LOW);
    digitalWrite(motorPin3, LOW);
    digitalWrite(motorPin4, LOW);
  }
}
