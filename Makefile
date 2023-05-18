CC = gcc

NAME = pedro

SRC = main.c new_image.c

OBJ = ${SRC:.c=.o}

MLX = MLX42/build/libmlx42.a

all: $(NAME)

$(NAME): $(OBJ) mlx
	$(CC) $(OBJ) $(MLX) -g -Iinclude -ldl -lglfw -pthread -lm -o $(NAME)
	@echo "Build succesfully ! :)"

mlx:
	@mkdir -p MLX42/build
	@cmake MLX42/ -B MLX42/build
	@make -C MLX42/build -j4
	@echo "MLX42 build done!"


fclean:
	@rm -f $(OBJ)
	@rm -rf MLX42/build
	@rm $(NAME)
	@echo "Fclean complete :)"

mac: mlx $(OBJ)
	$(CC) $(OBJ) $(MLX) -framework Cocoa -framework OpenGL -framework IOKit -Iinclude -lglfw -L"/Users/mmarcott/.brew/opt/glfw/lib/" -o pedro
	@echo "Build finished !"
