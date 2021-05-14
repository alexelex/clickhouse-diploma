click.ru-central1.internal :) SELECT *　FROM system.storage_policies

SELECT *
FROM system.storage_policies

Query id: 9c63ef37-a8fc-4277-94d4-b49f43dfc60c

┌─policy_name─┬─volume_name────┬─volume_priority─┬─disks───────────────┬─volume_type─┬─max_data_part_size─┬─move_factor─┬─prefer_not_to_merge─┐
│ default     │ default_volume │               1 │ ['disk_1']          │ JBOD        │                  0 │           0 │                   0 │
│ secret      │ default_volume │               1 │ ['disk_2','disk_3'] │ JBOD        │                  0 │           0 │                   0 │
└─────────────┴────────────────┴─────────────────┴─────────────────────┴─────────────┴────────────────────┴─────────────┴─────────────────────┘

2 rows in set. Elapsed: 0.011 sec. 

click.ru-central1.internal :) SELECT *　FROM system.disks

SELECT *
FROM system.disks

Query id: 0fe19cc5-b61c-4007-a74d-cb5ce09fd01b

┌─name────┬─path─────────────┬───free_space─┬──total_space─┬─keep_free_space─┬─type──────┐
│ default │ ./               │ 127825711104 │ 211387633664 │               0 │ local     │
│ disk_1  │ /home/ch/disk_1/ │ 127825711104 │ 211387633664 │               0 │ local     │
│ disk_2  │ /home/ch/disk_2/ │ 127825711104 │ 211387633664 │               0 │ local     │
│ disk_3  │ /home/ch/disk_2/ │ 127825711104 │ 211387633664 │               0 │ encrypted │
└─────────┴──────────────────┴──────────────┴──────────────┴─────────────────┴───────────┘

4 rows in set. Elapsed: 0.011 sec. 
