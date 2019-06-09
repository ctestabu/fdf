/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thereretry.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctestabu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 19:47:36 by ctestabu          #+#    #+#             */
/*   Updated: 2019/06/03 19:47:36 by ctestabu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <unistd.h>
#include <stdlib.h>
#include "fdf2.h"
#include "./libft/libft.h"

//void *mlx_ptr;
//void *win_ptr;

int deal_key(int key, void *param)
{

	if (key == 53)
		exit (0);

	return (0);
}

int		*read_map(char *line, t_fdf *fdf)
{
	char **str;
	int *mass;
	int i;

	fdf->row_number = 0;
	str = ft_strsplit(line, ' ');
	while (str[fdf->row_number] != NULL)
		(fdf->row_number)++;//КОЛИЧЕСТВО СИМВОЛОВ В СТРОКЕ [x]
	mass = (int*)malloc(sizeof(int) * fdf->row_number);
	i = 0;
	while (str[i] != NULL)
	{
		mass[i] = ft_atoi(str[i]);
//		printf("%d\n", mass[i]);
		i++;
	}
/*	printf("%d\n", i);*/
	return(mass);
}

int **create_int_massive(char *filename, t_fdf *fdf)
{
	int **massive;
	int i;
	char *line;
	int file;

	fdf->col_number = 0;
	file = open(filename, O_RDONLY);
	while (get_next_line(file, &line))
		(fdf->col_number)++;// КОЛИЧЕСТВО СТОЛБЦОВ [y]
	close(file);
//	printf("%d\n", fdf->col_number);
	massive = (int **)malloc(sizeof(int *) * (fdf->col_number + 1));
	massive[fdf->col_number] = NULL;
	i = 0;
	file = open(filename, O_RDONLY);
	while (get_next_line(file, &line))
	{
		massive[i] = read_map(line, fdf);
		i++;
	}
	close(file);
	fdf->coord_massive = massive;
//	int x;
//	x = 0;
//	while (x < fdf->col_number)
//	{
//		int k;
//		k = 0;
//		while (k < fdf->row_number)
//		{
//			printf("%d", fdf->coord_massive[x][k]);
//			k++;
//		}
//		printf("\n");
//		x++;
//	}
	return (0);
}

void	init(t_fdf *fdf)
{
	fdf->scale_x = 35;
	fdf->scale_y = 35;
	fdf->start_x = 800;
	fdf->start_y = 100;
}

int		mapping(t_fdf *fdf)
{
	draw_y(fdf);
	draw_x(fdf);
	return (1);
}

int main(int ac, char **av)
{
	t_fdf fdf;
	int fd;

	fdf.mlx_ptr = mlx_init();
	fdf.win_ptr = mlx_new_window(fdf.mlx_ptr, 2500, 2500, "mlx 42");
	init(&fdf);
	create_int_massive(av[1], &fdf);
//	printf("%d\n", fdf.coord_massive[1][1]);
	mlx_expose_hook(fdf.win_ptr, mapping, &fdf);

	mlx_key_hook(fdf.win_ptr, deal_key, (void *)0);
	mlx_loop(fdf.mlx_ptr);
	return (0);
}