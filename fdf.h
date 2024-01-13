#ifndef FDF_H
# define FDF_H

# include <unistd.h> // WRITE, READ
# include <stdlib.h> // MALLOC, FREE, NULL
# include <fcntl.h>  // OPEN, CLOSE
# include <math.h>   // SIN, COS, TAN...

typedef struct s_coords
{
	double	x;
	double	y;
	double	z;
	int	rgb[3];
}	t_coords;

/* Todo ponto, na teoria, deverá ter uma coordenada x, y, e z. Além, também de uma cor. */

typedef struct s_fdf
{
	int	width;          // -> Largura.
	int	height;         // -> Altura.
	void	*mlx;           // -> Conexão com a MLX(???).
	void	*window         // -> Janela(???).
	t_coords	**map;  // -> Pontos do mapa (Matriz).
}	t_fdf;

//----------FDF----------//

//----------UTILS----------//

#endif //FDF
