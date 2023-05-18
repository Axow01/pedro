/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pedro.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 17:15:19 by mmarcott          #+#    #+#             */
/*   Updated: 2023/05/12 17:15:19 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PEDRO_H
# define PEDRO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <time.h>
# include "MLX42/include/MLX42/MLX42.h"

typedef struct	s_pedro
{
	mlx_image_t		*img;
	struct s_pedro	*next;
}					pedro_t;

typedef	struct s_info
{
	mlx_image_t	*image;
	mlx_t		*mlx;
	mlx_image_t	*back;
	double		x;
	double		y;
	mlx_texture_t *sex;
	pedro_t		*pedro;
}				info_t;

/* This function add a new image and displays it on the screen. */
void	add_pedro(info_t *info);

// This function deletes all the pedros.
void	remove_pedro(info_t *info, int count);

int		get_pedro_size(pedro_t *pedro);

#endif
