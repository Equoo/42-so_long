/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:51:51 by dderny            #+#    #+#             */
/*   Updated: 2025/03/20 02:50:54 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <ft_printf.h>
#include <errno.h>
#include <ft_time.h>
#include "classes/vector2d.h"
#include "so_long.h"
#include "render.h"
#include "seed.h"

void printticks(t_gameenv *env)
{
	static double last = 0;
	static double middle = 0;
	static int fps = TICK;
	static int count = 0;

	middle = middle + env->frametime;
	count++;
	if (env->time - last >= 1)
	{
		middle /= count;
		count = 0;
		fps = 1 / middle;
		middle = env->frametime;
		last = env->time;
	}
	ft_printf("Time: %f s; Frame time: %f; TICK: %i; FPS: %i;\n", env->time, env->frametime, (int)(1 / env->frametime), fps);
}

int	tick(t_gameenv *env)
{
	void	*lbuffer;
	void	*buffer;

#ifdef DEBUG
	printticks(env);
#endif
	*getseed() = env->seed;

	lbuffer = mlx_new_image(env->mlx, (int)((double)env->width / (double)env->height * 16.f * 14.f), 16 * 14);

	if (!lbuffer) // NEW_IMAGE RETURN 11 ???????? WHY ????? WHY ?????
	{
		ft_printf("Error\n%s\n", strerror(errno));
		mlx_destroy_window(env->mlx, env->win);
		mlx_destroy_display(env->mlx);
		free(env->mlx);
		exit(EXIT_FAILURE);
	}

	texture_draw_slice(env->back0, lbuffer, (t_transform){{0, 16}, {0}, 0}, "all");
	texture_blend_slice(env->back1, lbuffer, (t_transform){{0, 16 * 9}, {0}, 0}, "all");
	texture_blend_slice(env->back2, lbuffer, (t_transform){{0, 16 * 9 + 8}, {0}, 0}, "all");

	texture_draw_slice(env->back0, lbuffer, (t_transform){{288, 16}, {0}, 0}, "all");
	texture_blend_slice(env->back1, lbuffer, (t_transform){{288, 16 * 9}, {0}, 0}, "all");
	texture_blend_slice(env->back2, lbuffer, (t_transform){{288, 16 * 9 + 8}, {0}, 0}, "all");

	env->terrain->base->draw(env->terrain->base, lbuffer);

	static double sanim;
	if (!sanim)
		sanim = env->time;
	double tanim = (env->time - sanim) / 0.8 * 7;
	mylx_img_blend((t_copyimg){
		(t_int2d){32 * (int)tanim, 0},
		(t_int2d){32, 32},
		(t_int2d){90, 160},
		env->character->img,
		lbuffer,
		FLIP_HORIZ,
		0});
	if (env->time - sanim > 0.8)
		sanim = env->time;

	buffer = mylx_img_scale(env->mlx, lbuffer, env->height / (16 * 12));
	mlx_put_image_to_window(env->mlx, env->win, buffer, 0, 0);
	mlx_destroy_image(env->mlx, buffer);

	mlx_destroy_image(env->mlx, lbuffer);

	return (0);
}

//pacat --rate=8000 --format=u8 --channels=1
	//static int fd;
	//char line[180];
	//if (!fd)
		//fd = open("music.raw", O_RDONLY);
	//read(fd, line, 180);
	//write(1, line, 180);
int	update(t_gameenv *env)
{
	static double lastrealtime = 0;
	static double elapsed = 0;

	env->time = ft_uptime();
	if (!env->lastframe)
		env->lastframe = env->time;
	if (!lastrealtime)
		lastrealtime = env->time;
	elapsed += env->time - lastrealtime;
	if (elapsed >= 1.f / ((double)TICK))
	{
		elapsed -= 1.f / ((double)TICK);
		env->frametime = (env->time - env->lastframe);
		tick(env);
		env->lastframe = env->time;
	}
	lastrealtime = env->time;
	return (0);
}
