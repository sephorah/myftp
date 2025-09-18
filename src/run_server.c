/*
** EPITECH PROJECT, 2024
** server.c
** File description:
** my_ftp
*/

#include "my_ftp.h"

int run_server(unsigned int port, char *path)
{
    fd_set rfds;
    int used_fds[MAX_FDS] = {0};
    int max_fd = 0;
    int current_fd_i = 0;
    struct server_info_s info;

    info.server_socket = socket(AF_INET, SOCK_STREAM, 0);
    info.serv_addr = init_addr(port);
    if (!init_server(info.server_socket, &info.serv_addr, &info, path))
        return ERROR;
    while (1) {
        monitor_clients(&rfds, used_fds, &max_fd, &info);
        if (FD_ISSET(info.server_socket, &rfds)) {
            accept_connection(info.server_socket,
            used_fds, &info.serv_addr, &current_fd_i);
        }
        handle_clients(used_fds, &rfds, &info, path);
    }
    close(info.server_socket);
    return SUCCESS;
}
