#include "fdf.h"

int     **get_coords(char *file, int width, int height)
{
        int     x;
        int     y;
        int     **pixel;

        pixel = (int**)malloc(sizeof(int) * height);
        if (!pixel)
                return (NULL);

        int i = 0;
        while (i < height)
        {
                pixel[i] = (int*)malloc(sizeof(int) * width);
                if (!pixel[i])
                {
                        int ii = 0;
                        while (ii < i)
                        {
                                free(pixel[ii]);
                                ii++;
                        }
                        free(pixel);
                }
                i++;
        }

        int fd = open(file, O_RDONLY);
        y = 0;
        while (y < height)
        {
                char *line = get_next_line(fd);
                char **split = ft_split(line, ' ');
                free(line);
                x = 0;
                while (x < width)
                {
                        pixel[y][x] = ft_atoi(split[x]); // Pega o Z.
                        x++;
                }
                free(split);
                y++;
        }
        close(fd);
        return (pixel);
}
