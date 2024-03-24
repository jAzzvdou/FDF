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

int	color(int z, int zmin, int zmax)
{
	float	calc;

	calc = (float)(z - zmin) / (zmax - zmin);

	int red = 255 * calc;
	int green = 0;
	int blue = 255 * (1 - calc);

	int color = (red << 16) | (green << 8) | blue;
	return (color);
}

int	**get_color(int	**pixel, int zmin, int zmax)
{
	int	y;
	int	x;

	i = 0;
	while (pixel[y])
	{
		ii = 0;
		while (pixel[y][x])
		{
			pixel[y][x][1] = color(pixel[y][x], zmin, zmax);
			x++;
		}
		y++;
	}
	return (pixel);
}

void	start_fdf(t_fdf *fdf, char *file)
{
	int	zmax;
	int	zmin;

	fdf->width = get_width(file);
	fdf->height = get_height(file);
	fdf->pixel = get_coords(file, fdf->width, fdf->height);
	zmax = biggest_z(fdf->pixel);
	zmin = smallest_z(fdf->pixel);
	fdf->pixel = get_color(fdf->pixel, zmin, zmax);
}

int	main(int argc, char **argv)
{
	int	fd;
	t_fdf	fdf;

	fdf = (t_fdf){0};
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
