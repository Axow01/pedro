CC = gcc
NAME = pedro
SRC = main.c
OBJ = ${SRCS:.c=.o}
MLX = MLX42/build/libmlx42.a

mac:
	$(CC) $(SRC) $(MLX) -framework Cocoa -framework OpenGL -framework IOKit -Iinclude -lglfw -L"/opt/homebrew/Cellar/glfw/3.3.8/lib/" -o pedro

all:
	@$(CC) $(SRC) $(MLX) -Iinclude -ldl -lglfw -pthread -lm -o $(NAME)
	@echo "Build succesfully ! :)"

fclean:
	@rm -f $(OBJ)
	@echo "Fclean complete :)"
