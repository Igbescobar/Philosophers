# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: igngonza <igngonza@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/22 11:32:21 by igngonza          #+#    #+#              #
#    Updated: 2025/05/22 12:41:42 by igngonza         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OBJ_DIR = obj
OBJ_UTILS_DIR = $(OBJ_DIR)/utils

CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread -I./src/include

SRC_MAIN = src/main.c
SRC_PARSE = src/utils/parse_args.c
SRC_TIME = src/utils/time_utils.c

OBJ_MAIN = $(OBJ_DIR)/main.o
OBJ_PARSE = $(OBJ_UTILS_DIR)/parse_args.o
OBJ_TIME = $(OBJ_UTILS_DIR)/time_utils.o
OBJ = $(OBJ_MAIN) $(OBJ_PARSE) $(OBJ_TIME)

TARGET = philo

all: $(OBJ_DIR) $(OBJ_UTILS_DIR) $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

$(OBJ_MAIN): $(SRC_MAIN)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_PARSE): $(SRC_PARSE)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_TIME): $(SRC_TIME)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_UTILS_DIR):
	mkdir -p $(OBJ_UTILS_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(TARGET)

re: fclean all

.PHONY: all clean fclean re