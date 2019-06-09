/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf2.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctestabu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 20:21:47 by ctestabu          #+#    #+#             */
/*   Updated: 2019/06/03 20:21:47 by ctestabu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF2_H
# define FDF2_H

# include "./libft/libft.h"
# include <math.h>
# include <unistd.h>
# include <mlx.h>
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include <stdio.h>

typedef struct		s_fdf
{
	void 			*mlx_ptr;
	void 			*win_ptr;
	int 			row_number; // количество элементов в ряду
	int 			col_number; // количество столбцов координат
	int 			**coord_massive;
//	int 			*mass;
	int 			start_x; //стартовая координата начала отрисовки
	int 			start_y; // -//-
	int 			scale_x;
	int 			scale_y;
	int 			x1;
	int 			x2;
	int 			y1;
	int 			y2;
}					t_fdf;

void	draw_y(t_fdf *fdf);
void	draw_x(t_fdf *fdf);

#endif
