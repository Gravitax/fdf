/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 21:13:22 by maboye            #+#    #+#             */
/*   Updated: 2019/06/18 20:38:05 by maboye           ###   ########.fr       */
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
			{
				ft_freestruct(&data);
				return (-1);
			}
			return (1);
		}
	return (0);
}

static int		copyin_struct(t_fdf *data, char **stock, int i)
{
	int		j;

	if (!(data->map[i] = (t_point *)malloc(sizeof(t_point)
					* ft_tablen((void **)stock))))
	{
		ft_freestruct(&data);
		return (0);
	}
	j = -1;
	while (stock && stock[++j])
	{
		data->map[i][j].x = i;
		data->map[i][j].y = j;
		data->map[i][j].z = ft_atoi(stock[j]);
		data->map[i][j].hexa = NULL;
		if ((data->map[i][j].token = stock_hexa(data, stock[j], i, j)) == -1)
			return (0);
		//data->map[i][j].hexa ? puts(data->map[i][j].hexa) : 0;
	}
	return (1);
}

static int		ft_copymap(char *input, t_fdf *data, char **stock)
{
	char	*line;
	int		file;
	int		ret;
	int		i;

	i = -1;
	if (!(data->map = (t_point **)malloc(sizeof(t_point *) * data->map_haut)))
		return (0);
	file = open(input, O_RDONLY);
	while ((ret = get_next_line(file, &line)))
	{
		if (ret == -1 || !(stock = ft_splitwspc(line))
				|| !copyin_struct(data, stock, ++i))
		{
			stock ? ft_tabfree((void **)stock) : 0;
			ft_strdel(&line);
			close(file);
			return (0);
		}
		ft_tabfree((void **)stock);
		ft_strdel(&line);
	}
	close(file);
	return (1);
}

int				struct_maker(char *input, t_fdf **data)
{
	return (ft_copymap(input, *data, NULL));
}
