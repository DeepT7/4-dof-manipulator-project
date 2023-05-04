clc
clear all
close all

%%
syms q d a al
T = [cos(q) -sin(q)*cos(al) sin(q)*sin(al) a*cos(q);sin(q) cos(q)*cos(al) -cos(q)*sin(al) a*sin(q);0 sin(al) cos(al) d;0 0 0 1];
syms q0 q1 q2 q3 l1 l2 l3 l4

%% 01^00
q = q0;
d = l1;
a = 0;
al = sym(pi/2);
T01 = [cos(q) -sin(q)*cos(al) sin(q)*sin(al) a*cos(q);sin(q) cos(q)*cos(al) -cos(q)*sin(al) a*sin(q);0 sin(al) cos(al) d;0 0 0 1];

%% 02^01
q = q1;
d = 0;
a = l2;
al = 0;
T12 = [cos(q) -sin(q)*cos(al) sin(q)*sin(al) a*cos(q);sin(q) cos(q)*cos(al) -cos(q)*sin(al) a*sin(q);0 sin(al) cos(al) d;0 0 0 1];

%% 03^02
q = q2;
d = 0;
a = 13;
al = 0;
T23 = [cos(q) -sin(q)*cos(al) sin(q)*sin(al) a*cos(q);sin(q) cos(q)*cos(al) -cos(q)*sin(al) a*sin(q);0 sin(al) cos(al) d;0 0 0 1];

%% 04^03
q = q3;
d = 0;
a = 14;
al = 0;
T34 = [cos(q) -sin(q)*cos(al) sin(q)*sin(al) a*cos(q);sin(q) cos(q)*cos(al) -cos(q)*sin(al) a*sin(q);0 sin(al) cos(al) d;0 0 0 1];

%% 01^00
D01 = T01;

%% 02^00
D02 = T01*T12;

%% 03^00
D03 = T01*T12*T23;

%% 04^00
D04 = T01*T12*T23*T34;

%% Vi tri diem cuoi <FW> Động học thuận
xE = D04(1,4);
yE = D04(2,4);
ze = D04(3,4);

%% ma tran FW
syms r11 r12 r13 r21 r22 r23 r31 r32 r33 Px Py Pz
FW = [r11 r12 r13 Px;r21 r22 r23 Pz;r31 r32 r33 Pz;0 0 0 1];

%% ma tran nghich dao cua T01
T10 = inv(T01);

%% 
FW_T10 = T10*FW; %% tich cua T10 va FW
T14 = T10*T01*T12*T23*T34;

x_FW_T10 = FW_T10(1,4); %%n1
y_FW_T10 = FW_T10(2,4); %%n2
z_FW_T10 = FW_T10(3,4); %%n3

x_T14 = T14(1,4); %%m1
y_T14 = T14(2,4); %%m2
z_T14 = T14(3,4); %%m3

%% xét n1=m1; n2=m2; n3=m3; tu chon tong q1+q2+q3
Q = 5*pi/6;
l0 = 7.4;
l1 = 9.35;
l2 = 12.25;
l3 = 12.5;
Px = 12;
Py = -14;
Pz = 6;
PT_3 = z_FW_T10 - z_T14; %% tìm đc q0
q0 = atan2(Py,Px)
q0 = q0*180/pi

a = sqrt(Px^2+Py^2);
b = l3 - l0 + Pz; %% tong binh a va b tim dc q2
q1 = atan2(b,a) + acos((-l2^2+l1^2+a^2+b^2)/(2*sqrt(a^2+b^2)*l1))
q1 = q1*180/pi

q2 = acos((-a^2+-b^2+l1^2+l2^2)/(2*l1*l2))-pi
q2 = q2*180/pi

q3 = acos((-l1^2+l2^2+a^2+b^2)/(2*sqrt(a^2+b^2)*l2))-atan2(b,a)-pi/2
q3 = q3*180/pi


