NAME	=	libftprintf.a

SRC	=	printf.c \
		printf2.c \
		printf3.c \
		printf4.c \
		printf5.c \
		get_len.c \
		get_len2.c \
		len.c

CC	=	cc

CFLAGS	=	-Wall -Wextra -Werror -MMD -g3

INCLUDES	=	includes/

SRC_DIR	=	srcs/

BUILD	=	.build/

OBJ	=	$(addprefix $(BUILD), $(SRC:.c=.o))

DEPS	=	$(OBJ:.o=.d)

all:	$(NAME)

$(BUILD):
	@mkdir -p $@

libft.a:
	make bonus -C libft/

$(NAME): libft.a $(BUILD) $(OBJ)
	ar rcs -o libft.a $(OBJ)
	cp libft.a $@

$(BUILD)%.o:	$(SRC_DIR)%.c Makefile
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INCLUDES)  -I./libft

bonus: $(NAME)

clean:
	rm -rf $(BUILD)
	make clean -C libft

fclean:	clean
	make fclean -C libft
	rm -rf $(NAME)

re: fclean all

.PHONY: re all fclean clean bonus

-include $(OBJ:.o=.d)

