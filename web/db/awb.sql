CREATE TABLE `users`(
    `id` INT UNSIGNED NOT NULL AUTO_INCREMENT,
    `username` VARCHAR(25) NOT NULL,
    `password` VARCHAR(255) NOT NULL,
    `access_token` VARCHAR(255) NOT NULL,
    `is_male` BOOL NOT NULL,
    `time_zone` TINYINT NOT NULL,
    `time_limit` BIGINT UNSIGNED NOT NULL DEFAULT 0
);
ALTER TABLE
    `users` ADD PRIMARY KEY `users_id_primary`(`id`);
CREATE TABLE `blocked_processes`(
    `id` INT UNSIGNED NOT NULL AUTO_INCREMENT,
    `user_id` INT UNSIGNED NOT NULL,
    `device` VARCHAR(255) NOT NULL,
    `process` VARCHAR(255) NOT NULL
);
ALTER TABLE
    `blocked_processes` ADD PRIMARY KEY `blocked_processes_id_primary`(`id`);
ALTER TABLE
    `blocked_processes` ADD CONSTRAINT `blocked_processes_user_id_foreign` FOREIGN KEY(`user_id`) REFERENCES `users`(`id`);
