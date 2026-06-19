NAME		=	cub3d
HEADER		=	inc/cub3d.h
SRC_FILES	=	main.c cleanup.c utils.c init.c textures.c raycasting.c \
				minimap.c rendering.c movement.c validate_utils.c parse.c \
				parse2.c parse3.c validate.c init2.c
SRC_DIR		=	src
SRC			=	$(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ_DIR		=	$(SRC_DIR)/obj
OBJ			=	$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))
LIBFT_DIR	=	inc/libft
LIBFT		=	$(LIBFT_DIR)/libft.a
MLX42_DIR	=	inc/MLX42
BUILD_DIR	=	inc/MLX42build
MLX42		=	$(BUILD_DIR)/libmlx42.a
CFLAGS		=	-Wall -Wextra -Werror -g
MFLAGS		=	-ldl -lglfw -pthread -lm

all: $(NAME)

$(LIBFT):
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR)

$(MLX42):
	@cmake -S $(MLX42_DIR) -B $(BUILD_DIR)
	@$(MAKE) --no-print-directory -C $(BUILD_DIR) -j4

$(NAME): $(OBJ) $(LIBFT) $(MLX42)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX42) -o $(NAME) $(MFLAGS)
	@echo "Compilation successful. Created $(NAME)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER) | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $@

clean:
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) clean
	@$(MAKE) --no-print-directory -C $(BUILD_DIR) clean
	@rm -rf $(OBJ_DIR)

fclean: clean
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) fclean
	@rm -rf $(BUILD_DIR)
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re