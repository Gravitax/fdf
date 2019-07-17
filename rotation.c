/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 03:28:08 by maboye            #+#    #+#             */
/*   Updated: 2019/07/17 09:35:46 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		fdf_center(t_fdf *data)
{
	long	A;
	long	B;
	long	C;

	A = (long)data->map[0][0].x + (long)data->map[0][0].y * WIN_L;
	B = (long)data->map[0][data->map_larg].x
		+ (long)data->map[0][data->map_larg].y * WIN_L;
	C = (long)data->map[data->map_haut - 1][0].x
		+ (long)data->map[data->map_haut - 1][0].y * WIN_L;
	data->center = ((C - A) / 2) + ((B - A) / 2);
	printf("center: %ld\n", data->center);
	data->center += ft_isabsolute(A);
	data->center = (WIN_L / 2) * (WIN_H / 2) - data->center;
}

static void		fdf_rotation_maker(t_fdf *data, int i, int j, int key)
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
		data->map[i][j].y = ry * cos(data->angle) + rz * sin(data->angle);
		data->map[i][j].z = -ry * sin(data->angle) + rz * cos(data->angle);
	}
}

static void		fdf_isometric_projection(t_fdf *data, int i, int j)
{
	float	ix;
    float 	iy;

	ix = data->map[i][j].x;
	iy = data->map[i][j].y;
	data->map[i][j].x = (ix - iy) * cos(data->angle);
	data->map[i][j].y = -data->map[i][j].z + (ix + iy) * sin(data->angle);
}

void            fdf_rotation(t_fdf *data, int key)
{
    int i;
    int j;

	data->angle = key ? 0.25 : 0.523599;
	if (key == XLESS || key == YLESS || key == ZLESS)
		data->angle = -data->angle;
    i = -1;
    while (++i < data->map_haut)
    {
        j = -1;
        while (++j < data->map_larg)
        {
            if (key)
                fdf_rotation_maker(data, i ,j, key);
            else
                fdf_isometric_projection(data, i, j);
        }
    }
	fdf_center(data);
	fdf_struct_to_image(data);
}
