#include <DHT.h>
#include <ESP32Servo.h>
#define PIN_SG90 22
#define PIN_SG9 21
DHT dht(26, DHT11);


Servo sg90;
Servo sg9;


void setup() {
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(27, OUTPUT);
  sg90.setPeriodHertz(50);
  sg90.attach(PIN_SG90, 500, 2400);
  sg9.setPeriodHertz(50);
  sg9.attach(PIN_SG9, 500, 2400);
  dht.begin();
  delay(2000);

  // Démarrez la communication série
  Serial.begin(115200);



  // Reste du code setup
}

void loop() {
  float temp = dht.readTemperature();
  float humidity = dht.readHumidity();
  if(humidity < 90) {
    for(int pos = 0; pos <= 180; pos += 1){
      sg9.write(pos);
      delay(10);
    }
    digitalWrite(27, HIGH);
    delay(1000);
  }
  if(temp > 25) {
    for(int pos = 0; pos <= 180; pos += 1){
      sg90.write(pos);
      delay(10);
    }
    digitalWrite(13, HIGH);
    digitalWrite(12, LOW);
    delay(1000);
  } else {
    digitalWrite(13, LOW);
    digitalWrite(12, HIGH);
    delay(1000);
  }
  Serial.print("Temp: ");
  Serial.print(temp);
  Serial.print(" C ");
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" % ");

  delay(2000);
  // Reste du code loop
}