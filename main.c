/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 16:10:01 by maboye            #+#    #+#             */
/*   Updated: 2019/06/18 20:42:25 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void				print_struct(t_fdf *data)
{
	int		i;
	int		j;
	t_point **map;

	map = data->map;
	i = -1;
	while (++i < data->map_haut)
	{
		j = -1;
		while (++j < data->map_larg)
			ft_printf(1, "%d ", data->map[i][j].z);
		ft_putchar('\n');
	}
}

int					main(int ac, char **av)
{
	t_fdf	*data;

	if (ac == 2 && *av[1])
	{
		if (!(data = malloc(sizeof(t_fdf))))
			return (my_putendl_fd("fdf: error: malloc", 2));
		ft_bzero(data, sizeof(data));
		if (!ft_parser(av[1], data))
		{
			free((void *)data);
			return (my_putendl_fd("fdf: error: invalid map", 2));
		}
		if (!(struct_maker(av[1], &data)))
			return (my_putendl_fd("fdf: error: struct failed", 2));
		//print_struct(data);
		fdf(data);
		ft_freestruct(&data);
	}
	else
		ft_putendl("fdf: usage: ./fdf [ valid_map.txt ]");
	return (0);
}
