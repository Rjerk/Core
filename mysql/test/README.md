1. creata database example and table exam_info.

```
$ mysql -u root -p [passwd]

mysql> create database example;
mysql> show databases;
mysql> use example;
mysql> create table exam_info (
    -> exam_num char(20) NOT NULL,
    -> exam_name char(10) NOT NULL,
    -> exam_age int NOT NULL,
    -> exam_grade char(5) NOT NULL,
    -> exam_score int,
    -> primary key(exam_num));
mysql> show tables;
mysql> insert into exam_info values("U201018113", "sonlee", 23, "1001", 85);
mysql> select * from exam_info;

+------------+-----------+----------+------------+------------+
| exam_num   | exam_name | exam_age | exam_grade | exam_score |
+------------+-----------+----------+------------+------------+
| U201018113 | sonlee    |       23 | 1001       |         85 |
+------------+-----------+----------+------------+------------+

```

2. compile and run.

```
$ g++ -std=c++11 test.cpp -o test -lmysqlclient -L /usr/include/mysql -I /usr/include/mysql

$ ./test
connection suceessed.
U201018113 sonlee 23 1001 85
```
