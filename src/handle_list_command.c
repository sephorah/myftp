/*
** EPITECH PROJECT, 2024
** handle_list_command.c
** File description:
** my_ftp
*/

#include "my_ftp.h"

void list_files_of_cwd(int client_data_sock, int data_socket)
{
    char *path_var = getenv("PATH");
    char *new_env[] = {path_var, NULL};
    char *args[] = {"/bin/ls", "-l", NULL};
    pid_t pid_child = fork();

    if (pid_child == 0) {
        dup2(client_data_sock, STDOUT_FILENO);
        execve("/bin/ls", args, new_env);
    }
    close(client_data_sock);
    close(data_socket);
}

void handle_list_command(int client_fd, struct server_info_s *info)
{
    dprintf(client_fd, "%d File status okay; about to"
    " open data connection.\n", 150);
    list_files_of_cwd(info->client_data_sock, info->data_socket);
    dprintf(client_fd, "%d Closing data connection. Requested file "
    "action successful.\n", 226);
}
