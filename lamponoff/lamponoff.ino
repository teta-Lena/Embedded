
const int lampPin = D7;


void setup() {
  // put your setup code here, to run once:
  pinMode(lampPin, OUTPUT);


}

void loop() {
  // put your main code here, to run repeatedly:

  digitalWrite(lampPin, HIGH);
   delay(1000);
  digitalWrite(lampPin, LOW);

}
