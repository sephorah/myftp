/*
** EPITECH PROJECT, 2024
** handle_auth.c
** File description:
** my_ftp
*/

#include "my_ftp.h"

int handle_good_server_info(int client_fd, char *input,
    struct server_info_s *info)
{
    if ((info->is_user_set == 1) && strcmp(input, "PASS \r\n") == 0) {
        info->is_password_set = 1;
        dprintf(client_fd, "%d User logged in, proceed.\r\n", 230);
        return 1;
    }
    return 0;
}

int handle_server_info(int client_fd, char *input, struct server_info_s *info)
{
    if (strncmp(input, "USER ", 5) == 0) {
        info->is_user_set = 1;
        dprintf(client_fd, "%d User name okay, need password.\r\n", 331);
        return 1;
    }
    if (strncmp(input, "PASS", 4) == 0 && (info->is_user_set == 0)) {
        dprintf(client_fd, "%d\n", 503);
        return 1;
    }
    return handle_good_server_info(client_fd, input, info);
}
