n = 1 : 30;

x = 2 * sin(pi * n/6 + pi/3);
stem(n, x);
xlabel('time sequence');
ylabel('amptitude');
title('sin funtion sequence: 2*sin(pi*n/6+pi/3)');