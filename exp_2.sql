-- based on exp_1

CREATE TABLE exp_1_default (
    id UInt32
) ENGINE = MergeTree()
ORDER BY id;

CREATE TABLE exp_1_secret (
    id UInt32
) ENGINE = MergeTree()
ORDER BY id
SETTINGS storage_policy = 'secret';

