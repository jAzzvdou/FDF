/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jazevedo <jazevedo@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 12:20:51 by jazevedo          #+#    #+#             */
/*   Updated: 2024/03/20 14:42:14 by jazevedo         ###   ########.fr       */
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

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	char	ch;

	ch = c;
	while (*s && *s != ch)
		s++;
	if (*s == ch)
		return ((char *)s);
	return (NULL);
}

char	*ft_strdup(const char *s)
{
	int		i;
	char	*final;

	final = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!final)
		return (NULL);
	i = -1;
	while (s[++i])
		final[i] = s[i];
	final[i] = '\0';
	return (final);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	char	*new_s;

	if (!s1 && !s2)
		return (NULL);
	new_s = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!new_s)
		return (NULL);
	i = 0;
	while (s1 && *s1)
		new_s[i++] = *s1++;
	while (s2 && *s2)
		new_s[i++] = *s2++;
	new_s[i] = '\0';
	return (new_s);
}
