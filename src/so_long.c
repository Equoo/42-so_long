
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

#include "map_parser.h"
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
	//mlx_get_screen_size(env.mlx, &env.width, &env.height);
	env.win = mlx_new_window(env.mlx, env.width, env.height, "So long");

	if (!load_map("maps/test.ber"))
	{
		mlx_destroy_window(env.mlx, env.win);
		mlx_destroy_display(env.mlx);
		free(env.mlx);		
		return (EXIT_FAILURE);
	}

	mlx_hook(env.win, ON_DESTROY, 0, process_close, &env);
	mlx_loop_hook(env.mlx, &update, &env);
	mlx_loop(env.mlx);

	return (EXIT_SUCCESS);
}
