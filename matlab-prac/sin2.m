n = 0 : 40;
x1 = 1.5 * sin ( 2 * pi * 0.1 * n );
x2 = sin ( 0.9 * n );

subplot (1, 2, 1);
stem (n, x1);
xlabel ('time sequence n');
ylabel ('amptitude');
title ('sinusoidal sequence: x1 = 1.5*sin(2*pi*0.1*n)');

subplot (1, 2, 2);
stem (n, x2);
xlabel ('time sequence n');
ylabel ('amptitude');
title ('sinusoidal sequence: x2 = sin(0.9*n)');
