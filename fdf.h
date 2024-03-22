/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jazevedo <jazevedo@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 17:29:55 by jazevedo          #+#    #+#             */
/*   Updated: 2024/03/21 17:47:17 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <unistd.h> // WRITE, READ
# include <stdlib.h> // MALLOC, FREE, NULL
# include <fcntl.h>  // OPEN, CLOSE
# include <math.h>   // SIN, COS, TAN...

//----------MAP STRUCT----------//
typedef struct s_pixel
{
	double	x;
	double	y;
	double	z;
	int	rgb[3];
}	t_pixel;

//----------MAIN STRUCT----------//
typedef struct s_fdf
{
	int	width;   // -> Largura;
	int	height;  // -> Altura;
	int	**pixel; // -> Pontos do mapa.
}	t_fdf;

//----------FDF----------//

//----------MAP UTILS----------//
char	*get_next_line(int fd);
int	revstrncmp(char *compare, char *argv, int n);
int	map_size(int fd);

//----------UTILS----------//
size_t	ft_strlen(const char *str);
int	ft_atoi(const char *nptr);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char *s1, char *s2);
char	**ft_split(char const *s, char c);

#endif //FDF
