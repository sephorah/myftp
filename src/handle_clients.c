/*
** EPITECH PROJECT, 2024
** handle_clients.c
** File description:
** my_ftp
*/

#include "my_ftp.h"

static int handle_file_transfer(int *client_fd, char *input,
    struct server_info_s *info)
{
    if (strcmp(input, "PASV\r\n") == 0) {
        handle_pasv_transfer(*client_fd, info);
        return 1;
    }
    if (strcmp(input, "LIST\r\n") == 0) {
        handle_list_command(*client_fd, info);
        return 1;
    }
    if (strncmp(input, "RETR ", 5) == 0) {
        handle_retr_command(*client_fd, input, info);
        return 1;
    }
    if (strncmp(input, "STOR ", 5) == 0) {
        handle_stor_command(*client_fd, input, info);
        return 1;
    }
    return 0;
}

static int handle_other_commands(int *client_fd, char *input, char *home)
{
    if (strncmp(input, "CWD ", 4) == 0) {
        change_working_directory(*client_fd, input, home);
        return 1;
    }
    if (strcmp(input, "CDUP\r\n") == 0) {
        go_to_parent_dir(*client_fd);
        return 1;
    }
    if (strcmp(input, "PWD\r\n") == 0) {
        get_cwd(*client_fd);
        return 1;
    }
    if (strncmp(input, "DELE ", 5) == 0) {
        delete_file(*client_fd, input);
        return 1;
    }
    return 0;
}

static int handle_commands(int *client_fd, char *input,
    struct server_info_s *info)
{
    if (!(info->is_user_set && info->is_password_set)) {
        dprintf(*client_fd, "%d\n", 530);
        return 1;
    }
    if (strcmp(input, "HELP\r\n") == 0) {
        dprintf(*client_fd, "%d USER PASS CWD CDUP QUIT DELE PWD"
        " PASV PORT HELP NOOP RETR STOR LIST\n", 214);
        return 1;
    }
    if (strcmp(input, "NOOP\r\n") == 0) {
        dprintf(*client_fd, "%d Ok.\n", 200);
        return 1;
    }
    if (strcmp(input, "QUIT\r\n") == 0) {
        dprintf(*client_fd, "%d Goodbye.\n", 221);
        close(*client_fd);
        *client_fd = 0;
        return 1;
    }
    return 0;
}

static void handle_client_input(int *client_fd, struct server_info_s *info,
    char *home)
{
    char input[BUFFER_LEN];
    int len = read(*client_fd, input, BUFFER_LEN);

    input[len] = '\0';
    if (handle_server_info(*client_fd, input, info)) {
        return;
    }
    if (handle_commands(client_fd, input, info)) {
        return;
    }
    if (handle_other_commands(client_fd, input, home)) {
        return;
    }
    if (handle_file_transfer(client_fd, input, info)) {
        return;
    }
    dprintf(*client_fd, "%d\n", 500);
}

void handle_clients(int *used_fds, fd_set *rfds,
    struct server_info_s *info, char *home)
{
    for (int i = 0; i < MAX_FDS; i += 1) {
        if (FD_ISSET(used_fds[i], rfds) && used_fds[i] > 0) {
            handle_client_input(&used_fds[i], info, home);
        }
    }
}
