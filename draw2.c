/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 17:43:32 by maboye            #+#    #+#             */
/*   Updated: 2019/07/30 18:08:44 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		ft_onesechelper(t_fdf *data, t_point *first, t_point *second)
{
	data->e = data->dy;
	data->dy = data->e * 2;
	data->dx *= 2;
	while (1)
	{
		fdf_putpixel(data, first, second);
		if (++data->y1 == data->y2)
			break ;
		data->e -= data->dx;
		if (data->e < 0)
		{
			++data->x1;
			data->e += data->dy;
		}
	}
}

static void		ft_onesec(t_fdf *data, t_point *first, t_point *second)
{
	if (data->dx >= data->dy)
	{
		data->e = data->dx;
		data->dx = data->e * 2;
		data->dy *= 2;
		while (1)
		{
			fdf_putpixel(data, first, second);
			if (++data->x1 == data->x2)
				break ;
			data->e -= data->dy;
			if (data->e < 0)
			{
				++data->y1;
				data->e += data->dx;
			}
		}
	}
	else
	{
		ft_onesechelper(data, first, second);
	}
}

static void		ft_twosechelper(t_fdf *data, t_point *first, t_point *second)
{
	data->e = data->dy;
	data->dy = data->e * 2;
	data->dx *= 2;
	while (1)
	{
		fdf_putpixel(data, first, second);
		if (--data->y1 == data->y2)
			break ;
		data->e += data->dx;
		if (data->e > 0)
		{
			++data->x1;
			data->e += data->dy;
		}
	}
}

static void		ft_twosec(t_fdf *data, t_point *first, t_point *second)
{
	if (data->dx >= -data->dy)
	{
		data->e = data->dx;
		data->dx = data->e * 2;
		data->dy *= 2;
		while (1)
		{
			fdf_putpixel(data, first, second);
			if (++data->x1 == data->x2)
				break ;
			data->e += data->dy;
			if (data->e < 0)
			{
				--data->y1;
				data->e += data->dx;
			}
		}
	}
	else
	{
		ft_twosechelper(data, first, second);
	}
}

void			fdf_drawsec(t_fdf *data, t_point *first, t_point *second)
{
	if (data->dy > 0)
	{
		ft_onesec(data, first, second);
	}
	else
	{
		ft_twosec(data, first, second);
	}
}
