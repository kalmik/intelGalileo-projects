xb5=[-1.000000:0.140000:1.000000];
yb5=[-1.000000:0.140000:1.000000];
zb5=[-0.812500 -0.810916 -0.810916 -0.810916 -0.777625 -0.622568 -0.498092 -0.498647 -0.498293 -0.497508 -0.498378 -0.418909 -0.139637 0.000000 0.000000 ;-0.810916 -0.810916 -0.810916 -0.810916 -0.777625 -0.622568 -0.498092 -0.498647 -0.498293 -0.497508 -0.498378 -0.418909 -0.139637 0.000000 0.000000 ;-0.810916 -0.810916 -0.787984 -0.787984 -0.729200 -0.590217 -0.498378 -0.498701 -0.498525 -0.468793 -0.441203 -0.289714 -0.064381 0.059844 0.059844 ;-0.810916 -0.810916 -0.787984 -0.703147 -0.597854 -0.568976 -0.498701 -0.498701 -0.498701 -0.475865 -0.272190 -0.060487 0.127991 0.339117 0.339117 ;-0.777625 -0.777625 -0.729200 -0.597854 -0.445393 -0.427247 -0.423621 -0.430544 -0.430544 -0.322296 -0.038366 0.172027 0.386285 0.498525 0.498525 ;-0.622568 -0.622568 -0.590217 -0.568976 -0.427247 -0.299221 -0.165947 -0.165947 -0.165947 -0.117199 0.099740 0.390200 0.406427 0.497839 0.497839 ;-0.498092 -0.498092 -0.498378 -0.498701 -0.423621 -0.165947 0.000000 0.000000 0.000000 0.038270 0.373783 0.498455 0.498647 0.498092 0.498092 ;-0.498647 -0.498647 -0.498701 -0.498701 -0.430544 -0.165947 0.000000 0.000000 0.000000 0.038270 0.373783 0.498701 0.498701 0.498647 0.498647 ;-0.498293 -0.498293 -0.498525 -0.498701 -0.430544 -0.165947 0.000000 0.000000 0.000000 0.038270 0.373783 0.498589 0.498701 0.498293 0.498293 ;-0.497508 -0.497508 -0.468793 -0.475865 -0.322296 -0.117199 0.038270 0.038270 0.038270 0.099567 0.367163 0.520877 0.517950 0.528668 0.528668 ;-0.498378 -0.498378 -0.441203 -0.272190 -0.038366 0.099740 0.373783 0.373783 0.373783 0.367163 0.415764 0.555585 0.667744 0.748052 0.748052 ;-0.418909 -0.418909 -0.289714 -0.060487 0.172027 0.390200 0.498455 0.498701 0.498589 0.520877 0.555585 0.634019 0.758814 0.810916 0.810916 ;-0.139637 -0.139637 -0.064381 0.127991 0.386285 0.406427 0.498647 0.498701 0.498701 0.517950 0.667744 0.758814 0.767450 0.810916 0.810916 ;0.000000 0.000000 0.059844 0.339117 0.498525 0.497839 0.498092 0.498647 0.498293 0.528668 0.748052 0.810916 0.810916 0.810916 0.810916 ;0.000000 0.000000 0.059844 0.339117 0.498525 0.497839 0.498092 0.498647 0.498293 0.528668 0.748052 0.810916 0.810916 0.810916 0.810916 ;];
x5 = (xb5.^0)'*xb5;
y5 = yb5'*(yb5.^0);
surf(x5,y5,zb5);
title('FUZZY SURFACE 5MFS');