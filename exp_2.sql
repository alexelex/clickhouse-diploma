-- based on exp_1

CREATE TABLE exp_default (
    id UInt32
) ENGINE = MergeTree()
ORDER BY id;

CREATE TABLE exp_secret (
    id UInt32
) ENGINE = MergeTree()
ORDER BY id
SETTINGS storage_policy = 'secret';

