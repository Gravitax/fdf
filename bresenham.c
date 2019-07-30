/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 06:21:47 by maboye            #+#    #+#             */
/*   Updated: 2019/07/30 17:43:07 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		fdf_get_color(t_fdf *data, t_point *p)
{
	float	z;

	z = p->za;
	p->color = 0x0000FF;
	if (z > data->scale[7])
		p->color = 0xFFFFFF;
	if (z <= data->scale[7] && z > data->scale[6])
		p->color = 0xC0C0C0;
	if (z <= data->scale[6] && z > data->scale[5])
		p->color = 0x808080;
	if (z <= data->scale[5] && z > data->scale[4])
		p->color = 0xFF0000;
	if (z <= data->scale[4] && z > data->scale[3])
		p->color = 0x800000;
	if (z <= data->scale[3] && z > data->scale[2])
		p->color = 0xFFFF00;
	if (z <= data->scale[2] && z > data->scale[1])
		p->color = 0x808000;
	if (z <= data->scale[1] && z >= data->scale[0])
		p->color = 0x00FF00;
	if (p->hexa)
		p->color = ((int)ft_atoi_base(p->hexa, 16));
}

void			fdf_putpixel(t_fdf *data, t_point *first, t_point *second)
{
	long	pos;

	if (data->x1 < 0 || data->y1 < 0 || data->x1 > WIN_L || data->y1 > WIN_H)
		return ;
	fdf_get_color(data, first->z > second->z ? first : second);
	pos = data->x1 + data->y1 * WIN_L;
	data->img->add[pos] = first->z > second->z ? first->color : second->color;
}

static void		fdf_draw_helper(t_fdf *data, t_point *first, t_point *second)
{
	data->dy = data->y2 - data->y1;
	if (data->dy)
	{
		if (data->dy > 0)
			while (data->y1 != data->y2)
			{
				fdf_putpixel(data, first, second);
				++data->y1;
			}
	}
	else
		while (data->y1 != data->y2)
		{
			fdf_putpixel(data, first, second);
			--data->y1;
		}
}

void			fdf_bresenham(t_fdf *data, t_point *first, t_point *second)
{
	data->x1 = first->x;
	data->y1 = first->y;
	data->x2 = second->x;
	data->y2 = second->y;
	data->dx = data->x2 - data->x1;
	data->dy = data->y2 - data->y1;
	if (data->dx)
	{
		fdf_draw(data, first, second);
	}
	else
	{
		fdf_draw_helper(data, first, second);
	}
}
