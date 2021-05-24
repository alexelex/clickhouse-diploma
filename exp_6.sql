/*

Bigger experiment

*/

CREATE TABLE big (
    id UInt32,
    value UInt32
) ENGINE = MergeTree()
ORDER BY id
SETTINGS storage_policy = 'secret';

INSERT INTO big SELECT number as x, x FROM numbers(10000000);
INSERT INTO big SELECT number as x, x FROM numbers(10000000);
INSERT INTO big SELECT number as x, x FROM numbers(10000000);
INSERT INTO big SELECT number as x, x FROM numbers(10000000);
INSERT INTO big SELECT number as x, x FROM numbers(10000000);
INSERT INTO big SELECT number as x, x FROM numbers(10000000);

SELECT * FROM big;

ALTER TABLE big MOVE PART 'all_1_1_0' TO DISK 'disk_3';

SELECT * FROM big;

OPTIMIZE TABLE big FINAL;

SELECT * FROM big;
