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

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "MLX42/include/MLX42/MLX42.h"

typedef	struct s_info
{
	mlx_image_t	*image;
	mlx_t		*mlx;
	mlx_image_t	*back;
	double		x;
	double		y;
	mlx_texture_t *sex;
	mlx_image_t		*ped2;
}				info_t;

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
	{
		while (++i < info->image->count)
			info->image->instances[i].enabled = false;
		i = -1;
		while (++i < info->ped2->count)
			info->ped2->instances[i].enabled = false;
	}
	else if (key.key == MLX_MOUSE_BUTTON_LEFT)
		mlx_image_to_window(info->mlx, info->image, info->x, info->y);
	else if (key.key == MLX_MOUSE_BUTTON_RIGHT)
		mlx_image_to_window(info->mlx, info->ped2, info->x, info.y);
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

	i = 0;

	while (++i < info->image->count)
	{
		if (info->image->instances[i].enabled)
			info->image->instances[i].y += generateRandomNumber(i);
		if (info->image->instances[i].x > info->mlx->width || info->image->instances[i].y > info->mlx->height)
			info->image->instances[i].enabled = false;
	}
	i = -1;
	while (++i < info->ped2->count)
	{
		if (info->ped2->instances[i].enabled)
			info->ped2->instances[i].y += generateRandomNumber(i);
		if ((info->ped2->instances[i].x > info->mlx->width || info->ped2->instances[i].x < 0) || (info->ped2->instances[i].y > info->mlx->height || info->ped2->instances[i].y < 0))
			info->ped2->instances[i].enabled = false;
	}
	info->image->instances[0].z = info->image->count;
}

int	main(void)
{
	mlx_t			*mlx;
	mlx_image_t		*hello;
	mlx_texture_t	*ppr;
	mlx_image_t		*flag;
	info_t			info;

	printf("hello world!");
	mlx = mlx_init(1500, 920, "PEDRO PASCAL OMG !", false);
	ppr = mlx_load_png("better.png");
	flag = mlx_texture_to_image(mlx, ppr);
	info.sex = mlx_load_png("pedro.png");
	info.back = flag;
	info.ped2 = mlx_texture_to_image(mlx, mlx_load_png("ped2.png"));
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
