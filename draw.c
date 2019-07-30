/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 16:04:39 by maboye            #+#    #+#             */
/*   Updated: 2019/07/30 18:02:18 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		ft_one(t_fdf *data, t_point *first, t_point *second)
{
	if (-data->dx >= data->dy)
	{
		data->e = data->dx;
		data->dx = data->e * 2;
		data->dy *= 2;
		while (1)
		{
			fdf_putpixel(data, first, second);
			if (--data->x1 == data->x2)
				break ;
			data->e += data->dy;
			if (data->e >= 0)
			{
				++data->y1;
				data->e += data->dx;
			}
		}
	}
	else
	{
		ft_one_helper(data, first, second);
	}
}

static void		ft_two_helper(t_fdf *data, t_point *first, t_point *second)
{
	data->e = data->dy;
	data->dy = data->e * 2;
	data->dx *= 2;
	while (1)
	{
		fdf_putpixel(data, first, second);
		if (--data->y1 == data->y2)
			break ;
		data->e -= data->dx;
		if (data->e >= 0)
		{
			--data->x1;
			data->e += data->dy;
		}
	}
}

static void		ft_two(t_fdf *data, t_point *first, t_point *second)
{
	if (data->dx <= data->dy)
	{
		data->e = data->dx;
		data->dx = data->e * 2;
		data->dy *= 2;
		while (1)
		{
			fdf_putpixel(data, first, second);
			if (--data->x1 == data->x2)
				break ;
			data->e -= data->dy;
			if (data->e >= 0)
			{
				--data->y1;
				data->e += data->dx;
			}
		}
	}
	else
		ft_two_helper(data, first, second);
}

static void		ft_first(t_fdf *data, t_point *first, t_point *second)
{
	data->dy = data->y2 - data->y1;
	if (data->dy)
	{
		if (data->dy > 0)
		{
			ft_one(data, first, second);
		}
		else
		{
			ft_two(data, first, second);
		}
	}
	else
		while (data->x1 != data->x2)
		{
			fdf_putpixel(data, first, second);
			--data->x1;
		}
}

void			fdf_draw(t_fdf *data, t_point *first, t_point *second)
{
	if (data->dx > 0)
	{
		if (data->dy)
		{
			fdf_drawsec(data, first, second);
		}
		else
			while (data->x1 != data->x2)
			{
				fdf_putpixel(data, first, second);
				++data->x1;
			}
	}
	else
	{
		ft_first(data, first, second);
	}
}
