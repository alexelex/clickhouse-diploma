/*
Acoording to CH architecture :

first insert and second insert are to disk_1
third are to disk_2
fourth are to disk_3

Let's check it and that inserts to encrypted disk works.
*/

INSERT INTO exp_default SELECT * FROM numbers(100);
INSERT INTO exp_default SELECT * FROM numbers(100);

INSERT INTO exp_secret SELECT * FROM numbers(100);
INSERT INTO exp_secret SELECT * FROM numbers(100);

SELECT * FROM system.parts　WHERE (table = 'exp_default' and active = 1)
SELECT * FROM system.parts　WHERE (table = 'exp_secret' and active = 1)
