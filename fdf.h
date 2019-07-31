/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 16:10:22 by maboye            #+#    #+#             */
/*   Updated: 2019/07/30 20:30:55 by maboye           ###   ########.fr       */
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
# define WIN_M	WIN_L + 300

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
# define CENTER	81
# define CLEAR	71
# define ESC	53
# define PARA	35

typedef struct	s_img
{
	int			*add;
	int			bpp;
	int			size_line;
	int			endian;
}				t_img;

typedef struct	s_point
{
	float		x;
	float		y;
	float		z;
	float		za;
	float		zsave;
	char		*hexa;
	int			color;
}				t_point;

typedef struct	s_fdf
{
	int			x1;
	int			y1;
	int			x2;
	int			y2;
	int			i;
	int			map_larg;
	int			map_haut;
	float		angle;
	float		height;
	float		esp;
	float		mid_x;
	float		mid_y;
	float		min_z;
	float		max_z;
	float		scale[9];
	int			zcount;
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	t_point		**map;
	t_point		**save;
	t_img		*img;
}				t_fdf;

int				deal_key(int key, void *param);
int				fdf(t_fdf **data);
void			fdf_bresenham(t_fdf *data, t_point *first, t_point *second);
t_point			**fdf_mapdup(t_fdf *data, t_point **map);
char			*fdf_parser(char *input, t_fdf *data);
void			fdf_putpixel(t_fdf *data, t_point *first, t_point *second);
void			fdf_rotation(t_fdf *data, int key);
int				fdf_struct_maker(char **input, t_fdf **data);
void			fdf_struct_to_image(t_fdf *data);

long			ft_atoi_base(const char *str, unsigned int base);
void			ft_freestruct(t_fdf **data);
void			ft_free_map(t_fdf *data, t_point **map);
int				ft_isblank(int c);
int				ft_ishexa(int c);

void			ft_one_helper(t_fdf *data, t_point *first, t_point *second);

#endif
