/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 03:28:08 by maboye            #+#    #+#             */
/*   Updated: 2019/07/29 18:35:12 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		fdf_center(t_fdf *data)
{
	float	mx;
	float	my;
	int		i;
	int		j;

	mx = (data->map[0][data->map_larg - 1].x
			+ data->map[data->map_haut - 1][0].x) / 2;
	my = (data->map[0][data->map_larg - 1].y
			+ data->map[data->map_haut - 1][0].y) / 2;
	mx = data->mid_x - mx;
	my = data->mid_y - my;
	i = -1;
	while (++i < data->map_haut)
	{
		j = -1;
		while (++j < data->map_larg)
		{
			data->map[i][j].x += mx;
			data->map[i][j].y += my;
		}
	}
}

static void		fdf_rotation_maker(t_fdf *data, int key, int i, int j)
{
	float	rx;
	float	ry;
	float	rz;

	rx = data->map[i][j].x;
	ry = data->map[i][j].y;
	rz = data->map[i][j].z;
	if (key == YLESS || key == YMORE)
	{
		data->map[i][j].x = rx * cos(data->angle) + rz * sin(data->angle);
		data->map[i][j].z = -rx * sin(data->angle) + rz * cos(data->angle);
	}
	else if (key == ZLESS || key == ZMORE)
	{
		data->map[i][j].x = rx * cos(data->angle) - ry * sin(data->angle);
		data->map[i][j].y = rx * sin(data->angle) + ry * cos(data->angle);
	}
	else
	{
		data->map[i][j].y = ry * cos(data->angle) - rz * sin(data->angle);
		data->map[i][j].z = ry * sin(data->angle) + rz * cos(data->angle);
	}
}

static void		fdf_isometric_projection(t_fdf *data)
{
	float	ix;
	float	iy;
	int		i;
	int		j;

	i = -1;
	while (++i < data->map_haut)
	{
		j = -1;
		while (++j < data->map_larg)
		{
			ix = data->map[i][j].x;
			iy = data->map[i][j].y;
			data->map[i][j].x = (ix - iy) * cos(0.523599);
			data->map[i][j].y = -data->map[i][j].z
				+ (ix + iy) * sin(0.523599);
		}
	}
}

static void		fdf_movehandler(t_fdf *data, int key)
{
	if (key == -2)
	{
		fdf_center(data);
		return ;
	}
	if (key == -1)
	{
		data->mid_x = WIN_L / 2;
		data->mid_y = WIN_H / 2;
	}
	if (key == 0)
	{
		if (!data->save)
			data->save = fdf_mapdup(data, data->map);
		fdf_isometric_projection(data);
	}
	fdf_center(data);
	fdf_struct_to_image(data);
}

void			fdf_rotation(t_fdf *data, int key)
{
	int i;
	int j;

	if (key < 1)
	{
		fdf_movehandler(data, key);
		return ;
	}
	if (key == XMORE || key == YMORE || key == ZMORE)
		data->angle = 0.261799;
	if (key == XLESS || key == YLESS || key == ZLESS)
		data->angle = -0.261799;
	i = -1;
	while (++i < data->map_haut)
	{
		j = -1;
		while (++j < data->map_larg)
			fdf_rotation_maker(data, key, i, j);
	}
	fdf_center(data);
	fdf_struct_to_image(data);
}
