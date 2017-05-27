s(1).name = 'ellen';
s(1).age = 13;
s(1).grade = 'a+';
disp(s);

s(2).name = 'sam';
s(2).age = 11;
s(2).grade = 's+';
disp(s);

s(3) = struct ('name', 'jerry', ...
               'age', 14, ...
               'grade', 'b+');
disp(s);

disp(s(3));

ages = [s.age]

names = char(s.name)

names = {s.name}