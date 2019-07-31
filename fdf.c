/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 19:04:26 by maboye            #+#    #+#             */
/*   Updated: 2019/07/30 20:38:43 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_img		*fdf_new_image(t_fdf *data)
{
	t_img	*img;

	if (!(img = (t_img *)ft_memalloc(sizeof(t_img))))
		return (NULL);
	data->img_ptr = mlx_new_image(data->mlx_ptr, WIN_L, WIN_H);
	img->add = (int *)mlx_get_data_addr(data->img_ptr,
		&(img->bpp), &(img->size_line), &(img->endian));
	return (img);
}

static void			fdf_draw_menu(t_fdf *d)
{
	mlx_string_put(d->mlx_ptr, d->win_ptr, WIN_L + 1, 1, 0xFFFFFF, "1: Z +");
	mlx_string_put(d->mlx_ptr, d->win_ptr, WIN_L + 1, 31, 0xFFFFFF, "5: Z -");
	mlx_string_put(d->mlx_ptr, d->win_ptr, WIN_L + 1, 61, 0xFFFFFF, "7: X +");
	mlx_string_put(d->mlx_ptr, d->win_ptr, WIN_L + 1, 91, 0xFFFFFF, "4: X -");
	mlx_string_put(d->mlx_ptr, d->win_ptr, WIN_L + 1, 121, 0xFFFFFF, "8: Y +");
	mlx_string_put(d->mlx_ptr, d->win_ptr, WIN_L + 1, 151, 0xFFFFFF, "9: Y -");
	mlx_string_put(d->mlx_ptr, d->win_ptr, WIN_L + 1, 181, 0xFFFFFF, "0: H-");
	mlx_string_put(d->mlx_ptr, d->win_ptr, WIN_L + 1, 211, 0xFFFFFF, "2: H+");
	mlx_string_put(d->mlx_ptr, d->win_ptr, WIN_L + 1, 241, 0xFFFFFF, "+: Zoom");
	mlx_string_put(d->mlx_ptr, d->win_ptr, WIN_L + 1, 271, 0xFFFFFF, "-: Zoom");
	mlx_string_put(d->mlx_ptr, d->win_ptr, WIN_L + 1, 301, 0xFFFFFF, "right");
	mlx_string_put(d->mlx_ptr, d->win_ptr, WIN_L + 1, 331, 0xFFFFFF, "left");
	mlx_string_put(d->mlx_ptr, d->win_ptr, WIN_L + 1, 361, 0xFFFFFF, "up");
	mlx_string_put(d->mlx_ptr, d->win_ptr, WIN_L + 1, 391, 0xFFFFFF, "down");
	mlx_string_put(d->mlx_ptr, d->win_ptr, WIN_L + 1, 421, 0xFFFFFF, "clear");
	mlx_string_put(d->mlx_ptr, d->win_ptr, WIN_L + 1, 451, 0xFFFFFF, "=: mid");
	mlx_string_put(d->mlx_ptr, d->win_ptr, WIN_L + 1, 481, 0xFFFFFF, "esc");
	mlx_string_put(d->mlx_ptr, d->win_ptr, WIN_L + 1, 511, 0xFFFFFF, "p: para");
}

void				fdf_struct_to_image(t_fdf *data)
{
	int		i;
	int		j;

	ft_bzero(data->img->add, WIN_L * WIN_H * 4);
	i = -1;
	while (++i < data->map_haut)
	{
		j = -1;
		while (++j < data->map_larg)
		{
			if (j > 0)
				fdf_bresenham(data, &data->map[i][j - 1], &data->map[i][j]);
			if (i > 0)
				fdf_bresenham(data, &data->map[i - 1][j], &data->map[i][j]);
		}
	}
	fdf_draw_menu(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0, 0);
}

int					fdf(t_fdf **data)
{
	if (!((*data)->mlx_ptr = mlx_init()))
		return (0);
	if (!((*data)->win_ptr = mlx_new_window((*data)->mlx_ptr,
	WIN_M, WIN_H, "maboye fdf")))
		return (0);
	if (!((*data)->img = fdf_new_image(*data)))
		return (0);
	fdf_rotation(*data, 0);
	(*data)->zcount = 0;
	if (!(mlx_hook((*data)->win_ptr, 2, 0, deal_key, *data)))
		return (0);
	if (!(mlx_loop((*data)->mlx_ptr)))
		return (0);
	return (1);
}
