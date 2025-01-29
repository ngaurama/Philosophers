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

OBJ_DIR = obj
MANDATORY_OBJ_DIR = $(OBJ_DIR)/philo
OBJS = $(SRCS:%.c=$(MANDATORY_OBJ_DIR)/%.o)
BONUS_OBJS = $(BONUS_SRCS:%.c=$(BONUS_OBJ_DIR)/%.o)
LIBFT = libft/libft.a

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@echo "Linking $(NAME)..."
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

# bonus: $(LIBFT) $(BONUS_NAME)

# $(BONUS_NAME): $(BONUS_OBJS) $(LIBFT)
# 	@echo "Linking $(BONUS_NAME)..."
# 	@$(CC) $(CFLAGS) $(BONUS_OBJS) $(LIBFT) -o $(BONUS_NAME)

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

$(LIBFT):
	@echo "Building libft..."
	@make -C libft --no-print-directory

clean:
	@echo "Cleaning project files..."
	@rm -rf $(OBJ_DIR)
	@make -C libft clean --no-print-directory

fclean: clean
	@echo "Removing $(NAME) and $(BONUS_NAME)..."
	@rm -f $(NAME) $(BONUS_NAME)
	@make -C libft fclean --no-print-directory

re: fclean all

.PHONY: all clean fclean re bonus