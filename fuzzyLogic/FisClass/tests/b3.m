xb3=[-1.000000:0.140000:1.000000];
yb3=[-1.000000:0.140000:1.000000];
zb3=[-0.625000 -0.623782 -0.623782 -0.623782 -0.623782 -0.623782 -0.623782 -0.623782 -0.504271 -0.344055 -0.155870 0.000000 0.000000 0.000000 0.000000 ;-0.623782 -0.623782 -0.623782 -0.623782 -0.623782 -0.623782 -0.623782 -0.623782 -0.504271 -0.344055 -0.155870 0.000000 0.000000 0.000000 0.000000 ;-0.623782 -0.623782 -0.623782 -0.623782 -0.623782 -0.623782 -0.623782 -0.623782 -0.504271 -0.344055 -0.155870 0.000000 0.000000 0.000000 0.000000 ;-0.623782 -0.623782 -0.623782 -0.623782 -0.623782 -0.623782 -0.623782 -0.623782 -0.504271 -0.344055 -0.155870 0.000000 0.000000 0.000000 0.000000 ;-0.623782 -0.623782 -0.623782 -0.623782 -0.577580 -0.577580 -0.577580 -0.570368 -0.347237 -0.207957 -0.049410 0.095914 0.095914 0.095914 0.095914 ;-0.623782 -0.623782 -0.623782 -0.623782 -0.577580 -0.514115 -0.502609 -0.432811 -0.170203 -0.031808 0.103997 0.293443 0.293443 0.293443 0.293443 ;-0.623782 -0.623782 -0.623782 -0.623782 -0.577580 -0.502609 -0.407622 -0.274137 -0.039938 0.086688 0.235858 0.460978 0.460978 0.460978 0.460978 ;-0.623782 -0.623782 -0.623782 -0.623782 -0.570368 -0.432811 -0.274137 -0.089079 0.141731 0.315141 0.464796 0.604867 0.604867 0.604867 0.604867 ;-0.504271 -0.504271 -0.504271 -0.504271 -0.347237 -0.170203 -0.039938 0.141731 0.348310 0.458900 0.554753 0.623782 0.623782 0.623782 0.623782 ;-0.344055 -0.344055 -0.344055 -0.344055 -0.207957 -0.031808 0.086688 0.315141 0.458900 0.502184 0.554753 0.623782 0.623782 0.623782 0.623782 ;-0.155870 -0.155870 -0.155870 -0.155870 -0.049410 0.103997 0.235858 0.464796 0.554753 0.554753 0.554753 0.623782 0.623782 0.623782 0.623782 ;0.000000 0.000000 0.000000 0.000000 0.095914 0.293443 0.460978 0.604867 0.623782 0.623782 0.623782 0.623782 0.623782 0.623782 0.623782 ;0.000000 0.000000 0.000000 0.000000 0.095914 0.293443 0.460978 0.604867 0.623782 0.623782 0.623782 0.623782 0.623782 0.623782 0.623782 ;0.000000 0.000000 0.000000 0.000000 0.095914 0.293443 0.460978 0.604867 0.623782 0.623782 0.623782 0.623782 0.623782 0.623782 0.623782 ;0.000000 0.000000 0.000000 0.000000 0.095914 0.293443 0.460978 0.604867 0.623782 0.623782 0.623782 0.623782 0.623782 0.623782 0.623782 ;];
x3 = (xb3.^0)'*xb3;
y3 = yb3'*(yb3.^0);
surf(x3,y3,zb3);
title('FUZZY SURFACE 3MFS');