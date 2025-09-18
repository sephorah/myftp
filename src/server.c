/*
** EPITECH PROJECT, 2024
** handle_server.c
** File description:
** my_ftp
*/

#include "my_ftp.h"

int monitor_clients(fd_set *rfds, int *used_fds, int *max_fd,
    struct server_info_s *info)
{
    FD_ZERO(rfds);
    FD_SET(info->server_socket, rfds);
    *max_fd = info->server_socket;
    for (int i = 0; i < MAX_FDS; i++) {
        if (used_fds[i] > 0) {
            FD_SET(used_fds[i], rfds);
        }
        if (used_fds[i] > *max_fd) {
            *max_fd = used_fds[i];
        }
    }
    if (select(*max_fd + 1, rfds, NULL, NULL, NULL) < 0) {
        perror("Error select");
        return 0;
    }
    return 1;
}

void add_to_used_fds(int new_socket, int *used_fds, int *current_fd_index)
{
    for (int i = 0; i < MAX_FDS; i++) {
        if (used_fds[i] == 0) {
            used_fds[i] = new_socket;
            printf("Adding to list of sockets as %d\n", i);
            *current_fd_index = i;
            break;
        }
    }
}

void accept_connection(int main_socket, int *used_fds,
    struct sockaddr_in *serv_addr, int *current_fd_index)
{
    int size_address = sizeof(serv_addr);
    int new_socket = accept(main_socket, (struct sockaddr *)serv_addr,
            (socklen_t *)&size_address);

    if (new_socket > 0) {
        printf("Connection from %s:%d\n", inet_ntoa(serv_addr->sin_addr),
        ntohs(serv_addr->sin_port));
        add_to_used_fds(new_socket, used_fds, current_fd_index);
        dprintf(used_fds[*current_fd_index], "%d\n", 220);
    } else {
        perror("Error accept\n");
    }
}

int init_server(int main_socket, struct sockaddr_in *serv_addr,
    struct server_info_s *server_info_s, char *path)
{
    int opt = 1;

    server_info_s->is_user_set = 0;
    server_info_s->is_password_set = 0;
    if (main_socket == -1 ||
    setsockopt(main_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt,
    sizeof(opt)) < 0) {
        return 0;
    }
    if (bind(main_socket, (struct sockaddr *)serv_addr,
    sizeof(*serv_addr)) == -1) {
        perror("Error bind");
        return 0;
    }
    if (listen(main_socket, MAX_FDS) == -1) {
        perror("Error listen");
        return 0;
    }
    chdir(path);
    return 1;
}

struct sockaddr_in init_addr(unsigned int port)
{
    struct sockaddr_in serv_addr;

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    return serv_addr;
}
