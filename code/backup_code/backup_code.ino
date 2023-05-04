#include <Servo.h>
#include <math.h>

#define Echo 7 //"Echo" labeled pin of HC-SR04 ultrasoniic module
#define Trigger 8 // "Trig" labeled pin of HC-SR04 ultrasonic module 
#define EF 4 // pin controlling electrical magnet of the end effector


long Time; // the time variable for ultrasonic sensor
float Distance; // the distance variable for ultrasonic sensor


Servo servo1; // servo of the 1st joint
Servo servo2; // servo of the 2nd joint
Servo servo3; // servo of the 2rd joint
Servo servo4; // servo of the 4th joint
Servo gripper; // servo dieu khien nam cham dien

float min_PWM; // default arduino 544
float max_PWM; // dafault arduino 2400

float Pi = 3.141592653589793;
float Yoffset;
float D;
float d;
float R;
float L0 = 7.4; // (cm) the length of L0
float L1 = 9.35; 
float L2 = 12.25;
float L3 = 12.5;

float px; // x axis coordinate of the EF
float py; // y axis coordinate of the EF
float pz; // Z axis coordiante of the EF


float a;
float b;
float Theta_0;
float Theta_1;
float Theta_2;
float Theta_3;
float t0;
float t1;
float t2;
float t3;
float m0, m1, m2, m3;

void Robot_IK()
{
  if (px != 0 && pz >= L1)
  {
    a = sqrt(pow(px,2) + pow(py,2));
    b = L3 - L0 + pz;
    Theta_0 = atan(py/px)*(180.00/Pi);
    Theta_1 = (atan(b/a) + acos((-pow(L2,2)+pow(L1,2)+pow(a,2)+pow(b,2))/(2*sqrt(pow(a,2)+pow(b,2))*L1)))*(180.00/Pi);
    Theta_2 = (acos((-pow(a,2)-pow(b,2)+pow(L1,2)+pow(L2,2))/(2*L1*L2))-Pi)*(180.00/Pi);
    Theta_3 = (acos((-pow(L1,2)+pow(L2,2)+pow(a,2)+pow(b,2))/(2*sqrt(pow(a,2)+pow(b,2))*L2))+atan(a/b)-Pi)*(180.00/Pi);
  }
  else if (px != 0 &&  pz <= L1)
  {
    a = sqrt(pow(px,2)+ pow(py,2));
    b = L3 - L0 + pz;
    Theta_0 = atan(py/px) * (180.00/Pi);
    Theta_1 = (atan(b/a) + acos((-pow(L2,2)+pow(L1,2) + pow(a,2)+pow(b,2))/(2*sqrt(pow(a,2)+pow(b,2))*L1)))*(180.00/Pi);
    Theta_2 = (acos((-pow(a,2)-pow(b,2)+pow(L1,2)+pow(L2,2))/(2*L1*L2))-Pi)*(180.00/Pi);
    Theta_3 = (acos((-pow(L1,2)+pow(L2,2)+pow(a,2)+pow(b,2))/(2*sqrt(pow(a,2)+pow(b,2))*L2))-atan(b/a)-Pi/2)*(180.00/Pi);
  }
  else if (px == 0 && pz >= L1)
  {
    a = sqrt(pow(px,2) + pow(py,2));
    b = L3 - L0 + pz;
    if(py >= 0)
    {
      Theta_0 = 90;
    }
    else if(py < 0)
    {
      Theta_0 = -90;
    }
    Theta_1 = (atan(b/a) + acos((-pow(L2,2)+pow(L1,2)+pow(a,2)+pow(b,2))/(2*sqrt(pow(a,2)+pow(b,2))*L1)))*(180.00/Pi);
    Theta_2 = (acos((-pow(a,2)-pow(b,2)+pow(L1,2)+pow(L2,2))/(2*L1*L2))-Pi)*(180.00/Pi);
    Theta_3 = (acos((-pow(L1,2)+pow(L2,2)+pow(a,2)+pow(b,2))/(2*sqrt(pow(a,2)+pow(b,2))*L2))+atan(a/b)-Pi)*(180.00/Pi);
  }
  else if (px == 0 && pz <= L1)
  {
    a = sqrt(pow(px,2)+ pow(py,2));
    b = L3 - L0 + pz;
    if(py >= 0)
    {
      Theta_0 = 90;
    }
    else if(py < 0)
    {
      Theta_0 = -90;
    }
    Theta_1 = (atan(b/a) + acos((-pow(L2,2)+pow(L1,2) + pow(a,2)+pow(b,2))/(2*sqrt(pow(a,2)+pow(b,2))*L1)))*(180.00/Pi);
    Theta_2 = (acos((-pow(a,2)-pow(b,2)+pow(L1,2)+pow(L2,2))/(2*L1*L2))-Pi)*(180.00/Pi);
    Theta_3 = (acos((-pow(L1,2)+pow(L2,2)+pow(a,2)+pow(b,2))/(2*sqrt(pow(a,2)+pow(b,2))*L2))-atan(b/a)-Pi/2)*(180.00/Pi);
  }
}

void setup()
{
  Serial.begin(9600);
  pinMode(Trigger, OUTPUT);
  pinMode(Echo, INPUT);
  servo1.attach(9);
  servo2.attach(10);
  servo3.attach(11);
  servo4.attach(6);
  gripper.attach(5);
  servo1.write(90);
  servo2.write(90);
  servo3.write(0);
  servo4.write(0);
  gripper.write(0);
}
int i =0;

