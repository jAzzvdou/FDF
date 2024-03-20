/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jazevedo <jazevedo@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 17:33:34 by jazevedo          #+#    #+#             */
/*   Updated: 2024/03/20 16:52:50 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "stdio.h"

int	count_spaces(char *line)
{
	int	i;
	int	spaces;

	spaces = 0;
	i = -1;
	while (line[++i])
		if (line[i] == ' ')
			spaces++;
	return (spaces);
}

int	map_size(int fd)
{
	int	i;
	int	spaces;
	char	*line;

	line = get_next_line(fd);
	spaces = count_spaces(line);
	free(line);
	line = get_next_line(fd);
	i = count_spaces(line);
	if (spaces != i)
		return (0);
	while (line)
	{
		spaces = count_spaces(line);
		free(line);
		line = get_next_line(fd);
		if (!line)
			break ;
		i = count_spaces(line);
		if (spaces != i)
			return (0);
	}
	close(fd);
	return (1);
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
	return (0);
}
