l0 = 7.4;
l1 = 9.35;
l2 = 12.15;
l3 = 12.5;
Px = 14;
Py = 12;
Pz = 5;

q0 = atan2(Py,Px)
q0 = q0*180/pi

a = sqrt(Px^2+Py^2);
b = l3 - l0 + Pz; %% tong binh a va b tim dc q2
q1 = atan2(b,a) + acos((-l2^2+l1^2+a^2+b^2)/(2*sqrt(a^2+b^2)*l1))
q1 = q1*180/pi

q2 = acos((-a^2-b^2+l1^2+l2^2)/(2*l1*l2))-pi
q2 = q2*180/pi

q3 = acos((-l1^2+l2^2+a^2+b^2)/(2*sqrt(a^2+b^2)*l2))+atan2(a,b)-pi
q3 = q3*180/pi


