/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 21:13:53 by maboye            #+#    #+#             */
/*   Updated: 2019/06/20 18:49:12 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int			backline_handler(t_fdf *data, char *file, int *tmp)
{
	if (data->map_larg)
	{
		if (data->map_larg != *tmp)
		{
			ft_strdel(&file);
			return (0);
		}
	}
	else
		data->map_larg = *tmp;
	++data->map_haut;
	*tmp = 0;
	return (1);
}

static int			check_hexa(char *file, int *i)
{
	int		x;
	char	*str;

	str = file + *i + 1;
	if (ft_strncmp(str, "0x", 3))
	{
		str += 2;
		x = -1;
		while (str && str[++x] && x < 6)
			if (!ft_ishexa(str[x]))
				return (0);
		if (ft_isblank(str[x]))
		{
			*(i) += 9;
			return (1);
		}
	}
	return (0);
}

static int			check_digit(t_fdf *data, char *file, int *i)
{
	if (file[*i] == '+' || file[*i] == '-')
		++(*i);
	if (file[*i] != '\n' && !ft_isdigit(file[*i]))
	{
		ft_strdel(&file);
		return (0);
	}
	while (ft_isdigit(file[*i]))
		++(*i);
	if (file[*i] == ',')
		if (!check_hexa(file, i))
		{
			ft_strdel(&file);
			return (0);
		}
	if (!ft_isblank(file[*i]) && file[*i] != '\0' && file[*i] != '\n')
	{
		ft_strdel(&file);
		return (0);
	}
	if (!file[(*i)--])
		++data->map_haut;
	return (1);
}

char				*check_file(t_fdf *data, char *file, int tmp)
{
	if (tmp)
		if (data->map_larg != tmp)
			ft_strdel(&file);
	if (!data->map_larg)
		ft_strdel(&file);
	return (file);
}

char				*ft_parser(char *input, t_fdf *data)
{
	char	*file;
	int		i;
	int		tmp;

	if (!(file = ft_readfile(input)))
		return (NULL);
	tmp = 0;
	i = -1;
	while (file && file[++i])
	{
		if (ft_isblank(file[i]))
			continue ;
		if (file[i] == '\n')
		{
			if (!backline_handler(data, file, &tmp))
				return (NULL);
			continue ;
		}
		if (!check_digit(data, file, &i))
			return (NULL);
		++tmp;
	}
	return (check_file(data, file, tmp));
}
