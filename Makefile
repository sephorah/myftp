##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## Makefile
##

SRC 		= 		src/main.c \
					src/run_server.c \
					src/server.c \
					src/handle_clients.c \
					src/handle_auth.c \
					src/handle_directory_commands.c \
					src/my_str_to_word_array.c \
					src/handle_pasv.c \
					src/handle_list_command.c \
					src/handle_file_transfer.c \

OBJ 		=		$(SRC:.c=.o)

NAME 		=	 	myftp

CPPFLAGS	=		-iquote include/

CFLAGS 		=		-Werror -Wall -Wextra

CC 		?=		gcc

RM 		= 		rm -f

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ)

debug: CFLAGS += -g3
debug: re

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY:	fclean clean all re debug tests_run
