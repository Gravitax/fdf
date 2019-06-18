/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 16:10:22 by maboye            #+#    #+#             */
/*   Updated: 2019/06/18 20:19:26 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <math.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# include "libft/libft.h"

typedef struct	s_point
{
	int			x;
	int			y;
	int			z;
	int			token;
	char		*hexa;
}				t_point;

typedef struct	s_fdf
{
	int			map_larg;
	int			map_haut;
	t_point		**map;
}				t_fdf;

void			ft_freestruct(t_fdf **data);
int				ft_isblank(int c);
int				ft_ishexa(int c);
int				ft_parser(char *input, t_fdf *data);
int				struct_maker(char *input, t_fdf **data);

#endif
