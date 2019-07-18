/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 16:10:01 by maboye            #+#    #+#             */
/*   Updated: 2019/07/18 09:35:46 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
		fdf(&data);
	}
	else
		ft_putendl("fdf: usage: ./fdf [ valid_map ]");
	return (0);
}
