#include "fdf.h"

void	wu(t_fdf *fdf, int x1, int y1, int x2, int y2)
{
	int dx = abs(x2 - x1);
	int dy = abs(y2 - y1);
	int steep = dy > dx;

	if (steep)
	{
		int temp = x1;
		x1 = y1;
		y1 = temp;
		temp = x2;
		x2 = y2;
		y2 = temp;
	}
	if (x1 > x2)
	{
		int temp = x1;
		x1 = x2;
		x2 = temp;
		temp = y1;
		y1 = y2;
		y2 = temp;
	}
	float gradient = (float)(y2 - y1) / (x2 - x1);
	float y = y1 + gradient;
	float ystep = gradient;
	for (int x = x1 + 1; x < x2; x++)
	{
		if (steep)
		{
			mlx_pixel_put(fdf->mlx, fdf->window, (int)y, x, fdf->color[0][0]);
			mlx_pixel_put(fdf->mlx, fdf->window, (int)y + 1, x, fdf->color[1][1]);
		}
		else
		{
			mlx_pixel_put(fdf->mlx, fdf->window, x, (int)y, fdf->color[1][1]);
			mlx_pixel_put(fdf->mlx, fdf->window, x, (int)y + 1, fdf->color[2][2]);
		}
		y += ystep;
	}
}
