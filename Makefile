CC = gcc
NAME = pedro
SRC = main.c
OBJ = ${SRCS:.c=.o}
MLX = MLX42/build/libmlx42.a


mlx:
	@mkdir -p MLX42/build
	@cmake MLX42/ -B MLX42/build
	@make -C MLX42/build -j4
	@echo "MLX42 build done!"

all: mlx
	$(CC) $(SRC) $(MLX) -Iinclude -ldl -lglfw -pthread -lm -o $(NAME)
	@echo "Build succesfully ! :)"

fclean:
	@rm -f $(OBJ)
	@rm -rf MLX42/build
	@rm $(NAME)
	@echo "Fclean complete :)"

mac: mlx
	$(CC) $(SRC) $(MLX) -framework Cocoa -framework OpenGL -framework IOKit -Iinclude -lglfw -L"/opt/homebrew/Cellar/glfw/3.3.8/lib/" -o pedro
	@echo "Build finished !"
