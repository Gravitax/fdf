/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 15:55:45 by maboye            #+#    #+#             */
/*   Updated: 2019/07/30 15:17:50 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		fdf_translation(t_fdf *data, int key)
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

static void		fdf_zoom(t_fdf *data, int key)
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

static int		fdf_resetmap(t_fdf *data, int key)
{
	int	i;
	int	j;

	ft_free_map(data, data->map);
	if (!(data->map = fdf_mapdup(data, data->save)))
		deal_key(53, data);
	data->zcount = 0;
	if (key == 0)
	{
		i = -1;
		while (++i < data->map_haut)
		{
			j = -1;
			while (++j < data->map_larg)
			{
				data->map[i][j].za = data->map[i][j].zsave;
				data->save[i][j].za = data->map[i][j].zsave;
			}
		}
		data->mid_x = WIN_L / 2;
		data->mid_y = WIN_H / 2;
		data->height = data->esp / 2;
		fdf_rotation(data, 0);
	}
	return (1);
}

static void		fdf_height(t_fdf *data, int key)
{
	int	i;
	int	j;

	i = -1;
	if (fdf_resetmap(data, 1) && key == PARA)
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
			data->map[i][j].z ? data->map[i][j].z += data->height : 0;
			if (data->map[i][j].za)
			{
				data->map[i][j].za += (key == HLESS ? 0.99 : -0.99);
				data->save[i][j].za += (key == HLESS ? 0.99 : -0.99);
			}
		}
	}
	fdf_rotation(data, 0);
}

int				deal_key(int key, void *param)
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
	return (1);
}
