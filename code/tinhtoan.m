clc
clear all
close all

%%
syms q d a al
T = [cos(q) -sin(q)*cos(al) sin(q)*sin(al) a*cos(q);sin(q) cos(q)*cos(al) -cos(q)*sin(al) a*sin(q);0 sin(al) cos(al) d;0 0 0 1];
syms q0 q1 q2 q3 l1 l2 l3 l4

%% 01^00
q =0.7086;
d = 7.4;
a = 0;
al = pi/2;
T01 = [cos(q) -sin(q)*cos(al) sin(q)*sin(al) a*cos(q);sin(q) cos(q)*cos(al) -cos(q)*sin(al) a*sin(q);0 sin(al) cos(al) d;0 0 0 1];

%% 02^01
q =0.7419;
d = 0;
a = 9.35;
al = 0;
T12 = [cos(q) -sin(q)*cos(al) sin(q)*sin(al) a*cos(q);sin(q) cos(q)*cos(al) -cos(q)*sin(al) a*sin(q);0 sin(al) cos(al) d;0 0 0 1];

%% 03^02
q =-0.4253;
d = 0;
a = 12.15;
al = 0;
T23 = [cos(q) -sin(q)*cos(al) sin(q)*sin(al) a*cos(q);sin(q) cos(q)*cos(al) -cos(q)*sin(al) a*sin(q);0 sin(al) cos(al) d;0 0 0 1];

%% 04^03
q =-1.8874;
d = 0;
a = 12.5;
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

%% Vi tri diem cuoi <FW>
xE = D04(1,4)
yE = D04(2,4)
ze = D04(3,4)

