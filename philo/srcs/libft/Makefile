CC = gcc

CFLAGS = -Wall -Wextra -Werror

NAME = libft.a

LIBC = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
		ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
		ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
		ft_strrchr.c ft_strncmp.c ft_memcmp.c ft_strnstr.c ft_atoi.c \
		ft_calloc.c ft_strdup.c ft_memchr.c get_next_line.c

ADD = ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
		ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
		ft_putendl_fd.c ft_putnbr_fd.c

ft_printf = ft_printf_d_i_helper.c  ft_printf_u.c	ft_result.c ft_printf.c ft_assign.c \
		ft_printf.c ft_printf_u_helpers.c handler.c ft_printf_c.c ft_printf_p.c \
		ft_printf_x.c	helpers.c utils.c ft_printf_d_i.c ft_printf_s.c	 ft_printf_x_helpers.c

BONUS = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c \
		ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c \
		ft_lstmap_bonus.c

SRCS = ${ft_printf} ${LIBC} ${ADD}

SRCSB = ${LIBC} ${ADD} ${BONUS} ${ft_printf}

OBJS = ${SRCS:.c=.o}

OBJSB = ${SRCSB:.c=.o}

.c.o:
	@${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
	@ar -rsc ${NAME} ${OBJS}

bonus:	${OBJSB}
	@ar -rsc ${NAME} ${OBJSB}

all: ${NAME}

clean:
	@rm -f ${OBJSB}

fclean:	clean;
	@echo "Removing $(NAME)..."
	@rm -f ${NAME}

re:	fclean all

.PHONY: all clean fclean re bonus
