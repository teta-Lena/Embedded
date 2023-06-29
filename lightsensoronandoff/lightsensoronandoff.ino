int sensorPin = A0; // light sensor is connected to analog pin 0
int ledPin = 13;    // LED is connected to digital pin 13
int sensorValue = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue);
  
  if (sensorValue>500) {
    Serial.println("here");
    delay(200);
    digitalWrite(ledPin, HIGH);
  } else {
    delay(200);
    digitalWrite(ledPin, LOW);
  }

//digitalWrite(ledPin,HIGH);
//delay(2000);
//digitalWrite(ledPin,LOW);
//delay(2000);
}
