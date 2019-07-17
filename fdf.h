/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 16:10:22 by maboye            #+#    #+#             */
/*   Updated: 2019/07/17 08:08:02 by maboye           ###   ########.fr       */
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

# define WIN_L	800
# define WIN_H	600

# define DOWN	125
# define LEFT	123
# define RIGHT	124
# define UP		126
# define LESS	78
# define MORE	69
# define HLESS	84
# define HMORE	82
# define XLESS	86
# define XMORE	89
# define YLESS	88
# define YMORE	92
# define ZLESS	83
# define ZMORE	87
# define ESC	53
# define CLEAR	71

typedef struct	s_img
{
	int			*add;
	int			bpp;
	int			size_line;
	int			endian;
	char		*save;
}				t_img;


typedef struct	s_point
{
	float		x;
	float		y;
	float		z;
	char		*hexa;
}				t_point;

typedef struct	s_fdf
{
	int			map_larg;
	int			map_haut;
	int			esp;
	int			zoom;
	long		center;
	float		angle;
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	t_point		**map;
	t_img		*img;
}				t_fdf;

int				deal_key(int key, void *param);
void			fdf(t_fdf **data);
void			fdf_bresenham(t_fdf *data, t_point *first, t_point *second);
char			*fdf_parser(char *input, t_fdf *data);
void        	fdf_rotation(t_fdf *data, int key);
int				fdf_struct_maker(char **input, t_fdf **data);
void			fdf_struct_to_image(t_fdf *data);

long			ft_atoi_base(const char *str, unsigned int base);
void			ft_freestruct(t_fdf **data);
long			ft_isabsolute(long c);
int				ft_isblank(int c);
int				ft_ishexa(int c);

#endif
