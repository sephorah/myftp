/*
** EPITECH PROJECT, 2024
** handle_file_transfer.c
** File description:
** my_ftp
*/

#include "my_ftp.h"
#include <sys/wait.h>

void print_data_socket_ip_and_port(int client_fd,
    struct sockaddr_in *data_addr)
{
    in_addr_t ip_addr = data_addr->sin_addr.s_addr;
    int port = ntohs(data_addr->sin_port);
    int port1 = (port >> 8) & 0xFF;
    int port2 = port & 0xFF;

    dprintf(client_fd, "%d (%d,%d,%d,%d,%d,%d).\n", 227,
        (int)(ip_addr & 0xFF), (int)((ip_addr & 0xFF00) >> 8),
        (int)((ip_addr & 0xFF0000) >> 16),
        (int)((ip_addr & 0xFF000000) >> 24), port1, port2);
}

int init_data_socket(int data_socket, struct sockaddr_in *data_addr,
    struct sockaddr_in *serv_addr)
{
    int size_address = 0;

    data_addr->sin_family = AF_INET;
    data_addr->sin_port = 0;
    data_addr->sin_addr.s_addr = serv_addr->sin_addr.s_addr;
    size_address = sizeof(data_addr);
    if (bind(data_socket, (struct sockaddr *)data_addr,
    sizeof(*data_addr)) == -1) {
        return 0;
    }
    if (listen(data_socket, 1) == -1) {
        return 0;
    }
    if (getsockname(data_socket, (struct sockaddr *)data_addr,
    (socklen_t *)&size_address) == -1) {
        return 0;
    }
    return 1;
}

void handle_pasv_transfer(int client_fd, struct server_info_s *info)
{
    int size_address = 0;
    struct sockaddr_in data_addr;

    info->data_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (!init_data_socket(info->data_socket, &data_addr,
    &info->serv_addr)) {
        return;
    }
    print_data_socket_ip_and_port(client_fd, &data_addr);
    info->client_data_sock = accept(info->data_socket,
    (struct sockaddr *)&data_addr, (socklen_t *)&size_address);
    if (info->client_data_sock == -1) {
        return;
    }
}
