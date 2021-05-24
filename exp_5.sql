/*

Let's recreate exp_secret, insert one time (to disk_2) and check alter table move

*/

ALTER TABLE exp_secret MOVE PART 'all_1_1_0' TO DISK 'disk_3';
