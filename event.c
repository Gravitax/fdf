/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 15:55:45 by maboye            #+#    #+#             */
/*   Updated: 2019/07/17 06:54:40 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void        fdf_translation(t_fdf *data, int key)
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
			if (key == UP)
				data->map[i][j].y -= esp;
			if (key == DOWN)
				data->map[i][j].y += esp;
			if (key == LEFT)
				data->map[i][j].x -= esp;
			if (key == RIGHT)
				data->map[i][j].x += esp;
		}
	}
	fdf_struct_to_image(data);
}

void        fdf_zoom(t_fdf*data, int key)
{
	(void)data;
	(void)key;	
}

void		fdf_height(t_fdf *data, int key)
{
	(void)data;
	(void)key;
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
		mlx_clear_window(data->mlx_ptr, data->win_ptr);
	if (key == XLESS || key == XMORE || key == YLESS
	|| key == XMORE || key == ZLESS || key == ZMORE)
		fdf_rotation(data, key);
	if (key == LEFT || key == RIGHT || key == DOWN || key == UP)
		fdf_translation(data, key);
	if (key == MORE || key == LESS)
		fdf_zoom(data, key);
	if (key == HMORE || key == HLESS)
		fdf_height(data, key);
	ft_printf(1, "key: %d\n", key);
	return (1);
}
