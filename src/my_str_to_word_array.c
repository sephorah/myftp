/*
** EPITECH PROJECT, 2024
** my_str_to_word_array.c
** File description:
** my_ftp
*/

#include "my_ftp.h"

int count_words(char const *str, char const *delim)
{
    int nb_words = 0;
    char *copy_str = strdup(str);
    char *arg;

    arg = strtok(copy_str, delim);
    nb_words++;
    while (arg != NULL){
        arg = strtok(NULL, delim);
        nb_words++;
    }
    free(copy_str);
    return nb_words;
}

char **my_str_to_word_array(char const *str, char const *delim)
{
    int len_str = strlen(str) + 1;
    int i = 1;
    int nb_words = count_words(str, delim) + 1;
    char *copy_str = strdup(str);
    char *arg;
    char **words = malloc(sizeof(char *) * nb_words);

    arg = strtok(copy_str, delim);
    words[0] = arg;
    for (; arg != NULL && i < len_str; i++){
        arg = strtok(NULL, delim);
        words[i] = arg;
    }
    words[i] = NULL;
    return words;
}
