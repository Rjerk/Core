n = 50;
r = rand(n, 1);
plot(r);

m = mean(r); % get average

hold on;
plot([0, n], [m, m]); % plot [x1, x2] [y1, y2]
hold off;
title('Mean of Random Uniform Data');
