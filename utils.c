/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 15:14:21 by maboye            #+#    #+#             */
/*   Updated: 2019/06/20 18:49:15 by maboye           ###   ########.fr       */
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

void			ft_freestruct(t_fdf **data)
{
	int		i;
	int		j;

	if (data && *data)
	{
		if ((*data)->map)
		{
			i = -1;
			while (++i < (*data)->map_haut)
			{
				j = -1;
				while (++j < (*data)->map_larg)
					if ((*data)->map[i][j].token)
						ft_strdel(&(*data)->map[i][j].hexa);
				free((void *)(*data)->map[i]);
			}
			free((void *)(*data)->map);
		}
		free((void *)*data);
		*data = NULL;
	}
}
