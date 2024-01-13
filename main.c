static int	start_fdf(t_fdf *fdf, int argc, char **argv)
{
	fdf->width = 0;
	fdf->height = 0;
	fdf->map = open(argv[1], O_RDONLY);
	if (fdf->map < 0)
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	if (argc != 2)
		return (write(2, ".ERROR! Usage: ./fdf <map.fdf>.\n", 32);
	if (start_fdf(&fdf, argc, argv))
		return (write(2, ".ERROR! start_fdf.\n", 19));
	// -> LER O ARQUIVO DO MAPA E ARMAZENAR AS INFOS NA STRUCT.
	// -> ABRIR A JANELA DO MAPA COM A MLX.
	// -> LER AS TECLAS DO USUÁRIO.
	/* -> FUNÇÃO BOLADA PRA DAR FREE E NÃO VAZAR NADA.
	 * TEM QUE DAR FREE EM CADA PONTO. */
	return (0);
}
