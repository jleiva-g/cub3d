NAME		= libft.a
HEADER		= inc/libft.h
SRC_FILES	= ctype0.c ctype1.c \
				string0.c string1.c string2.c string3.c string4.c string5.c \
				stdlib0.c \
				stdio0.c stdio1.c stdio2.c stdio3.c \
				list0.c list1.c
SRC_DIR		= src
SRC			= $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ_DIR		= $(SRC_DIR)/obj
OBJ			= $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))
AR			= ar rcs
CFLAGS		= -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	@$(AR) $@ $^
	@echo "Compilation successful. Created $@"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER) | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $@

clean:
	@$(RM) -rf $(OBJ_DIR)

fclean: clean
	@$(RM) -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
