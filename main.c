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

void	start_fdf(t_fdf *fdf, char *file)
{
	fdf->width = get_width(file);
	fdf->height = get_height(file);
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
	printf("Largura do Mapa: %d.\n", fdf.width);
	printf("Altura do Mapa: %d.\n", fdf.height);

	return (0);
}
