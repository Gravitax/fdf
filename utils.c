/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 15:14:21 by maboye            #+#    #+#             */
/*   Updated: 2019/07/17 08:07:52 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

long			ft_isabsolute(long c)
{
	return (c < 0 ? -c : c);
}

int				ft_isblank(int c)
{
	return (c == ' ' || c == '\t');
}

int				ft_ishexa(int c)
{
	return (ft_isdigit(c)
		|| (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'));
}

static void		free_map(t_fdf **data)
{
	int	i;
	int	j;

	i = -1;
	while (++i < (*data)->map_haut)
	{
		j = -1;
		while (++j < (*data)->map_larg)
			if ((*data)->map[i][j].hexa)
				ft_strdel(&(*data)->map[i][j].hexa);
		free((void *)(*data)->map[i]);
	}
	free((void *)(*data)->map);
}

void			ft_freestruct(t_fdf **data)
{
	if (data && *data)
	{
		if ((*data)->map)
			free_map(data);
		if ((*data)->img)
		{
			if ((*data)->img->add)
				ft_memdel((void *)&(*data)->img->add);
			free((void *)(*data)->img);
		}
		free((void *)*data);
		*data = NULL;
	}
}
