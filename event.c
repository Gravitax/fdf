/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 15:55:45 by maboye            #+#    #+#             */
/*   Updated: 2019/07/29 19:00:22 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		fdf_translation(t_fdf *data, int key)
{
	int		i;
	int		j;
	float	esp;

	esp = WIN_L / 50;
	i = -1;
	while (++i < data->map_haut)
	{
		j = -1;
		while (++j < data->map_larg)
		{
			if (key == UP || key == DOWN)
				data->map[i][j].y = data->map[i][j].y
					+ (key == UP ? -esp : esp);
			if (key == LEFT || key == RIGHT)
				data->map[i][j].x = data->map[i][j].x
					+ (key == LEFT ? -esp : esp);
		}
	}
	if (key == UP || key == DOWN)
		data->mid_y = data->mid_y + (key == UP ? -esp : esp);
	if (key == LEFT || key == RIGHT)
		data->mid_x = data->mid_x + (key == LEFT ? -esp : esp);
	fdf_struct_to_image(data);
}

void		fdf_zoom(t_fdf *data, int key)
{
	int	i;
	int	j;

	data->zcount += (key == LESS ? 1 : -1);
	if (data->zcount < -5 || data->zcount > 10)
	{
		data->zcount = data->zcount < -5 ? -5 : 10;
		return ;
	}
	i = -1;
	while (++i < data->map_haut)
	{
		j = -1;
		while (++j < data->map_larg)
		{
			data->map[i][j].x *= (key == LESS ? 1.5 : 0.65);
			data->map[i][j].y *= (key == LESS ? 1.5 : 0.65);
		}
	}
	fdf_rotation(data, -2);
	fdf_struct_to_image(data);
}

void		fdf_resetmap(t_fdf *data, int key)
{
	ft_free_map(data, data->map);
	if (!(data->map = fdf_mapdup(data, data->save)))
		deal_key(53, data);
	data->zcount = 0;
	if (key == 0)
	{
		data->mid_x = WIN_L / 2;
		data->mid_y = WIN_H / 2;
		data->height = data->esp / 2;
		fdf_rotation(data, 0);
	}
}

void		fdf_height(t_fdf *data, int key)
{
	int	i;
	int	j;

	i = -1;
	fdf_resetmap(data, 1);
	if (key == PARA)
	{
		fdf_rotation(data, -2);
		fdf_struct_to_image(data);
		return ;
	}
	data->height += (key == HLESS ? data->esp : -data->esp) / 2;
	while (++i < data->map_haut)
	{
		j = -1;
		while (++j < data->map_larg)
		{
			if (data->map[i][j].z)
				data->map[i][j].z += data->height;
			if (data->map[i][j].az)
				data->map[i][j].az += data->height;
		}
	}
	fdf_rotation(data, 0);
}

int			deal_key(int key, void *param)
{
	t_fdf	*data;

	data = (t_fdf *)param;
	if (key == ESC)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		ft_freestruct(&data);
		exit(EXIT_SUCCESS);
	}
	if (key == CLEAR)
		fdf_resetmap(data, 0);
	if (key == XLESS || key == XMORE || key == YLESS || key == YMORE
			|| key == XMORE || key == ZLESS || key == ZMORE)
		fdf_rotation(data, key);
	if (key == LEFT || key == RIGHT || key == DOWN || key == UP)
		fdf_translation(data, key);
	if (key == MORE || key == LESS)
		fdf_zoom(data, key);
	if (key == HMORE || key == HLESS || key == PARA)
		fdf_height(data, key);
	if (key == CENTER)
		fdf_rotation(data, -1);
	ft_printf(1, "key: %d\n", key);
	return (1);
}
