/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:51:51 by dderny            #+#    #+#             */
/*   Updated: 2025/04/01 21:10:15 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <X11/Xutil.h>
#include <mlx.h>
#include <ft_printf.h>
#include <errno.h>
#include <ft_time.h>
#include <sys/types.h>
#include "classes/element.h"
#include "error.h"
#include "libft.h"
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
	t_img	*lbuffer;
	t_img	*hudbuffer;
	void	*buffer;

//#ifdef DEBUG
	printticks(env);
//#endif
	*getseed() = env->seed;

	lbuffer = mlx_new_image(env->mlx, 398, 224);
	hudbuffer = mlx_new_image(env->mlx, env->width, env->height);
	if (!lbuffer)
	{
		ft_printf("Error\n%s\n", strerror(errno));
		mlx_destroy_window(env->mlx, env->win);
		mlx_destroy_display(env->mlx);
		free(env->mlx);
		exit(EXIT_FAILURE);
	}

	int scale = (int)((double)env->height / 224 * 1.3);

	lbuffer->format = 0;
	hudbuffer->format = scale;

	t_list	*node = env->scene->elements;
	while (node)
	{
		t_element *elem = (t_element *)node->content;
		if (elem->update)
			elem->update(elem);
		if (elem->draw)
			elem->draw(elem, lbuffer, hudbuffer);
		node = node->next;
	}

	if (scale)
	{
		buffer = mylx_img_scale(env->mlx, lbuffer, scale);
		mlx_put_image_to_window(env->mlx, env->win, buffer, -8 * scale, -8 * scale);
		mlx_destroy_image(env->mlx, buffer);
	}
	mlx_put_image_to_window(env->mlx, env->win, hudbuffer, 0, 0);
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

int	last_keys_states[80000] = {0};
int	keys_states[80000] = {0};

int	down_key(int keycode, t_gameenv *env)
{
	if (keycode == XK_Escape)
		process_close(env);
	keys_states[keycode] = 1;
	return (0);
}

int	up_key(int keycode, t_gameenv *env)
{
	keys_states[keycode] = 0;
	if (keycode == XK_Escape)
		process_close(env);
	return (0);
}

int	update(t_gameenv *env)
{
	int modifier;
	if (keys_states[(u_int8_t)('w')] && !last_keys_states[(u_int8_t)('w')])
		env->ply->actor->move(env->ply->actor, 2, 0);
	modifier = MOVE_JOG;
	if (keys_states[XK_Alt_L])
		modifier = MOVE_WALK;
	if (keys_states[XK_Shift_L])
		modifier = MOVE_SPEED;
	if (keys_states[(u_int8_t)('a')])
		env->ply->actor->move(env->ply->actor, 0, modifier);
	if (keys_states[(u_int8_t)('d')])
		env->ply->actor->move(env->ply->actor, 1, modifier);
	ft_memcpy(&last_keys_states, &keys_states, sizeof(int) * 256);

	static double lastrealtime = 0;
	static double elapsed = 0;

	env->time = ft_uptime();
	if (env->time == -1 && print_error("Time"))
		process_close(env);
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
