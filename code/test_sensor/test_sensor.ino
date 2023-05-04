#define Echo 7
#define Trigger 8


void setup() {
  Serial.begin(9600);
  pinMode(Echo, INPUT);
  pinMode(Trigger, OUTPUT);
}
long Time, Distance;
void loop() {
  digitalWrite(Trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trigger, LOW);
  Time = pulseIn(Echo, HIGH);
  Distance = Time*0.034/2;
  Serial.print("Distance = ");
  Serial.println(Distance);
  delay(25);
}
