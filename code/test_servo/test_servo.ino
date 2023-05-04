#include <Servo.h>

Servo myservo; // create servo object to control a servo 
Servo s1;
Servo s2;
Servo s3;
int pos = 0;

void setup() {
  Serial.begin(9600);
  myservo.attach(9);
  s1.attach(10);
  s2.attach(11);
  s3.attach(6);
  myservo.write(90);
  s1.write(90);
  s2.write(0);
  s3.write(0);
}



int i = 0;
void loop() 
{
    // s3.write(90+90);
    // s2.write(90+45);
    // s1.write(60);
    //myservo.write(90+Theta)
    delay(100);
}
