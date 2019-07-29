/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 06:21:47 by maboye            #+#    #+#             */
/*   Updated: 2019/07/29 19:00:21 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int				get_color(t_fdf *data, t_point *first, t_point *second)
{
	float	z;

	z = first->az > second->az ? first->az : second->az;
	if (first->hexa)
		return ((int)ft_atoi_base(first->hexa, 16));
	if (z > data->scale[7])
		return (0xFFFFFF);
	if (z <= data->scale[7] && z > data->scale[6])
		return (0xC0C0C0);
	if (z <= data->scale[6] && z > data->scale[5])
		return (0x808080);
	if (z <= data->scale[5] && z > data->scale[4])
		return (0xFF0000);
	if (z <= data->scale[4] && z > data->scale[3])
		return (0x800000);
	if (z <= data->scale[3] && z > data->scale[2])
		return (0xFFFF00);
	if (z <= data->scale[2] && z > data->scale[1])
		return (0x808000);
	if (z <= data->scale[1] && z >= data->scale[0])
		return (0x00FF00);
	return (0x008000);
}

void			fdf_putpixel(int x, int y, t_fdf *data, int color)
{
	long	pos;

	if (x < 0 || y < 0 || x > WIN_L || y > WIN_H)
		return ;
	pos = (long)x + (long)y * WIN_L;
	data->img->add[pos] = color;
}

void			fdf_bresenham(t_fdf *data, t_point *first, t_point *second)
{
	int		x1;
	int		y1;
	int		x2;
	int		y2;

	x1 = first->x;
	y1 = first->y;
	x2 = second->x;
	y2 = second->y;
	int     dx;
	int     dy;
	int		e;

	dx = x2 - x1;
	dy = y2 - y1;
	if (dx)
	{
		if (dx > 0)
		{
			if (dy)
			{
				if (dy > 0) // vecteur oblique dans le 1er quadran
				{
					if (dx >= dy)  // vecteur diagonal ou oblique proche de l’horizontale, dans le 1er octant
					{
						e = dx;
						dx = e * 2;
						dy *= 2; // e est positif
						while (1) // déplacements horizontaux
						{
							fdf_putpixel(x1, y1, data, get_color(data, first, second));
							if (++x1 == x2)
								break ;
							e -= dy;
							if (e < 0)
							{
								++y1;  // déplacement diagonal
								e += dx;
							}
						}
					}
					else // vecteur oblique proche de la verticale, dans le 2d octant
					{
						e = dy;
						dy = e * 2;
						dx *= 2; // e est positif
						while (1) // déplacements verticaux
						{
							fdf_putpixel(x1, y1, data, get_color(data, first, second));
							if (++y1 == y2)
								break ;
							e -= dx;
							if (e < 0)
							{
								++x1; // déplacement diagonal
								e += dy;
							}
						}
					}
				}
				else // dy < 0 (et dx > 0) vecteur oblique dans le 4e cadran
				{
					if (dx >= -dy) // vecteur diagonal ou oblique proche de l’horizontale, dans le 8e octant
					{
						e = dx;
						dx = e * 2;
						dy *= 2; // e est positif
						while (1)  // déplacements horizontaux
						{
							fdf_putpixel(x1, y1, data, get_color(data, first, second));
							if (++x1 == x2)
								break ;
							e += dy;
							if (e < 0)
							{
								--y1; // déplacement diagonal
								e += dx;
							}
						}
					}
					else // vecteur oblique proche de la verticale, dans le 7e octant
					{
						e = dy;
						dy = e * 2;
						dx *= 2; // e est négatif
						while (1) // déplacements verticaux
						{
							fdf_putpixel(x1, y1, data, get_color(data, first, second));
							if (--y1 == y2)
								break ;
							e += dx;
							if (e > 0)
							{
								++x1; // déplacement diagonal
								e += dy;
							}
						}
					}
				}
			}
			else // dy = 0 (et dx > 0) vecteur horizontal vers la droite
				while (x1 != x2)
					fdf_putpixel(x1++, y1, data, get_color(data, first, second));
		}
		else // dx < 0
		{
			dy = y2 - y1;
			if (dy)
			{
				if (dy > 0) // vecteur oblique dans le 2d quadran
				{
					if (-dx >= dy) // vecteur diagonal ou oblique proche de l’horizontale, dans le 4e octant
					{
						e = dx;
						dx = e * 2;
						dy *= 2; // e est négatif
						while (1) // déplacements horizontaux
						{
							fdf_putpixel(x1, y1, data, get_color(data, first, second));
							if (--x1 == x2)
								break ;
							e += dy;
							if (e >= 0)
							{
								++y1;
								e += dx;
							}
						}
					}
					else // vecteur oblique proche de la verticale, dans le 3e octant
					{
						e = dy;
						dy = e * 2;
						dx *= 2; // e est positif
						while (1) // déplacements verticaux
						{
							fdf_putpixel(x1, y1, data, get_color(data, first, second));
							if (++y1 == y2)
								break ;
							e += dx;
							if (e <= 0)
							{
								--x1; // déplacement diagonal
								e += dy;
							}
						}
					}
				}
				else // dy < 0 (et dx < 0) vecteur oblique dans le 3e cadran
				{
					if (dx <= dy) // vecteur diagonal ou oblique proche de l’horizontale, dans le 5e octant
					{
						e = dx;
						dx = e * 2;
						dy *= 2; // e est négatif
						while (1) // déplacements horizontaux
						{
							fdf_putpixel(x1, y1, data, get_color(data, first, second));
							if (--x1 == x2)
								break ;
							e -= dy;
							if (e >= 0)
							{
								--y1; // déplacement diagonal
								e += dx;
							}
						}
					}
					else // vecteur oblique proche de la verticale, dans le 6e octant
					{
						e = dy;
						dy = e * 2;
						dx *= 2; // e est négatif
						while (1) // déplacements verticaux
						{
							fdf_putpixel(x1, y1, data, get_color(data, first, second));
							if (--y1 == y2)
								break ;
							e -= dx;
							if (e >= 0)
							{
								--x1; // deplacement diagonal
								e += dy;
							}
						}
					}
				}
			}
			else  // dy = 0 (et dx < 0)  vecteur horizontal vers la gauche
				while (x1 != x2)
					fdf_putpixel(x1--, y1, data, get_color(data, first, second));
		}
	}
	else  // dx = 0
	{
		dy = y2 - y1;
		if (dy)
		{
			if (dy > 0) // vecteur vertical croissant
				while (y1 != y2)
					fdf_putpixel(x1, y1++, data, get_color(data, first, second));
		} 
		else // dy < 0 (et dx = 0) vecteur vertical décroissant
			while (y1 != y2)
				fdf_putpixel(x1, y1--, data, get_color(data, first, second));
	}
	fdf_putpixel(x2, y2, data, get_color(data, first, second));
}
