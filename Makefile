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

$(NAME):	$(BUILD) $(OBJ)
	ar rcs -o $@ $(OBJ) 

$(BUILD)%.o:	$(SRC_DIR)%.c Makefile
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INCLUDES)

bonus: $(NAME)

clean:
	rm -rf $(BUILD)

fclean:	clean
	rm -rf $(NAME)

re: fclean all

.PHONY: re all fclean clean bonus

-include $(OBJ:.o=.d)

