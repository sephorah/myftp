/*
** EPITECH PROJECT, 2024
** main.c
** File description:
** my_ftp
*/

#include "my_ftp.h"

int main(int ac, char **av)
{
    if (ac != 3) {
        return ERROR;
    }
    return run_server(atoi(av[1]), av[2]);
}
