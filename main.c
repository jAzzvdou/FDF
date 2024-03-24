/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jazevedo <jazevedo@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 17:33:34 by jazevedo          #+#    #+#             */
/*   Updated: 2024/03/21 17:48:12 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "stdio.h"

int	get_width(char *file)
{
	int	fd;
	int	width;
	char	*line;
	char	**map;

	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	map = ft_split(line, ' ');
	free(line);
	close(fd);
	width = 0;
	while (map[width])
		width++;
	return (width);
}

int	get_height(char *file)
{
	int	fd;
	int	height;
	char	*line;

	fd = open(file, O_RDONLY);
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

int	**get_color(t_fdf *fdf, int **pixel, int zmin, int zmax)
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
			color[y][x] = paint_z(pixel[y][x], zmin, zmax);
			x++;
		}
		y++;
	}
	return (color);
}

int	biggest_z(t_fdf *fdf, int **pixel)
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
			if (pixel[y][x] > biggest)
				biggest = pixel[y][x];
			x++;
		}
		y++;
	}
	return (biggest);
}

int	smallest_z(t_fdf *fdf, int **pixel)
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
			if (pixel[y][x] < smallest)
				smallest = pixel[y][x];
			x++;
		}
		y++;
	}
	return (smallest);
}

void	start_fdf(t_fdf *fdf, char *file)
{
	int	zmax;
	int	zmin;

	fdf->width = get_width(file);
	fdf->height = get_height(file);
	fdf->pixel = get_coords(file, fdf->width, fdf->height);
	zmax = biggest_z(fdf, fdf->pixel);
	zmin = smallest_z(fdf, fdf->pixel);
	fdf->color = get_color(fdf, fdf->pixel, zmin, zmax);
	int y = 0;
	while (y < fdf->height)
	{
		int x = 0;
		while (x < fdf->width)
		{
			printf("z: %d.\n", fdf->pixel[y][x]);
			printf("color: %d.\n", fdf->color[y][x]);
			x++;
		}
		y++;
	}
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

	return (0);
}
