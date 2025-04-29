# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/12 10:00:00 by ansebast          #+#    #+#              #
#    Updated: 2025/04/29 19:52:57 by ansebast         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH)/libft.a

SRCS = binaries.c \
	   builtins.c \
	   create_commands.c \
	   execute.c \
	   execute_binary.c \
	   export.c \
	   expantion.c \
	   find_path_to_exec.c \
	   heredoc.c \
	   print_export.c \
	   redirections.c \
	   show_prompt.c \
	   signals.c \
	   utils_binaries.c \
	   utils_builtins.c \
	   utils_builtins_2.c \
	   utils_commands.c \
	   utils_create_commands.c \
	   aux.c

OBJS = $(SRCS:.c=.o)

RM = rm -f

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L$(LIBFT_PATH) -lft -lreadline

$(LIBFT):
	make -C $(LIBFT_PATH)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)
	make -C $(LIBFT_PATH) clean

fclean: clean
	$(RM) $(NAME)
	make -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: all clean fclean re
