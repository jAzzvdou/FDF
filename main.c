/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jazevedo <jazevedo@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 17:33:34 by jazevedo          #+#    #+#             */
/*   Updated: 2024/03/27 17:33:37 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#include "stdio.h"

int	get_width(char *argv1)
{
	int	fd;
	int	width;
	char	*line;
	char	**map;

	fd = open(argv1, O_RDONLY);
	line = get_next_line(fd);
	map = ft_split(line, ' ');
	free(line);
	close(fd);
	width = 0;
	while (map[width])
		width++;
	return (width);
}

int	get_height(char *argv1)
{
	int	fd;
	int	height;
	char	*line;

	fd = open(argv1, O_RDONLY);
	height = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		free(line);
		height++;
	}
	close(fd);
	return (height);
}

int	paint_z(int z, int zmin, int zmax)
{
	float	calc;

	calc = (float)(z - zmin) / (zmax - zmin);

	int red = 255 * calc;
	int green = 0;
	int blue = 255 * (1 - calc);

	int color = (red << 16) | (green << 8) | blue;
	return (color);
}

int	**get_color(t_fdf *fdf, int **file, int zmin, int zmax)
{
        int     x;
        int     y;
        int     **color;

        color = (int**)malloc(sizeof(int) * fdf->height);
        if (!color)
                return (NULL);

        int i = 0;
        while (i < fdf->height)
        {
                color[i] = (int*)malloc(sizeof(int) * fdf->width);
                if (!color[i])
                {
                        int ii = 0;
                        while (ii < i)
                        {
                                free(color[ii]);
                                ii++;
                        }
                        free(color);
                }
                i++;
        }
	y = 0;
	while (y < fdf->height)
	{
		x = 0;
		while (x < fdf->width)
		{
			color[y][x] = paint_z(file[y][x], zmin, zmax);
			x++;
		}
		y++;
	}
	return (color);
}

int	biggest_z(t_fdf *fdf, int **file)
{
	int	y;
	int	x;
	int	biggest;

	biggest = -2147483648;
	y = 0;
	while (y < fdf->height)
	{
		x = 0;
		while (x < fdf->width)
		{
			if (file[y][x] > biggest)
				biggest = file[y][x];
			x++;
		}
		y++;
	}
	return (biggest);
}

int	smallest_z(t_fdf *fdf, int **file)
{
	int	y;
	int	x;
	int	smallest;

	smallest = 2147483647;
	y = 0;
	while (y < fdf->height)
	{
		x = 0;
		while (x < fdf->width)
		{
			if (file[y][x] < smallest)
				smallest = file[y][x];
			x++;
		}
		y++;
	}
	return (smallest);
}

void	start_fdf(t_fdf *fdf, char *argv1)
{
	int	zmax;
	int	zmin;

	fdf->width = get_width(argv1);
	fdf->height = get_height(argv1);
	fdf->file = get_zcoord(argv1, fdf->width, fdf->height);
	zmax = biggest_z(fdf, fdf->file);
	zmin = smallest_z(fdf, fdf->file);
	fdf->color = get_color(fdf, fdf->file, zmin, zmax);
}

int	main(int argc, char **argv)
{
	int	fd;
	t_fdf	fdf;

	fdf = (t_fdf){0};
	if (argc < 2)
		return (write(2, "Error! To Few Arguments.\n", 25));
	if (revstrncmp(".fdf", argv[1], 5))
		return (write(2, "Error! Not '.fdf'.\n", 19));
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (write(2, "Error! Invalid File.\n", 21));
	if (!map_size(fd))
		return (write(2, "Error! Invalid Map Size.\n", 25));
	start_fdf(&fdf, argv[1]);

	fdf.mlx = mlx_init();
	fdf.window = mlx_new_window(fdf.mlx, WIDTH, HEIGHT, "MY FDF!");

//----------| TESTES |----------//

	int x = 10;
	int y = 10;
	int side = 100;

	int down = 9;
	int right = 18;
	int i = 0;
	while (i++ < down)
	{
		int ii = 0;
		while (ii++ < right)
		{
			wu(&fdf, x, y, x + side, y);
			wu(&fdf, x + side, y, x + side, y + side);
			wu(&fdf, x + side, y + side, x, y + side);
			wu(&fdf, x, y + side, x, y);
			x = x + side;
		}
		x = 10;
		y = y + side;
	}

//--------------------//

	mlx_loop(fdf.mlx);

	return (0);
}
