/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 06:21:47 by maboye            #+#    #+#             */
/*   Updated: 2019/07/17 09:33:28 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			fdf_putpixel(int x, int y, t_fdf *data, char *color)
{
	long	pos;

	pos = (long)x + (long)y * WIN_L + data->center;
	//printf("center: %ld pos: %ld x: %d, y: %d\n", data->center, pos, x, y);
	if (pos < 0 || pos > WIN_L * WIN_H)
		return ;
	data->img->add[pos] = color ? (int)ft_atoi_base(color, 16) : 0xFFFFFF;
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
							fdf_putpixel(x1, y1, data, first->hexa);
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
							fdf_putpixel(x1, y1, data, first->hexa);
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
							fdf_putpixel(x1, y1, data, first->hexa);
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
							fdf_putpixel(x1, y1, data, first->hexa);
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
					fdf_putpixel(x1++, y1, data, first->hexa);
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
							fdf_putpixel(x1, y1, data, first->hexa);
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
							fdf_putpixel(x1, y1, data, first->hexa);
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
							fdf_putpixel(x1, y1, data, first->hexa);
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
							fdf_putpixel(x1, y1, data, first->hexa);
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
					fdf_putpixel(x1--, y1, data, first->hexa);
		}
	}
	else  // dx = 0
	{
		dy = y2 - y1;
		if (dy)
		{
			if (dy > 0) // vecteur vertical croissant
				while (y1 != y2)
					fdf_putpixel(x1, y1++, data, first->hexa);
		} 
		else // dy < 0 (et dx = 0) vecteur vertical décroissant
			while (y1 != y2)
				fdf_putpixel(x1, y1--, data, first->hexa);
	}
	fdf_putpixel(x2, y2, data, first->hexa);
}
