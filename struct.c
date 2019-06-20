/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 21:13:22 by maboye            #+#    #+#             */
/*   Updated: 2019/06/20 18:49:14 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int		stock_hexa(t_fdf *data, char *str, int i, int j)
{
	if ((int)ft_strlen(str) > ft_intlen(data->map[i][j].z))
		if (*(str + (int)ft_intlen(data->map[i][j].z)) == ',')
		{
			if (!(data->map[i][j].hexa = ft_strdup(str
			+ (int)ft_intlen(data->map[i][j].z) + 1)))
				return (-1);
			return (1);
		}
	return (0);
}

static int		copyin_struct(t_fdf *data, char **stock, int i)
{
	int		j;

	if (!(data->map[i] = (t_point *)malloc(sizeof(t_point)
					* ft_tablen((void **)stock))))
		return (0);
	j = -1;
	while (stock && stock[++j])
	{
		data->map[i][j].x = j;
		data->map[i][j].y = i;
		data->map[i][j].z = ft_atoi(stock[j]);
		data->map[i][j].hexa = NULL;
		if ((data->map[i][j].token = stock_hexa(data, stock[j], i, j)) == -1)
			return (0);
	}
	return (1);
}

static char		*line_handler(char **input, int choose)
{
	int		i;
	char	*tmp;

	if (choose)
	{
		while (*input && **input && **input != '\n')
			++(*input);
		if (*input && **input && **input == '\n')
			++(*input);
		return (NULL);
	}
	tmp = *input;
	i = -1;
	while (tmp && tmp[++i] && tmp[i] != '\n')
		;
	return (ft_strsub(tmp, 0, i));
}

static int		clean_exit(t_fdf **data, char **stock, char **input, char *line)
{
	data ? ft_freestruct(data) : 0;
	stock ? ft_tabfree((void **)stock) : 0;
	input ? ft_strdel(input) : 0;
	line ? ft_strdel(&line) : 0;
	return (0);
}

int				struct_maker(char **input, t_fdf **data)
{
	char	**stock;
	char	*line;
	char	*tmp;
	int		i;

	if (!((*data)->map = (t_point **)malloc(sizeof(t_point *)
	* (*data)->map_haut)))
		return (clean_exit(data, NULL, input, NULL));
	stock = NULL;
	tmp = *input;
	i = -1;
	while (++i < (*data)->map_haut)
	{
		if (!(line = line_handler(&tmp, 0)))
			return (clean_exit(data, NULL, input, NULL));
		line_handler(&tmp, 1);
		if (!(stock = ft_splitwspc(line)) || !(copyin_struct(*data, stock, i)))
			return (clean_exit(data, stock, input, line));
		ft_tabfree((void **)stock);
		ft_strdel(&line);
	}
	ft_strdel(input);
	return (1);
}
