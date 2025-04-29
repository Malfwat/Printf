NAME	=	libftprintf.a

SRC	=	printf.c \
		utils.c \
		utils2.c \
		print.c \
		parsing.c \
		get_len.c \
		get_len2.c \
		align.c \
		get_size_bonus.c \
		len.c

SRC_M	=	format.c

SRC_B	=  format_bonus.c

CC	=	cc

CFLAGS	=	-Wall -Wextra -Werror -MMD -g3

INCLUDES	=	includes/

SRC_DIR	=	srcs/

BUILD	=	.build/

OBJ	=	$(addprefix $(BUILD), $(SRC:.c=.o))
OBJ_B	=	$(addprefix $(BUILD), $(SRC_B:.c=.o))
OBJ_M	=	$(addprefix $(BUILD), $(SRC_M:.c=.o))

DEPS	=	$(OBJ:.o=.d)

all:	$(NAME)

$(BUILD):
	@mkdir -p $@

$(BUILD)libft.a:
	make bonus -C libft/

$(BUILD)libft_bonus.a:
	make bonusp -C libft/

$(NAME): $(BUILD) $(OBJ) $(OBJ_M) $(BUILD)libft.a
	ar rcs -o $(BUILD)libft.a $(OBJ) $(OBJ_M)
	cp $(BUILD)libft.a $@
	touch $(SRC_DIR)$(SRC_B)

$(BUILD)%.o:	$(SRC_DIR)%.c Makefile
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INCLUDES) -I./libft 

bonus: $(BUILD) $(OBJ_B) $(OBJ) $(BUILD)libft_bonus.a
	ar rcs -o $(BUILD)libft_bonus.a $(OBJ) $(OBJ_B)
	cp $(BUILD)libft_bonus.a $(NAME)
	touch $(SRC_DIR)$(SRC_M)

clean:
	rm -rf $(BUILD)
	make clean -C libft/

fclean:	
	rm -rf $(BUILD)
	make fclean -C libft/
	rm -rf $(NAME)

re: fclean all

.PHONY: re all fclean clean bonus

-include $(OBJ:.o=.d)

