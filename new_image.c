/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_image.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 17:14:42 by mmarcott          #+#    #+#             */
/*   Updated: 2023/05/12 17:14:42 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pedro.h"

int	get_pedro_size(pedro_t *pedro)
{
	pedro_t	*current;
	int		i;

	current = pedro;
	i = 0;
	while (current->next) {
		current = current->next;
		i++;
	}
	return (i);
}

void	add_pedro(info_t *info)
{
	pedro_t	*pedro;

	pedro = info->pedro;
	if (!pedro)
		pedro = calloc(1, sizeof(pedro_t));
	while (pedro->next)
		pedro = pedro->next;
	if (!pedro->img) {
		pedro->img = mlx_texture_to_image(info->mlx, info->sex);
		mlx_image_to_window(info->mlx, pedro->img, info->x, info->y);
		pedro->next = NULL;
		return ;
	}
	pedro->next = calloc(1, sizeof(pedro_t));
	pedro = pedro->next;
	pedro->img = mlx_texture_to_image(info->mlx, info->sex);
	pedro->next = NULL;
	mlx_image_to_window(info->mlx, pedro->img, info->x, info->y);
}

void remove_pedro(info_t *info, int count)
{
	pedro_t	*pedro = info->pedro;
	pedro_t	*buf;
	int		start_point = get_pedro_size(pedro) - count;
	if (pedro == NULL || start_point < 0)
		return ;
	while (start_point-- > 0 && pedro->next) {
		pedro = pedro->next;
	}
	if (pedro == NULL)
		return ;
	buf = pedro->next;
	pedro->next = NULL;
	pedro = buf;
	while (pedro->next) {
		if (pedro->img)
			pedro->img->enabled = false;
		mlx_delete_image(info->mlx, pedro->img);
		buf = pedro;
		pedro = pedro->next;
		free(buf);
	}
	if (pedro->img)
		pedro->img->enabled = false;
	mlx_delete_image(info->mlx, pedro->img);
	buf = pedro;
	free(buf);
}
