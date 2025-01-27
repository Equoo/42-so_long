/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:51:51 by dderny            #+#    #+#             */
/*   Updated: 2025/01/27 06:19:48 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <ft_printf.h>
#include "classes/vector2d.h"
#include "so_long.h"
#include "render.h"

int	tick(t_gameenv *env)
{
	void	*lbuffer;
	void	*buffer;

	static void	*img;
	static void	*img2;
	char	*relative_path = "./textures/stringstar_fields.xpm";
	char	*relative_path2 = "./textures/cat.xpm";
	int		img_width;
	int		img_height;

	lbuffer = mlx_new_image(env->mlx, (int)((double)env->width / (double)env->height * 16.f * 13.f), 16 * 13);
	if (!img2)
		img2 = mlx_xpm_file_to_image(env->mlx, relative_path2, &img_width, &img_height);
	if (!img)
		img = mlx_xpm_file_to_image(env->mlx, relative_path, &img_width, &img_height);
		
	mylx_img_blend((t_iaabb){(t_int2d){0, 0}, (t_int2d){288, 176}}, (t_int2d){0, 0}, lbuffer, img);
	
	//mylx_img_copy((t_iaabb){(t_int2d){56, 35}, (t_int2d){200, 100}}, (t_int2d){40, 40}, lbuffer, img);

	static double sanim;
	if (!sanim)
		sanim = env->time;
	double tanim = (env->time - sanim) / 0.8 * 7;
	mylx_img_blend((t_iaabb){(t_int2d){32 * (int)tanim, 0}, (t_int2d){32 * ((int)tanim + 1), 32}}, (t_int2d){70, 112}, lbuffer, img2);
	if (env->time - sanim > 0.8)
		sanim = env->time;

	buffer = mylx_img_scale(env->mlx, lbuffer, env->height / (16 * 12));
	mlx_put_image_to_window(env->mlx, env->win, buffer, 0, 0);
	mlx_destroy_image(env->mlx, buffer);
	
	mlx_destroy_image(env->mlx, lbuffer);
	return (0);
}

int	update(t_gameenv *env)
{
	static double middle = 0;
	static double last = 0;
	// static int fps = TICK;
	static int count = 0;

	env->time = uptime();
	if (!env->lastframe)
		env->lastframe = env->time;

	if (!last)
		last = env->time;

	if (env->time - env->lastframe >= 1.f / ((double)TICK))
	{
		env->frametime = (env->time - env->lastframe);
		
		middle = middle + env->frametime;
		count++;
		if (env->time - last >= 1)
		{
			middle /= count;
			count = 0;
			// fps = 1 / middle;
			middle = env->frametime;
			last = env->time;
		}

		tick(env);
		//ft_printf("Time: %f s; Frame time: %f; TICK: %i; FPS: %i;\n", env->time, env->time - env->lastframe, (int)(1 / (env->time - env->lastframe)), fps);
		env->lastframe = env->time;
	}
	return (0);
}
