/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 16:10:01 by maboye            #+#    #+#             */
/*   Updated: 2019/07/30 18:01:42 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void				ft_one_helper(t_fdf *data, t_point *first, t_point *second)
{
	data->e = data->dy;
	data->dy = data->e * 2;
	data->dx *= 2;
	while (1)
	{
		fdf_putpixel(data, first, second);
		if (++data->y1 == data->y2)
			break ;
		data->e += data->dx;
		if (data->e <= 0)
		{
			--data->x1;
			data->e += data->dy;
		}
	}
}

static void			fdf_get_scale(t_fdf *data)
{
	float	diff;
	int		i;

	diff = data->max_z - data->min_z;
	i = -1;
	while (++i < 10)
		if (i && i < 10)
			data->scale[i] = diff / 10 * i;
}

int					main(int ac, char **av)
{
	t_fdf	*data;
	char	*input;

	if (ac == 2 && *av[1])
	{
		if (!(data = (t_fdf *)ft_memalloc(sizeof(t_fdf))))
			return (my_putendl_fd("fdf: error", 2));
		if (!(input = fdf_parser(av[1], data)))
		{
			free((void *)data);
			return (my_putendl_fd("fdf: error: invalid map", 2));
		}
		if (!(fdf_struct_maker(&input, &data)))
			return (my_putendl_fd("fdf: error", 2));
		fdf_get_scale(data);
		fdf(&data);
		return (0);
	}
	else
		return (my_putendl_fd("fdf: usage: ./fdf [ valid_map ]", 1));
}
