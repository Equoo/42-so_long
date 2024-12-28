
#include <stdlib.h>
#include "mlx.h"

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct	s_vars {
	void	*mlx;
	void	*win;
	t_data	*img;
}				t_vars;

enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	close(int __attribute__((unused))keycode, t_vars *vars)
{
	free(vars->img->img);
	mlx_destroy_window(vars->mlx, vars->win);
	return (0);
}

int	render_next_frame(void *__attribute__((unused))vars)
{


	return (0);
}

int	main(int __attribute__((unused))argc, char **__attribute__((unused))argv)
{
	t_vars	vars;
	t_data	img;


	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1920, 1080, "Hello world!");
	vars.img = &img;
	img.img = mlx_new_image(vars.mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);

	int i = 0;
	while (i < 200)
	{
		my_mlx_pixel_put(&img, i, 5, 0x00FF0000);
		my_mlx_pixel_put(&img, i, 6, 0x0FFF0000);
		my_mlx_pixel_put(&img, i, 7, 0xFFFF0000);
		i++;
	}

	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);

	mlx_hook(vars.win, ON_DESTROY, 0, close, &vars);
	mlx_loop_hook(vars.mlx, render_next_frame, &vars);

	mlx_hook(vars.win, 2, 1L<<0, close, &vars);
	mlx_loop(vars.mlx);

	return (0);
}