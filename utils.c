/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 15:14:21 by maboye            #+#    #+#             */
/*   Updated: 2019/07/29 18:36:05 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int				ft_isblank(int c)
{
	return (c == ' ' || c == '\t');
}

int				ft_ishexa(int c)
{
	return (ft_isdigit(c)
		|| (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'));
}

t_point			**fdf_mapdup(t_fdf *data, t_point **map)
{
	t_point	**save;
	int		i;
	int		j;

	if (!((save = (t_point **)malloc(sizeof(t_point *) * data->map_haut))))
		return (NULL);
	i = -1;
	while (++i < data->map_haut)
	{
		j = -1;
		if (!(save[i] = (t_point *)malloc(sizeof(t_point)
		* data->map_larg)))
			return (NULL);
		while (++j < data->map_larg)
		{
			save[i][j].x = map[i][j].x;
			save[i][j].y = map[i][j].y;
			save[i][j].z = map[i][j].z;
			save[i][j].az = map[i][j].az;
			save[i][j].hexa = NULL;
			if (map[i][j].hexa)
				save[i][j].hexa = ft_strdup(map[i][j].hexa);
		}
	}
	return (save);
}

void			ft_free_map(t_fdf *data, t_point **map)
{
	int	i;
	int	j;

	i = -1;
	while (++i < data->map_haut)
	{
		j = -1;
		while (++j < data->map_larg)
			if (map[i][j].hexa)
				ft_strdel(&(map[i][j].hexa));
		free((void *)map[i]);
		map[i] = NULL;
	}
	free((void **)map);
	map = NULL;
}

void			ft_freestruct(t_fdf **data)
{
	if (data && *data)
	{
		if ((*data)->map)
			ft_free_map(*data, (*data)->map);
		if ((*data)->save)
			ft_free_map(*data, (*data)->save);
		if ((*data)->img)
		{
			if ((*data)->img->add)
				ft_memdel((void *)&(*data)->img->add);
			free((void *)(*data)->img);
			(*data)->img = NULL;
		}
		free((void *)*data);
		*data = NULL;
	}
}
