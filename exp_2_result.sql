-- create tables

click.ru-central1.internal :) CREATE TABLE exp_1_default (　    id UInt32　) ENGINE = MergeTree() ORDER BY id;

CREATE TABLE exp_1_default
(
    `id` UInt32
)
ENGINE = MergeTree
ORDER BY id

Query id: 154c7458-f5c1-4f0f-bbac-eae1031a2c23

Ok.

0 rows in set. Elapsed: 0.019 sec. 

click.ru-central1.internal :) CREATE TABLE exp_1_secret (
:-]     id UInt32
:-] ) ENGINE = MergeTree()
:-] ORDER BY id
:-] SETTINGS storage_policy = 'secret';

CREATE TABLE exp_1_secret
(
    `id` UInt32
)
ENGINE = MergeTree
ORDER BY id
SETTINGS storage_policy = 'secret'

Query id: d515075c-715c-45d1-b12d-664c9ca1a81f

Ok.

0 rows in set. Elapsed: 0.018 sec. 



-- read tables system data

SELECT name, data_paths, metadata_path, metadata_modification_time, storage_policy, total_rows, total_bytes FROM system.tables　WHERE name LIKE 'exp_1%'

click.ru-central1.internal :) SELECT name, data_paths, metadata_path, metadata_modification_time, storage_policy, total_rows, total_bytes FROM system.tables　WHERE name LIKE 'exp_1%'

SELECT
    name,
    data_paths,
    metadata_path,
    metadata_modification_time,
    storage_policy,
    total_rows,
    total_bytes
FROM system.tables
WHERE name LIKE 'exp_1%'

Query id: b3cb5429-4230-465e-b607-c4fd46f4db4d

┌─name──────────┬─data_paths────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┬─metadata_path──────────────────────────────────────────────────────────────────────────────────────────┬─metadata_modification_time─┬─storage_policy─┬─total_rows─┬─total_bytes─┐
│ exp_1_default │ ['/home/ch/disk_1/store/00f/00f12043-d5e8-427e-80f1-2043d5e8027e/']                                                                   │ /home/alexelex/master/programs/server/store/6ae/6aeb2dfb-798d-4d2d-aaeb-2dfb798d5d2d/exp_1_default.sql │        2021-05-13 12:45:20 │ default        │          0 │           0 │
│ exp_1_secret  │ ['/home/ch/disk_2/store/9a4/9a4f8b0e-70c2-4026-9a4f-8b0e70c21026/','/home/ch/disk_2/store/9a4/9a4f8b0e-70c2-4026-9a4f-8b0e70c21026/'] │ /home/alexelex/master/programs/server/store/6ae/6aeb2dfb-798d-4d2d-aaeb-2dfb798d5d2d/exp_1_secret.sql  │        2021-05-13 12:45:56 │ secret         │          0 │           0 │
└───────────────┴───────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┴────────────────────────────────────────────────────────────────────────────────────────────────────────┴────────────────────────────┴────────────────┴────────────┴─────────────┘

2 rows in set. Elapsed: 0.023 sec.
