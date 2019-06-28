/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 16:10:22 by maboye            #+#    #+#             */
/*   Updated: 2019/06/22 16:12:56 by maboye           ###   ########.fr       */
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

# define WIN_L	2400
# define WIN_H	1200
# define WIN_C	WIN_L * WIN_H * 2

typedef struct	s_img
{
	int			*add;
	int			bpp;
	int			size_line;
	int			endian;
}				t_img;


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
	int			start_x;
	int			start_y;
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	t_point		**map;
	t_img		*img;
}				t_fdf;

void			fdf(t_fdf **data);
void			ft_freestruct(t_fdf **data);
int				ft_isblank(int c);
int				ft_ishexa(int c);
char			*ft_parser(char *input, t_fdf *data);
int				struct_maker(char **input, t_fdf **data);

#endif
