/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 21:13:53 by maboye            #+#    #+#             */
/*   Updated: 2019/07/29 18:00:32 by maboye           ###   ########.fr       */
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
		if (ft_isblank(str[x]) || str[x] == '\n' || str[x] == '\0')
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

static char			*check_file(t_fdf *data, char *file, int tmp)
{
	if (tmp)
		if (data->map_larg != tmp)
			ft_strdel(&file);
	if (!data->map_larg)
		ft_strdel(&file);
	if (file)
	{
		if (WIN_L / data->map_larg < WIN_H / data->map_haut)
			data->esp = WIN_L / data->map_larg;
		else
			data->esp = WIN_H / data->map_haut;
		data->esp /= 2;
		data->height = data->esp / 2;
		data->mid_x = WIN_L / 2;
		data->mid_y = WIN_H / 2;
	}
	return (file);
}

char				*fdf_parser(char *input, t_fdf *data)
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
