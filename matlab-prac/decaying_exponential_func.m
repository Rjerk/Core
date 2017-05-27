t = [0 .3 .8 1.1 1.6 2.3]';
y = [.82 .72 .63 .60 .55 .50]';

% y(t) = c1 + c2 * e.^(-t)
% y = E * C
%                     c1
% y =  [ 1 e^(-t) ] [ c2 ]

E = [ones(size(t)) exp(-t)];

C = E \ y;

T = (0: 0.1 : 2.5)';
Y = [ones(size(T)) exp(-T)] * C;

plot(T, Y, '-', t, y, 'x')
