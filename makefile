# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: igngonza <igngonza@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/22 11:32:21 by igngonza          #+#    #+#              #
#    Updated: 2025/05/26 12:10:02 by igngonza         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OBJ_DIR = obj
OBJ_UTILS_DIR = $(OBJ_DIR)/utils

CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread -I./src/include

SRC_MAIN = src/main.c
SRC_UTILS = $(wildcard src/utils/*.c)
OBJ_MAIN = $(OBJ_DIR)/main.o
OBJ_UTILS = $(patsubst src/utils/%.c,$(OBJ_UTILS_DIR)/%.o,$(SRC_UTILS))
OBJ = $(OBJ_MAIN) $(OBJ_UTILS)

TARGET = philo

all: $(OBJ_DIR) $(OBJ_UTILS_DIR) $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

$(OBJ_MAIN): $(SRC_MAIN)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_UTILS): $(OBJ_UTILS_DIR)/%.o: src/utils/%.c
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