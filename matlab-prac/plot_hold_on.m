x = 0 : pi/10 : 2*pi;
y = sin(x);
plot(x, y);
hold off;

y2 = cos(x);
plot(x, y2, ':');
legend('sin', 'cos');