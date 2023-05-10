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
#include "MLX42/include/MLX42/MLX42.h"

typedef	struct s_info
{
	mlx_image_t	*image;
	mlx_t		*mlx;
}				info_t;

void	ft_quit(void *mlx)
{
	printf("closed\n");
	mlx_terminate(mlx);
	exit(1);
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
	}
}

void	ft_cursor(double xpos, double ypos, void *cursor)
{
	info_t *info;

	info = cursor;
	
	info->image->instances[0].y = ypos;
	info->image->instances[0].x = xpos;
	info->image->instances[0].z = info->image->count;
	if (mlx_is_mouse_down(info->mlx, MLX_MOUSE_BUTTON_LEFT))
		mlx_image_to_window(info->mlx, info->image, xpos, ypos);
}

int	main(void)
{
	mlx_t			*mlx;
	mlx_image_t		*hello;
	mlx_texture_t	*ppr;
	mlx_image_t		*flag;
	info_t			info;

	printf("hello world!");
	mlx = mlx_init(1500, 920, "LGBTQ", false);
	ppr = mlx_load_png("ppr.png");
	flag = mlx_texture_to_image(mlx, ppr);
	hello = mlx_texture_to_image(mlx, mlx_load_png("pedro.png"));
	mlx_image_to_window(mlx, flag, 0, 0);
	mlx_image_to_window(mlx, hello, (mlx->width / 2) - (hello->width / 2), (mlx->height / 2) - (hello->height / 2));
	hello->enabled = true;
	mlx_close_hook(mlx, (mlx_closefunc)ft_quit, mlx);
	info.image = hello;
	info.mlx = mlx;
	mlx_key_hook(mlx, ft_key, &info);
	mlx_cursor_hook(mlx, (mlx_cursorfunc)ft_cursor, &info);
	mlx_loop(mlx);
	return (0);
}
