/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jazevedo <jazevedo@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:15:02 by jazevedo          #+#    #+#             */
/*   Updated: 2024/03/21 17:49:34 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	revstrncmp(char *compare, char *argv, int n)
{
	int	i;
	int	ii;

	if (n == 0)
		return (0);
	i = 0;
	ii = 0;
	while (argv[i])
		i++;
	while (compare[ii])
		ii++;
	while (n--)
		if (argv[i--] != compare[ii--])
			return (1);
	return (0);
}

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

// MUDAR ESSA FUNÇÃO! DÁ PRA DEIXAR MELHOR.
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
