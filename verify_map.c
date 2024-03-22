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

int	map_size(int fd)
{
	int	size_l1;
	int	size_l2;
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		size_l1 = ft_strlen(line);
		free(line);
		line = get_next_line(fd);
		if (!line)
			break ;
		size_l2 = ft_strlen(line);
		if (size_l1 != size_l2)
			return (0);
	}
	close(fd);
	return (1);
}
