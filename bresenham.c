/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 06:21:47 by maboye            #+#    #+#             */
/*   Updated: 2019/07/30 20:41:23 by maboye           ###   ########.fr       */
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

	if (data->x1 < 0 || data->y1 < 0
	|| data->x1 > WIN_L - 1 || data->y1 > WIN_H)
		return ;
	fdf_get_color(data, first->z > second->z ? first : second);
	pos = data->x1 + data->y1 * WIN_L;
	data->img->add[pos] = first->z > second->z ? first->color : second->color;
}

void			fdf_draw_one(t_fdf *data, t_point *p1, t_point *p2, double coef)
{
	t_point	*buf;

	if (p1->x > p2->x)
	{
		buf = p2;
		p2 = p1;
		p1 = buf;
	}
	while (p1->x + data->i <= p2->x)
	{
		data->x1 = p1->x + data->i;
		data->y1 = (int)(p1->y + data->i * coef);
		fdf_putpixel(data, p1, p2);
		++data->i;
	}
}

void			fdf_draw_sec(t_fdf *data, t_point *p1, t_point *p2, double coef)
{
	t_point	*buf;

	coef = 1 / coef;
	if (p1->y > p2->y)
	{
		buf = p2;
		p2 = p1;
		p1 = buf;
	}
	while (p1->y + data->i <= p2->y)
	{
		data->x1 = (int)(p1->x + data->i * coef);
		data->y1 = p1->y + data->i;
		fdf_putpixel(data, p1, p2);
		++data->i;
	}
}

void			fdf_bresenham(t_fdf *data, t_point *p1, t_point *p2)
{
	double	coef;

	data->i = 0;
	if (p2->x == p1->x)
		coef = 1000000;
	else
		coef = (double)(p2->y - p1->y) / (double)(p2->x - p1->x);
	if (coef > -1 && coef < 1)
	{
		fdf_draw_one(data, p1, p2, coef);
	}
	else
	{
		fdf_draw_sec(data, p1, p2, coef);
	}
}
