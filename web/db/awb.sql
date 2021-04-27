CREATE TABLE `users`(
    `id` INT UNSIGNED NOT NULL AUTO_INCREMENT,
    `username` VARCHAR(25) NOT NULL,
    `password` VARCHAR(255) NOT NULL,
    `access_token` VARCHAR(255) NOT NULL,
    `is_male` BOOL NOT NULL,
    `time_zone` TINYINT NOT NULL,
    `time_limit` BIGINT UNSIGNED NOT NULL DEFAULT 0,
    PRIMARY KEY (`id`)
);