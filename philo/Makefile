# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ngaurama <ngaurama@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/01 15:03:41 by ngaurama          #+#    #+#              #
#    Updated: 2025/02/01 15:03:42 by ngaurama         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = philo
BONUS_NAME = checker
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
BONUS_OBJS = $(BONUS_SRCS:%.c=$(BONUS_OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	@echo "Linking $(NAME)..."
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

# bonus: $(BONUS_NAME)

# $(BONUS_NAME): $(BONUS_OBJS)
# 	@echo "Linking $(BONUS_NAME)..."
# 	@$(CC) $(CFLAGS) $(BONUS_OBJS) -o $(BONUS_NAME)

$(MANDATORY_OBJ_DIR)/%.o: %.c | $(MANDATORY_OBJ_DIR)
	@mkdir -p $(@D)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@

# $(BONUS_OBJ_DIR)/%.o: %.c | $(BONUS_OBJ_DIR)
# 	@mkdir -p $(@D)
# 	@echo "Compiling $<..."
# 	@$(CC) $(CFLAGS) -c $< -o $@

$(MANDATORY_OBJ_DIR):
	@mkdir -p $(MANDATORY_OBJ_DIR)

# $(BONUS_OBJ_DIR):
# 	@mkdir -p $(BONUS_OBJ_DIR)

clean:
	@echo "Cleaning project files..."
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "Removing $(NAME) and $(BONUS_NAME)..."
	@rm -f $(NAME) $(BONUS_NAME)

re: fclean all

.PHONY: all clean fclean re bonus