NAME		=	cub3D
HEADER		=	inc/cub3d.h
SRC_FILES	=	main.c cleanup.c utils.c init.c textures.c raycasting.c \
				minimap.c rendering.c movement.c validate_utils.c parse.c \
				parse2.c parse3.c validate.c init2.c
SRC_DIR		=	src
SRC			=	$(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ_DIR		=	$(SRC_DIR)/obj
OBJ			=	$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))
BONUS_NAME	=	cub3d_bonus
BONUS_H		=	inc/cub3d_bonus.h
BONUS_FILES	=	main_bonus.c cleanup_bonus.c utils_bonus.c init_bonus.c \
				textures_bonus.c raycasting_bonus.c minimap_bonus.c \
				rendering_bonus.c movement_bonus.c validate_utils_bonus.c \
				parse_bonus.c parse2_bonus.c parse3_bonus.c validate_bonus.c \
				init2_bonus.c
BONUS_DIR	=	$(SRC_DIR)/bonus
BONUS_SRC	=	$(addprefix $(BONUS_DIR)/, $(BONUS_FILES))
B_OBJ_DIR	=	$(BONUS_DIR)/obj
BONUS_OBJ	=	$(patsubst $(BONUS_DIR)/%.c,$(B_OBJ_DIR)/%.o,$(BONUS_SRC))
LIBFT_DIR	=	inc/libft
LIBFT		=	$(LIBFT_DIR)/libft.a
MLX42_DIR	=	inc/MLX42
BUILD_DIR	=	inc/MLX42build
MLX42		=	$(BUILD_DIR)/libmlx42.a
CFLAGS		=	-Wall -Wextra -Werror
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

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(BONUS_OBJ) $(LIBFT) $(MLX42)
	@$(CC) $(CFLAGS) $(BONUS_OBJ) $(LIBFT) $(MLX42) -o $(BONUS_NAME) $(MFLAGS)
	@echo "Compilation successful. Created $(BONUS_NAME)"

$(B_OBJ_DIR)/%.o: $(BONUS_DIR)/%.c $(BONUS_H) | $(B_OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(B_OBJ_DIR):
	@mkdir -p $@

clean:
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) clean
	@$(MAKE) --no-print-directory -C $(BUILD_DIR) clean
	@rm -rf $(OBJ_DIR) $(BONUS_OBJ)

fclean: clean
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) fclean
	@rm -rf $(BUILD_DIR)
	@rm -rf $(NAME) $(BONUS_NAME)

re: fclean all

.PHONY: all clean fclean re