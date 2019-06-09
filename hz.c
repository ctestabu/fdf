/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hz.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctestabu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 20:21:10 by ctestabu          #+#    #+#             */
/*   Updated: 2019/06/03 20:21:10 by ctestabu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf2.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

//void drawline(int x0, int y0, int x1, int y1)
//{
//	int dx, dy, p, x, y;
//
//	dx = x1 - x0;
//	dy = y1 - y0;
//
//	x = x0;
//	y = y0;
//
//	p = 2 * dy - dx;
//
//	while(x < x1)
//	{
//		if(p >= 0)
//		{
//			mlx_pixel_put(fdf.mlx_ptr,fdf.win_ptr, x, y, 0xDC143C);
//			y = y+1;
//			p = p + 2 * dy - 2 * dx;
//		}
//		else
//		{
//			mlx_pixel_put(fdf.mlx_ptr,fdf.win_ptr, x, y, 0xDC143C);
//			p = p + 2 * dy;
//		}
//		x = x + 1;
//	}
//}


void drawLine(t_fdf *fdf)
{
	const int deltaX = abs(fdf->x2 - fdf->x1);
	const int deltaY = abs(fdf->y2 - fdf->y1);
	const int signX = fdf->x1 < fdf->x2 ? 1 : -1;
	const int signY = fdf->y1 < fdf->y2 ? 1 : -1;
	//
	int error = deltaX - deltaY;
	//
	mlx_pixel_put(fdf->mlx_ptr, fdf->win_ptr, fdf->x2, fdf->y2, 0xDC143C);
	while(fdf->x1 != fdf->x2 || fdf->y1 != fdf->y2)
	{
		mlx_pixel_put(fdf->mlx_ptr, fdf->win_ptr, fdf->x1, fdf->y1, 0xDC143C);
		const int error2 = error * 2;
		//
		if(error2 > -deltaY)
		{
			error -= deltaY;
			fdf->x1 += signX;
		}
		if(error2 < deltaX)
		{
			error += deltaX;
			fdf->y1 += signY;
		}
	}
}

int		coord_x(t_fdf *fdf, int x, int y)
{
	return (fdf->start_x - (fdf->scale_x * y) + (fdf->scale_x * x));
}

int		coord_y(t_fdf *fdf, int x, int y, int z)
{
	if (z > 15000)
		z = 15000;
	if (z < -15000)
		z = -15000;
	return (fdf->start_y + ((fdf->scale_y) * x) + ((fdf->scale_y) * y) -  (z * 2));
}

void	draw_x(t_fdf *fdf)
{
	int i;
	int j;

	i = 0;
	while (i < (fdf->row_number))
	{
		j = 0;
		while (j < fdf->col_number - 1)
		{
			fdf->x1 = coord_x(fdf, i, j);
			fdf->y1 = coord_y(fdf, j, i, fdf->coord_massive[j][i]);
			fdf->x2 = coord_x(fdf, i, j + 1);
			fdf->y2 = coord_y(fdf, j, i + 1, fdf->coord_massive[j + 1][i]);
			drawLine(fdf);
			j++;
		}
		i++;
	}
} // FIX

void	draw_y(t_fdf *fdf)
{
	int			i;
	int			j;

	i = 0;
	while (i < fdf->col_number)
	{
		j = 0;
		while (j < fdf->row_number - 1)
		{
			fdf->x1 = coord_x(fdf, j, i);
			fdf->y1 = coord_y(fdf, j, i, fdf->coord_massive[i][j]);
			j++;
			fdf->x2 = coord_x(fdf, j, i);
			fdf->y2 = coord_y(fdf, j, i, fdf->coord_massive[i][j]);
			drawLine(fdf);
		}
		i++;
	}
}


//void	draw_x(t_fdf *fdf)
//{
//	int i;
//	int j;
//
//	i = 0;
//	while (i < (fdf->row_number))
//	{
//		j = 0;
//		while (j < fdf->col_number - 1)
//		{
//			fdf->x1 = coord_x(fdf, i, j);
//			fdf->y1 = coord_y(fdf, j, i, fdf->coord_massive[j][i]);
//			fdf->x2 = coord_x(fdf, i, j + 1);
//			fdf->y2 = coord_y(fdf, j, i + 1, fdf->coord_massive[j + 1][i]);
//			drawLine(fdf);
//			j++;
//		}
//		i++;
//	}
//} // FIX
