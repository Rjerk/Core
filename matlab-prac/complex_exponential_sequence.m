n = 1 : 30;

x = 2 * exp (j * 3 * n);

stem (n, x);
xlabel ('time sequence n');
tlabel ('amptitude');
title ('complex exponetial sequence: x = 2*exp(j*3*n)');