void loop()
{
  digitalWrite(Trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trigger, LOW);
  Time= pulseIn(Echo, HIGH);
  Distance = Time*0.034/2; 
  Serial.print("Distance = ");
  Serial.println(Distance);

if(Distance > 7.00)
//if(i != 0)
  {
    // Neu chua dat vat lai gan cam bien sieu am
    
    // cho canh tay robot o trang thai nghi
    servo4.write(0);
    servo3.write(0);
    servo2.write(90);
    servo1.write(90);
    delay(1000);
  }
  else if (Distance <= 7.00 )
  //else if(i == 0)
  {
    px = 12; 
    py = -14;
    pz = 5.5;
    Robot_IK();
    t0 = servo1.read();
    t1 = servo2.read();
    t2 = servo3.read();
    t3 = servo4.read();
    m0 = (Theta_0+90) - t0;
    m1 = Theta_1 - t1;
    m2 = -Theta_2 - t2;
    m3 = -Theta_3 - t3;
    // Neu goc cua khop mot can phai tang len
    if(m0  > 0)
    {
      for(; t0 <= (Theta_0+90); t0 += m0/100.0, t1 += m1/100.0, t2 += m2/100.0, t3+=m3/100.0)
      {
        servo4.write(t3);
        servo3.write(t2);
        servo2.write(t1);
        servo1.write(t0);
        delay(25);
      }
    }
    else if(m0 <= 0)
    {
      for(; t0 >= (Theta_0+90); t0 += m0/100.0, t1 += m1/100.0, t2 += m2/100.0, t3+=m3/100.0)
      {
        servo4.write(t3);
        servo3.write(t2);
        servo2.write(t1);
        servo1.write(t0);
        delay(25);
      }
    }
  delay(300);
  // Doan nay bat nam cham dien len
  gripper.write(40);
  delay(1500);
  
    px = 14; 
    py = 4;
    pz = 10;
    Robot_IK();
    t0 = servo1.read();
    t1 = servo2.read();
    t2 = servo3.read();
    t3 = servo4.read();
    m0 = (Theta_0+90) - t0;
    m1 = Theta_1 - t1;
    m2 = -Theta_2 - t2;
    m3 = -Theta_3 - t3;
    // Neu goc cua khop mot can phai tang len
    if(m0  > 0)
    {
      for(; t0 <= (Theta_0+90); t0 += m0/100.0, t1 += m1/100.0, t2 += m2/100.0, t3+=m3/100.0)
      {
        servo4.write(t3);
        servo3.write(t2);
        servo2.write(t1);
        servo1.write(t0);
        delay(25);
      }
    }
    else if(m0 <= 0)
    {
      for(; t0 >= (Theta_0+90); t0 += m0/100.0, t1 += m1/100.0, t2 += m2/100.0, t3+=m3/100.0)
      {
        servo4.write(t3);
        servo3.write(t2);
        servo2.write(t1);
        servo1.write(t0);
        delay(25);
      }
    }
    px = 14; 
    py = 12;
    pz = 4;
    Robot_IK();
    t0 = servo1.read();
    t1 = servo2.read();
    t2 = servo3.read();
    t3 = servo4.read();
    m0 = (Theta_0+90) - t0;
    m1 = Theta_1 - t1;
    m2 = -Theta_2 - t2;
    m3 = -Theta_3 - t3;
    // Neu goc cua khop mot can phai tang len
    if(m0  > 0)
    {
      for(; t0 <= (Theta_0+90); t0 += m0/100.0, t1 += m1/100.0, t2 += m2/100.0, t3+=m3/100.0)
      {
        servo4.write(t3);
        servo3.write(t2);
        servo2.write(t1+10);
        servo1.write(t0);
        delay(25);
      }
    }
    else if(m0 <= 0)
    {
      for(; t0 >= (Theta_0+90); t0 += m0/100.0, t1 += m1/100.0, t2 += m2/100.0, t3+=m3/100.0)
      {
        servo4.write(t3);
        servo3.write(t2);
        servo2.write(t1+10);
        servo1.write(t0);
        delay(25);
      }
    }
    delay(100);
    // Doan nay tat nam cham dien de tha vat
    gripper.write(0);
    delay(1500);
    // quay ve trang thai nghi
    t0 = servo1.read();
    t1 = servo2.read();
    t2 = servo3.read();
    t3 = servo4.read();
    m0 = 90 - t0;
    m1 = 90 - t1;
    m2 =0 - t2;
    m3 =0 - t3;
    // Neu goc cua khop mot can phai tang len
    if(m0  > 0)
    {
      for(; t0 <= 90.0; t0 += m0/100.0, t1 += m1/100.0, t2 += m2/100.0, t3+=m3/100.0)
      {
        servo4.write(t3);
        servo3.write(t2);
        servo2.write(t1+10);
        servo1.write(t0);
        delay(25);
      }
    }
    else if(m0 <= 0)
    {
      for(; t0 >= 90.0; t0 += m0/100.0, t1 += m1/100.0, t2 += m2/100.0, t3+=m3/100.0)
      {
        servo4.write(t3);
        servo3.write(t2);
        servo2.write(t1+10);
        servo1.write(t0);
        delay(25);
      }
    }
    delay(100);
    i = 1;
  }
}





