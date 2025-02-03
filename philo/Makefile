# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ngaurama <ngaurama@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/01 15:03:41 by ngaurama          #+#    #+#              #
#    Updated: 2025/02/03 15:09:21 by ngaurama         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = philo
SRCS = design.c \
	   inits.c \
	   main.c \
       monitor.c \
       simulation.c \
       start_and_clean.c \
       utils.c \
	   philo_utils.c

OBJ_DIR = obj
MANDATORY_OBJ_DIR = $(OBJ_DIR)/philo
OBJS = $(SRCS:%.c=$(MANDATORY_OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	@echo "Linking $(NAME)..."
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(MANDATORY_OBJ_DIR)/%.o: %.c | $(MANDATORY_OBJ_DIR)
	@mkdir -p $(@D)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@

$(MANDATORY_OBJ_DIR):
	@mkdir -p $(MANDATORY_OBJ_DIR)

clean:
	@echo "Cleaning project files..."
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "Removing $(NAME)..."
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re