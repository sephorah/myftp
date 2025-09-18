/*
** EPITECH PROJECT, 2024
** handle_file_transfer.c
** File description:
** my_ftp
*/

#include "my_ftp.h"

char *get_file_content(char *filename)
{
    int fd = open(filename, O_RDONLY);
    char *buffer = NULL;
    struct stat statbuf;

    stat(filename, &statbuf);
    buffer = malloc(sizeof(char) * (statbuf.st_size + 1));
    if (buffer == NULL) {
        close(fd);
        return NULL;
    }
    if (read(fd, buffer, statbuf.st_size) == -1) {
        close(fd);
        return NULL;
    }
    buffer[statbuf.st_size] = '\0';
    close(fd);
    return buffer;
}

void handle_retr_command(int client_fd, char *input,
    struct server_info_s *info)
{
    char **input_arr = my_str_to_word_array(input, " \r\n");
    char *file_content = NULL;

    if (input_arr == NULL || input_arr[1] == NULL) {
        dprintf(client_fd, "%d\n", 550);
        return;
    }
    file_content = get_file_content(input_arr[1]);
    if (file_content == NULL) {
        dprintf(client_fd, "%d\n", 550);
        return;
    }
    dprintf(client_fd, "%d File status okay; about to"
    " open data connection.\n", 150);
    dprintf(info->client_data_sock, file_content);
    close(info->client_data_sock);
    close(info->data_socket);
    dprintf(client_fd, "%d Closing data connection. Requested file "
    "action successful.\n",
    226);
}

int upload_file(int client_fd, char *filename)
{
    int fd_new_file = open(filename, O_CREAT | O_RDWR,
    S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
    char buffer[BUFFER_LEN];
    int len = 0;

    if (fd_new_file == -1) {
        return 0;
    }
    len = read(client_fd, buffer, BUFFER_LEN);
    while (len > 0){
        write(fd_new_file, buffer, len);
        len = read(client_fd, buffer, BUFFER_LEN);
    }
    return 1;
}

void handle_stor_command(int client_fd, char *input,
    struct server_info_s *info)
{
    char **input_arr = my_str_to_word_array(input, " \r\n");

    if (input_arr == NULL || input_arr[1] == NULL) {
        dprintf(client_fd, "%d\n", 550);
        return;
    }
    dprintf(client_fd, "%d File status okay; about to open "
    "data connection.\n", 150);
    if (upload_file(info->client_data_sock, input_arr[1])) {
        dprintf(client_fd, "%d Closing data connection."
        " Requested file action successful\n", 226);
    } else {
        dprintf(client_fd, "%d\n", 550);
    }
    close(info->client_data_sock);
    close(info->data_socket);
}
