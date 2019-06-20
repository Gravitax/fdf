/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 19:04:26 by maboye            #+#    #+#             */
/*   Updated: 2019/06/20 20:32:16 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//https://en.wikipedia.org/wiki/Xiaolin_Wu%27s_line_algorithm
//https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm

//https://forum.intra.42.fr/topics/16245/messages
//https://forum.intra.42.fr/topics/19254/messages

int					deal_key(int key, void *param)
{
	t_fdf 	*data;

	data = (t_fdf *)param;
	if (key == 53)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		ft_freestruct(&data);
		exit(EXIT_SUCCESS);
	}
	if (key == 12)
		mlx_clear_window(data->mlx_ptr, data->win_ptr);
	else
		ft_putnbr(key);
	return (1);
}

void				ft_printmap(t_fdf *data)
{
	t_point	**map;
	int		i;
	int		j;
	int		h;
	int		l;

	map = data->map;
	h = 0;
	i = -1;
	while (++i < data->map_haut)
	{
		l = 0;
		j = -1;
		while (++j < data->map_larg)
		{
			map[i][j].x += (WIN_L / data->map_larg) / 4;
			map[i][j].y += (WIN_H / data->map_haut) / 4;
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, map[i][j].x + l, map[i][j].y + h, 0xFFFFFF);
			int test = (WIN_L / data->map_larg) / 4;
			while (++test < l + data->map_larg + WIN_L / data->map_larg / 4)
				mlx_pixel_put(data->mlx_ptr, data->win_ptr, test, map[i][j].y + h, 0xFFFFFF);
			int test2 = (WIN_H / data->map_haut) / 4;
			while (++test2 < h + data->map_haut + WIN_H / data->map_haut / 4)
				mlx_pixel_put(data->mlx_ptr, data->win_ptr, map[i][j].x + l, test2, 0xFFFFFF);
			l += WIN_L / data->map_larg;
		}
		h += WIN_H / data->map_haut;
	}
}

t_img				*ft_new_image(t_fdf *data)
{
	t_img	*img;

	if (!(img = (t_img*)malloc(sizeof(t_img))))
		return (NULL);
	img->img = mlx_new_image(data->mlx_ptr, WIN_H, WIN_L);
	img->data = mlx_get_data_addr(img->img, &(img->bpp), &(img->size_line), &(img->endian));
	ft_printf(1, "bpp: %d, size_line: %d, endian: %d\n", img->bpp, img->size_line, img->endian);
	printf("str: %d\n", (int *)img->data);
	return (img);
}

void				fdf(t_fdf **data)
{
	t_img	*img;

	(*data)->mlx_ptr = mlx_init();
	img = ft_new_image(*data);
	(*data)->win_ptr = mlx_new_window((*data)->mlx_ptr, WIN_L, WIN_H, "maboye fdf");
	ft_printmap(*data);
	mlx_key_hook((*data)->win_ptr, deal_key, *data);
	mlx_loop((*data)->mlx_ptr);
	ft_strdel(&img->data);
	ft_memdel((void **)&img);
	//mlx_destroy_image((*data)->mlx_ptr, (*data)->img_ptr);
}
