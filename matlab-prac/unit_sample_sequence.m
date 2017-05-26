n = 0 : 10; %% …Ë÷√ 0 - 10

x1 = [ 1 zeros(1, 10)];
x2 = [ zeros(1, 5) 1 zeros(1, 5)];

subplot(1, 2, 1)
stem(n, x1);
xlabel('time sequence n');
ylabel('amplitude');
title('unit sample squence');

subplot(1, 2, 2);
stem(n, x2);
xlabel('time sequence n');
ylabel('amplitude');
title('unit sample squence (time-delay: 5)');


