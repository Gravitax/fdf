/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 19:04:26 by maboye            #+#    #+#             */
/*   Updated: 2019/07/17 07:57:16 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_img				*fdf_new_image(t_fdf *data)
{
	t_img	*img;

	if (!(img = (t_img *)ft_memalloc(sizeof(t_img))))
		return (NULL);
	data->img_ptr = mlx_new_image(data->mlx_ptr, WIN_L, WIN_H);
	img->add = (int *)mlx_get_data_addr(data->img_ptr,
		&(img->bpp), &(img->size_line), &(img->endian));
	//ft_printf(1, "bpp: %d, size_line: %d, endian: %d\n", img->bpp, img->size_line, img->endian);
	return (img);
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
			//printf("x: %d y: %d\n",(*data)->map[i][j].x, (*data)->map[i][j].y);
			if (j > 0)
				fdf_bresenham(data, &data->map[i][j - 1], &data->map[i][j]);
			if (i > 0)
				fdf_bresenham(data, &data->map[i - 1][j], &data->map[i][j]);
		}
	}
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0, 0);
}

void				fdf(t_fdf **data)
{
	(*data)->mlx_ptr = mlx_init();
	(*data)->win_ptr = mlx_new_window((*data)->mlx_ptr,
		WIN_L, WIN_H, "maboye fdf");
	(*data)->img = fdf_new_image(*data);
	fdf_rotation(*data, 0);
	mlx_key_hook((*data)->win_ptr, deal_key, *data);
	mlx_loop((*data)->mlx_ptr);
}
