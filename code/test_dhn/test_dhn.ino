#include <Servo.h>

float Pi = 3.141592653589793;
float Yoffset;
float D;
float d;
float R;
float L0 = 7.4; // (cm) the length of L0
float L1 = 9.35; 
float L2 = 12.15;
float L3 = 12.5;
float L = L0+L1+L2+L3;

float px; // x axis coordinate of the EF
float py; // y axis coordinate of the EF
float pz; // Z axis coordiante of the EF

Servo myservo; // create servo object to control a servo 
Servo s1;
Servo s2;
Servo s3;

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
  delay(3000);
  if(i == 0)
  {
    px = 12; 
    py = -14;
    pz = 4;
    Robot_IK();
    t0 = myservo.read();
    t1 = s1.read();
    t2 = s2.read();
    t3 = s3.read();
    m0 = (Theta_0+90) - t0;
    m1 = Theta_1 - t1;
    m2 = -Theta_2 - t2;
    m3 = -Theta_3 - t3;
    // Neu goc cua khop mot can phai tang len
    if(m0  > 0)
    {
      for(; t0 <= (Theta_0+90); t0 += m0/100.0, t1 += m1/100.0, t2 += m2/100.0, t3+=m3/100.0)
      {
        s3.write(t3);
        s2.write(t2);
        s1.write(t1);
        myservo.write(t0);
        delay(25);
      }
    }
    else if(m0 <= 0)
    {
      for(; t0 >= (Theta_0+90); t0 += m0/100.0, t1 += m1/100.0, t2 += m2/100.0, t3+=m3/100.0)
      {
        s3.write(t3);
        s2.write(t2);
        s1.write(t1);
        myservo.write(t0);
        delay(25);
      }
    }
    px = 14; 
    py = -6;
    pz = 8;
    Robot_IK();
    t0 = myservo.read();
    t1 = s1.read();
    t2 = s2.read();
    t3 = s3.read();
    m0 = (Theta_0+90) - t0;
    m1 = Theta_1 - t1;
    m2 = -Theta_2 - t2;
    m3 = -Theta_3 - t3;
    // Neu goc cua khop mot can phai tang len
    if(m0  > 0)
    {
      for(; t0 <= (Theta_0+90); t0 += m0/100.0, t1 += m1/100.0, t2 += m2/100.0, t3+=m3/100.0)
      {
        s3.write(t3);
        s2.write(t2);
        s1.write(t1);
        myservo.write(t0);
        delay(25);
      }
    }
    else if(m0 <= 0)
    {
      for(; t0 >= (Theta_0+90); t0 += m0/100.0, t1 += m1/100.0, t2 += m2/100.0, t3+=m3/100.0)
      {
        s3.write(t3);
        s2.write(t2);
        s1.write(t1);
        myservo.write(t0);
        delay(25);
      }
    }
    px = 14; 
    py = 4;
    pz = 10;
    Robot_IK();
    t0 = myservo.read();
    t1 = s1.read();
    t2 = s2.read();
    t3 = s3.read();
    m0 = (Theta_0+90) - t0;
    m1 = Theta_1 - t1;
    m2 = -Theta_2 - t2;
    m3 = -Theta_3 - t3;
    // Neu goc cua khop mot can phai tang len
    if(m0  > 0)
    {
      for(; t0 <= (Theta_0+90); t0 += m0/100.0, t1 += m1/100.0, t2 += m2/100.0, t3+=m3/100.0)
      {
        s3.write(t3);
        s2.write(t2);
        s1.write(t1);
        myservo.write(t0);
        delay(25);
      }
    }
    else if(m0 <= 0)
    {
      for(; t0 >= (Theta_0+90); t0 += m0/100.0, t1 += m1/100.0, t2 += m2/100.0, t3+=m3/100.0)
      {
        s3.write(t3);
        s2.write(t2);
        s1.write(t1);
        myservo.write(t0);
        delay(25);
      }
    }
    px = 14; 
    py = 12;
    pz = 5;
    Robot_IK();
    t0 = myservo.read();
    t1 = s1.read();
    t2 = s2.read();
    t3 = s3.read();
    Serial.println(Theta_0);
    Serial.println(Theta_1);
    Serial.println(Theta_2);
    Serial.println(Theta_3);

    m0 = (Theta_0+90) - t0;
    m1 = Theta_1 - t1;
    m2 = -Theta_2 - t2;
    m3 = -Theta_3 - t3;
    // Neu goc cua khop mot can phai tang len
    if(m0  > 0)
    {
      for(; t0 <= (Theta_0+90); t0 += m0/100.0, t1 += m1/100.0, t2 += m2/100.0, t3+=m3/100.0)
      {
        s3.write(t3);
        s2.write(t2);
        s1.write(t1+10);
        myservo.write(t0);
        delay(25);
      }
    }
    else if(m0 <= 0)
    {
      for(; t0 >= (Theta_0+90); t0 += m0/100.0, t1 += m1/100.0, t2 += m2/100.0, t3+=m3/100.0)
      {
        s3.write(t3);
        s2.write(t2);
        s1.write(t1+10);
        myservo.write(t0);
        delay(25);
      }
    }
    i = 1;
  }
}
