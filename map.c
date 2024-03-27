#include "fdf.h"

int     **get_zcoord(char *argv1, int width, int height)
{
        int     x;
        int     y;
        int     **file;

        file = (int**)malloc(sizeof(int) * height);
        if (!file)
                return (NULL);

        int i = 0;
        while (i < height)
        {
                file[i] = (int*)malloc(sizeof(int) * width);
                if (!file[i])
                {
                        int ii = 0;
                        while (ii < i)
                        {
                                free(file[ii]);
                                ii++;
                        }
                        free(file);
                }
                i++;
        }

        int fd = open(argv1, O_RDONLY);
        y = 0;
        while (y < height)
        {
                char *line = get_next_line(fd);
                char **split = ft_split(line, ' ');
                free(line);
                x = 0;
                while (x < width)
                {
                        file[y][x] = ft_atoi(split[x]); // Pega o Z.
                        x++;
                }
                free(split);
                y++;
        }
        close(fd);
        return (file);
}
