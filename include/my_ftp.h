/*
** EPITECH PROJECT, 2024
** my_ftp.h
** File description:
** my_ftp
*/

#ifndef MY_FTP_H_
    #define MY_FTP_H_
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <stdio.h>
    #include <unistd.h>
    #include <stdlib.h>
    #include <errno.h>
    #include <sys/select.h>
    #include <string.h>
    #include <fcntl.h>
    #include <sys/stat.h>

    #define MAX_FDS 20
    #define BUFFER_LEN 500
    #define SUCCESS 0
    #define ERROR 84

struct server_info_s {
    int server_socket;
    struct sockaddr_in serv_addr;
    int data_socket;
    int client_data_sock;
    int is_user_set;
    int is_password_set;
};

int monitor_clients(fd_set *rfds, int *used_fds, int *max_fd,
    struct server_info_s *info);
void add_to_used_fds(int new_socket, int *used_fds, int *current_fd_index);
void accept_connection(int main_socket, int *used_fds,
    struct sockaddr_in *serv_addr, int *current_fd_index);
int init_server(int main_socket, struct sockaddr_in *serv_addr,
    struct server_info_s *info, char *path);
struct sockaddr_in init_addr(unsigned int port);
int run_server(unsigned int port, char *path);
void handle_clients(int *used_fds, fd_set *rfds,
    struct server_info_s *info, char *home);
int handle_server_info(int client_fd, char *input, struct server_info_s *info);
void change_working_directory(int client_fd, char *input, char *home);
char **my_str_to_word_array(char const *str, char const *delim);
void go_to_parent_dir(int client_fd);
void get_cwd(int client_fd);
void delete_file(int client_fd, char *input);
void handle_pasv_transfer(int client_fd, struct server_info_s *info);
void handle_list_command(int client_fd, struct server_info_s *info);
void handle_retr_command(int client_fd, char *input,
    struct server_info_s *info);
void handle_stor_command(int client_fd, char *input,
    struct server_info_s *info);

#endif /* !MY_FTP_H_ */
