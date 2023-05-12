/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 23:20:03 by mmarcott          #+#    #+#             */
/*   Updated: 2023/05/09 23:20:03 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pedro.h"

void	ft_quit(void *mlx)
{
	printf("closed\n");
	mlx_terminate(mlx);
	exit(1);
}

int generateRandomNumber(int instanceIndex) {
    // Seed the random number generator with the current time and instance index
    srand(time(NULL) + instanceIndex);

    // Generate a random number between -5 and 5
    int randomNumber = rand() % 21 - 10;

    return randomNumber;
}

int generateRandomNumberX(int instanceIndex) {
    // Seed the random number generator with the current time and instance index
    srand(time(NULL) + instanceIndex);

    // Generate a random number between -5 and 5
    int randomNumber = rand() % 11 - 5;

    return randomNumber;
}

void	ft_key(mlx_key_data_t key, void *mlx)
{
	info_t	*info;
	int	i;

	i = 0;

	info = (info_t*)mlx;
	if (key.key == MLX_KEY_ESCAPE)
		ft_quit(info->mlx);
	else if (key.key == MLX_KEY_C)
		remove_pedro(info, 4);
}

void	ft_cursor(double xpos, double ypos, void *cursor)
{
	info_t *info;

	info = cursor;
	info->x = xpos;
	info->y = ypos;
	info->image->instances[0].y = ypos - (info->image->height / 2);
	info->image->instances[0].x = xpos - (info->image->width / 2);
}

void	ft_loop(info_t *info)
{
	int 		i;
	static int	count = 0;
	pedro_t	*current = info->pedro;

	i = 0;

	while (current->next)
	{
		current->img->instances[0].y += generateRandomNumber(i);
		current->img->instances[0].x += generateRandomNumberX(i++);
		current = current->next;
	}
	info->image->instances[0].z = info->image->count;
	if (mlx_is_mouse_down(info->mlx, MLX_MOUSE_BUTTON_LEFT)) {
		add_pedro(info);
		count++;
	}
}

int	main(void)
{
	mlx_t			*mlx;
	mlx_image_t		*hello;
	mlx_texture_t	*ppr;
	mlx_image_t		*flag;
	info_t			info;

	printf("hello world!");
	info.pedro = calloc(1, sizeof(pedro_t));
	mlx = mlx_init(1500, 920, "PEDRO PASCAL OMG !", true);
	ppr = mlx_load_png("better.png");
	flag = mlx_texture_to_image(mlx, ppr);
	info.sex = mlx_load_png("pedro.png");
	info.back = flag;
	hello = mlx_texture_to_image(mlx, info.sex);
	mlx_image_to_window(mlx, flag, 0, 0);
	mlx_put_string(mlx, "RESET = C  ---  NEW PEDRO = MOUSE CLICK", 10, 10);
	mlx_image_to_window(mlx, hello, (mlx->width / 2) - (hello->width / 2), (mlx->height / 2) - (hello->height / 2));
	hello->enabled = true;
	mlx_close_hook(mlx, (mlx_closefunc)ft_quit, mlx);
	info.image = hello;
	info.mlx = mlx;
	mlx_set_cursor_mode(mlx, MLX_MOUSE_HIDDEN);
	mlx_key_hook(mlx, ft_key, &info);
	mlx_cursor_hook(mlx, (mlx_cursorfunc)ft_cursor, &info);
	mlx_loop_hook(mlx, ft_loop, &info);
	mlx_loop(mlx);
	return (0);
}
