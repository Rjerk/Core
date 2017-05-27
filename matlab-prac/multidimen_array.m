p = perms(1 : 4);
a = magic(4);
m = zeros(4, 4, 24);

for k = 1 : 24
    m(:, :, k) = a(:, p(k, :));
    disp(m);
end

size(m)

disp('sum(m,1):');
sum(m, 1)

disp('sum(m,2):');
sum(m, 2)

disp('sum(m,3):');
sum(m, 3)