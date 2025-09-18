/*
** EPITECH PROJECT, 2024
** handle_directory_commands.c
** File description:
** my_ftp
*/

#include "my_ftp.h"

void change_working_directory(int client_fd, char *input, char *home)
{
    char **input_arr = my_str_to_word_array(input, " \r\n");
    int chdir_return_val = 0;
    char *dest = NULL;

    if (input_arr == NULL || input_arr[1] == NULL) {
        dprintf(client_fd, "%d\n", 550);
        return;
    }
    if (strcmp(input_arr[1], "~") == 0) {
        dest = home;
    } else {
        dest = input_arr[1];
    }
    chdir_return_val = chdir(dest);
    if (chdir_return_val == -1) {
        dprintf(client_fd, "%d\n", 550);
    } else {
        dprintf(client_fd, "%d\n", 250);
    }
}

void go_to_parent_dir(int client_fd)
{
    int chdir_return_val = chdir("..");

    if (chdir_return_val == -1) {
        dprintf(client_fd, "%d\n", 550);
    } else {
        dprintf(client_fd, "%d\n", 250);
    }
}

void get_cwd(int client_fd)
{
    char *cwd = getcwd(NULL, 0);

    dprintf(client_fd, "%d %s\n", 257, cwd);
}

void delete_file(int client_fd, char *input)
{
    char **input_arr = my_str_to_word_array(input, " \r\n");
    int remove_return_val = 0;

    if (input_arr == NULL || input_arr[1] == NULL) {
        dprintf(client_fd, "%d\n", 550);
        return;
    }
    remove_return_val = remove(input_arr[1]);
    if (remove_return_val == 0) {
        dprintf(client_fd, "%d\n", 250);
    } else {
        dprintf(client_fd, "%d\n", 550);
    }
}
