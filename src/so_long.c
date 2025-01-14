
#include <ft_printf.h>
#include <stdlib.h>
#include <fcntl.h>
#include <mlx.h>
#include <stdio.h>
#include <libft.h>
#include "so_long.h"
#include "render.h"

int	process_close(t_gameenv *env)
{
	mlx_destroy_window(env->mlx, env->win);
	mlx_destroy_display(env->mlx);
	free(env->mlx);
	exit(EXIT_SUCCESS);
	return (0);
}

int	main()
{
	t_gameenv	env;
	//t_data	img;

	env = (t_gameenv){};
	env.mlx = mlx_init();
	if (!env.mlx)
		return (0);
	env.width = 1920;
	env.height = 1080;
	env.win = mlx_new_window(env.mlx, env.width, env.height, "So long");

	//vars.img = &img;
	//img.img = mlx_new_image(vars.mlx, 1920, 1080);
	//img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
	//							&img.endian);

	//int i = 0;
	//while (i < 200)
	//{
	//	my_mlx_pixel_put(&img, i, 5, 0x00FF0000);
	//	my_mlx_pixel_put(&img, i, 6, 0x0FFF0000);
	//	my_mlx_pixel_put(&img, i, 7, 0xFFFF0000);
	//	i++;
	//}

	//mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);

	//mlx_destroy_image(vars.mlx, vars.img->img);

	mlx_hook(env.win, ON_DESTROY, 0, process_close, &env);
	mlx_loop_hook(env.mlx, &update, &env);
	mlx_loop(env.mlx);

	return (0);
}
